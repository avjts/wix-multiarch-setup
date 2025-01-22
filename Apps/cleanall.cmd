@ECHO OFF
SETLOCAL
@CD /D "%~dp0"
SET "BASEDIR=%cd%"

FOR /D %%d IN (Debug-* Release-*) DO (
	CALL :deletefolder %%d
)

CALL :deletefolder MyMultiArchApp\ARM64
CALL :deletefolder MyMultiArchApp\Win32
CALL :deletefolder MyMultiArchApp\x64
CALL :delfile MyMultiArchApp\App.aps
CALL :delfile MyMultiArchApp\MyMultiArchApp.wixproj.user

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

