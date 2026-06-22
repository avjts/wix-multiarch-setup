@CD /D "%~dp0"

@SET arch=%1
@IF "%arch%"=="" SET arch=x64
@SET version=%2
@IF "%version%"=="" (
    @IF "%arch%"=="ARM64" SET version=3.0
    @IF "%arch%"=="x64" SET version=2.0
    @IF "%arch%"=="x86" SET version=1.0
)

@PUSHD .\MyMultiArchSetup

dotnet tool run -- wix extension add WixToolset.Util.wixext ^
 -acceptEula wix7
@IF ERRORLEVEL 1 POPD & EXIT /B 1

dotnet tool run -- wix build -arch %arch%  MyMultiArchSetup.wxs ^
 -acceptEula wix7 ^
 -ext WixToolset.Util.wixext ^
 -d MSIProductVersion=%version%  -o ..\_out\MySimpleAppSetup-%arch%-%version%.msi
@IF ERRORLEVEL 1 POPD & EXIT /B 1

@POPD

dotnet tool run -- wix msi validate _out\MySimpleAppSetup-%arch%-%version%.msi ^
 -acceptEula wix7
@IF ERRORLEVEL 1 EXIT /B 1

@EXIT /B 0
