#pragma once

// WINVER & _WIN32_WINNT & NTDDI_VERSION: target Windows 10 2004
// required to run pnputil with /remove-device and /scan-devices options
#ifndef WINVER
#define WINVER 0x0A00
#endif

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0A00
#endif

#ifndef NTDDI_VERSION
#define NTDDI_VERSION 0x0A000008
#endif

#ifndef _WIN32_IE        // Specifies that the minimum required platform is Internet Explorer 6.0 SP3.
#define _WIN32_IE 0x0603 // Change this to the appropriate value to target other versions of IE.
#endif

#ifndef _WIN32_MSI     // Specifies that the minimum required MSI version is MSI 3.1
#define _WIN32_MSI 405 // Change this to the appropriate value to target other versions of MSI.
#endif
