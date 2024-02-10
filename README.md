# xy

A simple command runner for any project/workspace, designed to be very fast and reliable.

Stores custom commands in default `xy.ini` file at the root of the project.

## `xy` CLI Options

A number of options are common in every fy-tool invocation:

```
Usage : xy [cmd] [options]

Options:
   --quiet, -q              : Quiet operation, do not output messages (default false)
   --version, -v            : Display xy version
   --help, -h               : Display help message
```

## Examples
Coming soon!

## Prerequisites

`xy` is primarily developed on Windows but Linux & MacOS builds are supported too.
* CMake or Any C Compiler

## Building

``xy`` uses cmake and also supports a simple build scheme:

### CMake
1. Run;
```
cmake -B "./build"
      -DCMAKE_CXX_COMPILER=COMP
      -DCMAKE_C_COMPILER=COMP
      -DCMAKE_BUILD_TYPE=Release
```
Replace `COMP` with either `gcc`, `clang` or `cl`

2. Build;
```
cmake --build "./build" --config Release
```

### MinGW `gcc`
* Download and install MinGW `gcc` Compiler
* run `./build.bat`

## Development and contributing
Feel free to send pull requests and raise issues.
