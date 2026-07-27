@ECHO OFF
@CD /D "%~dp0"

SET "slnfilename=MyMultiArchApp.slnx"
@IF "%VisualStudioVersion:~0,3%" == "17." SET "slnfilename=MyMultiArchApp.sln"

@IF "%~1"=="" (
    CALL :build Win32 1.0
    IF ERRORLEVEL 1 EXIT /B 1
    CALL :build x64 2.0
    IF ERRORLEVEL 1 EXIT /B 1
    CALL :build ARM64 3.0
    IF ERRORLEVEL 1 EXIT /B 1
    EXIT /B 0
)

:buildNext
IF "%~1"=="" EXIT /B 0
IF "%~2"=="" (
    ECHO Error: missing version.
    EXIT /B 1
)

CALL :build %1 %2
IF ERRORLEVEL 1 EXIT /B 1

SHIFT
SHIFT
GOTO buildNext

:build
msbuild %slnfilename% -t:Build -p:Configuration=Release -p:Platform=%1 -p:PRODUCT_VERSION=%2
EXIT /B %ERRORLEVEL%
