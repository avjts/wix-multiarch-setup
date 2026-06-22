@CD /D "%~dp0"

@IF EXIST .config\dotnet-tools.json GOTO workspaceready
@IF EXIST .\dotnet-tools.json GOTO workspaceready

dotnet new tool-manifest
@IF errorlevel 1 GOTO failed

@:workspaceready

dotnet tool install --local wix --version 7.0.0
dotnet tool restore
