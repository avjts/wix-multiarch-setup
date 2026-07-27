@CD /D "%~dp0"

SET "slnfilename=Setup.slnx"
@IF "%VisualStudioVersion:~0,3%" == "17." SET "slnfilename=Setup.sln"

@SET arch=%1
@IF "%arch%"=="" SET arch=x64
@SET version=%2
@IF "%version%"=="" (
    @IF "%arch%"=="ARM64" SET version=3.0
    @IF "%arch%"=="x64" SET version=2.0
    @IF "%arch%"=="x86" SET version=1.0
)

msbuild %slnfilename% -t:Restore -p:Configuration=Release -p:Platform=%arch% -p:RestorePackagesConfig=true
msbuild %slnfilename% -t:Restore -p:Configuration=Release -p:Platform=%arch%

msbuild %slnfilename% -t:Build -p:Configuration=Release -p:Platform=%arch% -p:PRODUCT_VERSION=%version%
@IF ERRORLEVEL 1 EXIT /B 1
