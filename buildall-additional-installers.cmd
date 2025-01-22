@CD /D "%~dp0"

cmd /c Apps\cleanall.cmd
cmd /c Apps\buildall.cmd 3.2.15 3.8.25 4.1.45

cmd /c Setup\cleanall.cmd
cmd /c Setup\build.cmd x86 3.2.15
cmd /c Setup\build.cmd x64 3.8.25
cmd /c Setup\build.cmd ARM64 4.1.45
