#include "framework.h"

#include <MsiQuery.h>
#include <wcautil.h>
#include <sstream>
#include <vector>

namespace utils{
std::string wide_to_ansi(const std::wstring& wide_string)
{
	size_t buflen = (wide_string.length() + 1) * 2;
    std::string ansi_string(buflen, '\0');
    WideCharToMultiByte(CP_ACP, 0, wide_string.c_str(), -1, ansi_string.data(), buflen, nullptr, nullptr);
    return ansi_string;
}

void Log(const std::string& message)
{
    OutputDebugStringA((message + "\n").c_str());
    WcaLog(LOGMSG_STANDARD, "%s", message.c_str());
}

void Log(const std::wstring& message)
{
    OutputDebugStringW((message + L"\n").c_str());
    WcaLog(LOGMSG_STANDARD, "%s", wide_to_ansi(message).c_str());
}

HRESULT LogError(HRESULT hr, const std::string& message)
{
    OutputDebugStringA((message + "\n").c_str());
    WcaLogError(hr, "%s", message.c_str());
    return hr;
}

HRESULT LogError(HRESULT hr, const std::wstring& message)
{
    OutputDebugStringW((message + L"\n").c_str());
    WcaLogError(hr, "%s", wide_to_ansi(message).c_str());
    return hr;
}
}

std::wstring GetTemporaryPath()
{
    constexpr DWORD max_length = MAX_PATH + 1;
    wchar_t path[max_length] = {};

    if (GetTempPathW(max_length, path) == 0)
    {
        utils::Log("GetTempPathW failed: " + std::to_string(GetLastError()));
        return {};
    }
    return path;
}


UINT __stdcall InitialBackup(MSIHANDLE hInstall)
{
    HRESULT hr = WcaInitialize(hInstall, "InitialBackup");
    if (FAILED(hr))
    {
        utils::LogError(hr, "WcaInitialize failed.");
        return ERROR_INSTALL_FAILURE;
    }

    utils::Log("Backing up...");

    UINT result = ERROR_SUCCESS;
    const std::wstring dstBasePath = GetTemporaryPath();
    if (dstBasePath.empty())
    {
        utils::LogError(E_FAIL, "GetTemporaryPath() failed.");
        result = ERROR_INSTALL_FAILURE;
    }
    else
    {
        std::wstring backupFolder = dstBasePath + L"\\MyMultiArchBackup";
        utils::Log(L"Backup path: " + backupFolder);
        BOOL success = CreateDirectoryW(backupFolder.c_str(), NULL);
        DWORD errcode = GetLastError();
        if (success == FALSE && errcode != ERROR_ALREADY_EXISTS)
        {
			utils::LogError(HRESULT_FROM_WIN32(errcode), "Creating backupFolder failed: " + std::to_string(errcode));
            result = errcode;
        }
        else
        {
            utils::Log("Backup folder created.");
            result = ERROR_SUCCESS;
        }
    }

    return WcaFinalize(result);
}

