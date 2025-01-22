@CD /D "%~dp0"

@SET arch=%1
@IF "%arch%"=="" SET arch=x64
@SET version=%2
@IF "%version%"=="" (
    @IF "%arch%"=="ARM64" SET version=3.0
    @IF "%arch%"=="x64" SET version=2.0
    @IF "%arch%"=="x86" SET version=1.0
)

@CD .\MyMultiArchSetup
dotnet tool run -- wix extension add WixToolset.Util.wixext
@IF ERRORLEVEL 1 EXIT /B 1

dotnet tool run -- wix build -arch %arch%  MyMultiArchSetup.wxs ^
 -ext WixToolset.Util.wixext ^
 -d PackageVersion=%version%  -o ..\_out\MySimpleAppSetup-%arch%-%version%.msi
@IF ERRORLEVEL 1 EXIT /B 1

@CD ..
dotnet tool run -- wix msi validate _out\MySimpleAppSetup-%arch%-%version%.msi
@IF ERRORLEVEL 1 EXIT /B 1

EXIT /B 0
