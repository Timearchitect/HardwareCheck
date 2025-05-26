@echo off
setlocal

set PROJECT_PATH=%~dp0
set UBT="C:\Program Files\Epic Games\UE_5.5\Engine\Binaries\DotNET\UnrealBuildTool\UnrealBuildTool.exe"
set UPROJECT="%PROJECT_PATH%HardwareCheck.uproject"

echo Generating project files for: %UPROJECT%
%UBT% -projectfiles -project=%UPROJECT% -game -engine

pause