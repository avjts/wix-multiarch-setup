
# How to build

- Open Visual Studio 2022 Developer Command Prompt
- cd to the root of this repository
- run `buildall.cmd`
- You will find three installers in the `Setup\_out\` directory
  - `MySimpleAppSetup-x86-3.2.11.msi`
  - `MySimpleAppSetup-x64-3.8.22.msi`
  - `MySimpleAppSetup-ARM64-4.1.44.msi`

# How to kaboom

- Pick Arm64 machine
- Start sandbox to avoid cluttering your machine
- Install `MySimpleAppSetup-x64-3.8.22.msi`
  - It will install 'My Multi Arch App' and autostarts it
- Install `MySimpleAppSetup-ARM64-4.1.44.msi`
  - It will stop the running 'My Multi Arch App (x64)'
  - and then uninstalls it
  - and then fails with a message "There is a problem with this Windows Installer package. A DLL required for this install to complete could not be run. Contact your support personnel or package vendor."
