@SET x86version=%1
@IF "x86version"=="" SET x86version=1.0
@SET x64version=%2
@IF "x64version"=="" SET x64version=2.0
@SET ARM64version=%3
@IF "ARM64version"=="" SET ARM64version=3.0

@CD /D "%~dp0"

msbuild MyMultiArchApp.sln -t:Build -p:Configuration=Release -p:Platform=Win32 -p:PRODUCT_VERSION=%x86version%

msbuild MyMultiArchApp.sln -t:Build -p:Configuration=Release -p:Platform=x64 -p:PRODUCT_VERSION=%x64version%

msbuild MyMultiArchApp.sln -t:Build -p:Configuration=Release -p:Platform=ARM64 -p:PRODUCT_VERSION=%ARM64version%
