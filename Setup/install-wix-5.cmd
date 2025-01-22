@CD /D "%~dp0"

@IF EXIST .config\dotnet-tools.json GOTO workspaceready

dotnet new tool-manifest
@IF errorlevel 1 GOTO failed

@:workspaceready

dotnet tool install --local wix --version 5.0.2
