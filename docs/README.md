# Build and Test

## Prerequisites

- CMake 3.21 or newer
- MSYS2 UCRT64 GCC and MinGW make
- Network access on the first configure so CMake can fetch GoogleTest

Install MinGW make from an MSYS2 UCRT64 terminal with:

```sh
pacman -S mingw-w64-ucrt-x86_64-make
```

Ensure `C:\msys64\ucrt64\bin` is on `PATH` so CMake can find `g++` and `mingw32-make`.

## VS Code

CMake Tools is configured by the workspace settings to use MinGW Makefiles and
the `build/mingw` directory. Configure and build the project from the CMake Tools
status bar, then run the discovered tests from the CTest view. GoogleTest is
fetched automatically when `BUILD_TESTING` is enabled.

The `mingw` configure, build, and test presets are also available for command-line
CMake workflows.
