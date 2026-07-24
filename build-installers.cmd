@CD /D "%~dp0"

cmd /c Setup\clean.cmd
cmd /c Setup\install-wix-tool.cmd
cmd /c Setup\build.cmd x86 3.2.11
cmd /c Setup\build.cmd x64 3.8.22
cmd /c Setup\build.cmd ARM64 4.1.44
