@CD /D "%~dp0"

cmd /c Setup\install-wix-5.cmd

cmd /c Apps\cleanall.cmd
cmd /c Apps\buildall.cmd 3.2.11 3.8.22 4.1.44

cmd /c Setup\cleanall.cmd
cmd /c Setup\build.cmd x86 3.2.11
cmd /c Setup\build.cmd x64 3.8.22
cmd /c Setup\build.cmd ARM64 4.1.44
