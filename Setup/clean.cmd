@ECHO OFF
SETLOCAL
@CD /D "%~dp0"
SET "BASEDIR=%cd%"

FOR /D %%d IN (Debug-* Release-*) DO (
	CALL :deletefolder %%d
)

IF "%1"=="all" CALL :deletefolder .vs
CALL :deletefolder .config
CALL :deletefolder .wix
CALL :deletefolder _bin
CALL :deletefolder _out
CALL :deletefolder global-packages
CALL :deletefolder packages
CALL :deletefolder MyMultiArchSetup\.wix
CALL :deletefolder MyMultiArchSetup\obj
CALL :deletefolder CppCustomActions\_bin
CALL :deletefolder CppCustomActions\_obj
CALL :deletefolder CSharpCustomActions\obj
CALL :delfile dotnet-tools.json
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

