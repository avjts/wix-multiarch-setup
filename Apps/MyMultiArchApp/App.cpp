#include "framework.h"
#include "App.h"
#include "resource.h"

#include <stdlib.h>

#define WSTRINGIFY(x) L#x
#define TOWSTRING(x) WSTRINGIFY(x)

HINSTANCE hInst;                     // current instance
WCHAR szWindowClass[100];            // the main window class name
bool EndingSession = false;


ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// Initialize global strings
	LoadStringW(hInstance, IDC_MYAPP, szWindowClass, _countof(szWindowClass));
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MYAPP));

	MSG msg;

	// Main message loop:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}



ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MYAPP));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_MYAPP);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

void BlinkMe(HWND hWnd)
{
	FLASHWINFO fi;
	fi.cbSize = sizeof(FLASHWINFO);
	fi.hwnd = hWnd;
	fi.dwFlags = FLASHW_ALL;
	fi.uCount = 5;
	fi.dwTimeout = 0;
	FlashWindowEx(&fi);
}


BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Store instance handle in our global variable

	WCHAR szTitle[200];
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, _countof(szTitle));
#if defined(_M_IX86)
	wcscat_s(szTitle, L" (x86)");
#elif defined(_M_X64)
	wcscat_s(szTitle, L" (x64)");
#elif defined(_M_ARM64)
	wcscat_s(szTitle, L" (Arm64)");
#endif

	wcscat_s(szTitle, L" ");
	wcscat_s(szTitle, TOWSTRING(PRODUCT_VERSION));

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}


void Ellipse(HDC hdc, int x, int y, int r)
{
	Ellipse(hdc, x - r, y - r, x + r, y + r);
}

void OnPaint(HWND hWnd, HDC hdc)
{
	RECT rect;
	GetClientRect(hWnd, &rect);
	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;
	int centerX = width / 2;
	int centerY = height / 2;

	int radius = (width < height ? width : height) / 4;

	HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, GetStockObject(EndingSession ? LTGRAY_BRUSH : BLACK_BRUSH));
	Ellipse(hdc, centerX, centerY, radius);
	SelectObject(hdc, GetStockObject(WHITE_BRUSH));
	Ellipse(hdc, centerX, centerY, radius * 3 / 4);
	Ellipse(hdc, centerX, centerY, radius / 2);
	SelectObject(hdc, hOldBrush);

	const wchar_t* version = TOWSTRING(PRODUCT_VERSION);
	if (EndingSession)
		version = L"End is near...";

	// Draw version, e.g. "3.8" in the center of the circle
	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, RGB(0, 0, 0));
	SIZE textSize;
	GetTextExtentPoint32(hdc, version, wcslen(version), &textSize);
	TextOut(hdc, centerX - textSize.cx / 2, centerY - textSize.cy / 2, version, wcslen(version));
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		OnPaint(hWnd, hdc);
		EndPaint(hWnd, &ps);
	}
	break;

	case WM_ENDSESSION:
	{
		if (wParam != 0)
		{
			if ((lParam & ENDSESSION_CLOSEAPP) != 0)
			{
				// Setup requested to close the app
				EndingSession = true;
				InvalidateRect(hWnd, NULL, TRUE);
				BlinkMe(hWnd);
				//MessageBox(hWnd, L"Installer requested to end session", L"SETUP", MB_OK);
			}
			else {
				//MessageBox(hWnd, L"Shutdown requested", L"SYSTEM", MB_OK);
			}
		}
	}
	break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}




INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
