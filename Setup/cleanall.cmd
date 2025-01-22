@ECHO OFF
SETLOCAL
@CD /D "%~dp0"
SET "BASEDIR=%cd%"

FOR /D %%d IN (Debug-* Release-*) DO (
	CALL :deletefolder %%d
)

CALL :deletefolder _bin
CALL :deletefolder _out
CALL :deletefolder global-packages
CALL :deletefolder MyMultiArchSetup\.wix
CALL :deletefolder MyMultiArchSetup\obj

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

