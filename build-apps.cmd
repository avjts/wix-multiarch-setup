@CD /D "%~dp0"

cmd /c Apps\clean.cmd
cmd /c Apps\build.cmd Win32 3.2.11 x64 3.8.22 ARM64 4.1.44
