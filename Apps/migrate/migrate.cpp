#include <Windows.h>

#include <iostream>
#include <sstream>

std::string wide_to_ansi(const std::wstring& wide_string)
{
    size_t buflen = (wide_string.length() + 1) * 2;
    std::string ansi_string(buflen, '\0');
    WideCharToMultiByte(CP_ACP, 0, wide_string.c_str(), -1, ansi_string.data(), (int)buflen, nullptr, nullptr);
    return ansi_string;
}

std::wstring GetTemporaryPath()
{
    constexpr DWORD max_length = MAX_PATH + 1;
    wchar_t path[max_length] = {};

    if (GetTempPathW(max_length, path) == 0)
    {
        std::cout << "GetTempPathW failed: " + std::to_string(GetLastError()) << std::endl;
        return {};
    }
    return path;
}

int main()
{
    std::cout << "Migrating...\n";

    const std::wstring dstBasePath = GetTemporaryPath();
    if (dstBasePath.empty())
    {
        return ERROR_INSTALL_FAILURE;
    }

    std::wstring migratorWorkspace = dstBasePath + L"\\MyMultiArchAppMigrations";
    std::cout << "Temporary path: " << wide_to_ansi(migratorWorkspace) << std::endl;
    BOOL success = CreateDirectoryW(migratorWorkspace.c_str(), NULL);
    DWORD errcode = GetLastError();
    if (success == FALSE && errcode != ERROR_ALREADY_EXISTS)
    {
        std::cerr<< "Creating migration workspace failed";
        return ERROR_INSTALL_FAILURE;
    }

    std::cout << "Migration workspace created.";
    return ERROR_SUCCESS;
}

