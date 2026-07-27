# Reproducing an x64 to arm64 upgrade problem

## Building a set of installers

- Copy nupkg files of a private build of WiX to `Setup\localNuget\`
- This project is configured for `WiX 8.0.0-build.7`. Modify `Setup\install-wix-tool.cmd` and `Setup\MyMultiArchSetup\MyMultiArchSetup.wixproj` to fix references to point to your WiX build version.
- Open Visual Studio 2026 Developer Command Prompt
- cd to the root of this repository
- Run `buildall.cmd`
- You will find three installers in the `Setup\_out\` directory
  - `MySimpleAppSetup-x86-3.2.11.msi`
  - `MySimpleAppSetup-x64-3.8.22.msi`
  - `MySimpleAppSetup-ARM64-4.1.44.msi`

To build only selected application architectures or to assign other versions, pass
architecture/version pairs to `Apps\build.cmd`, for example:

```bat
Apps\build.cmd Win32 3.2.11 ARM64 4.1.44
```

### If you need more installers

- Collect installers from `Setup\_out`. The directory will be cleaned.
- Run `buildall-additional-releases.cmd`
- Installers x86-3.2.15, x64-3.8.25, and arm64-4.1.45 are generated in `Setup\_bin`.

## How to kaboom

- Pick Arm64 machine
- Start a sandbox to avoid cluttering your machine
- Install `MySimpleAppSetup-x64-3.8.22.msi`
  - It installs 'My Multi Arch App' and launches it
- Install `MySimpleAppSetup-ARM64-4.1.44.msi`
  - It will stop the running 'My Multi Arch App (x64)'
  - and then uninstalls it
  - and then fails with a message "There is a problem with this Windows Installer package. A DLL required for this install to complete could not be run. Contact your support personnel or package vendor."
