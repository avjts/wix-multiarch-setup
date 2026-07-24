@ECHO OFF
SETLOCAL
PUSHD "%~dp0"
SET "BASEDIR=%cd%"

FOR /D %%d IN (Debug-* Release-*) DO (
	CALL :deletefolder %%d
)

FOR /D %%d IN (MyMultiArchApp migrate) DO (
	CALL :deletefolder %%d\ARM64
	CALL :deletefolder %%d\Win32
	CALL :deletefolder %%d\x64
)


IF "%1"=="all" CALL :deletefolder .vs
IF "%1"=="all" CALL :delfile MyMultiArchApp\App.aps
IF "%1"=="all" CALL :delfile MyMultiArchApp\MyMultiArchApp.vcxproj.user
IF "%1"=="all" CALL :delfile migrate\migrate.vcxproj.user

POPD
GOTO :EOF


:deletefolder
IF NOT EXIST "%BASEDIR%\%1\" EXIT /B
ECHO ^> rmdir /S /Q "%BASEDIR%\%1"
rmdir /S /Q "%BASEDIR%\%1"
EXIT /B

:delfile
IF NOT EXIST "%BASEDIR%\%1" EXIT /B
ECHO ^> del "%BASEDIR%\%1"
del "%BASEDIR%\%1"
EXIT /B

