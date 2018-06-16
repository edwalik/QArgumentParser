    Please do not use this unless you are working with Qt already and do not want to link to boost-program-options

# QArgumentParser
[![License](https://img.shields.io/badge/license-LGPL%203.0-blue.svg?style=flat)](https://github.com/glClear/QGameBoy/blob/master/LICENSE)
[![Binaries](https://img.shields.io/badge/OS-windows%2Flinux%2FmacOSX-blue.svg)](https://github.com/glClear/QGameBoy/releases)
[![Version](https://img.shields.io/badge/version-v0.1-blue.svg)](https://github.com/glClear/QGameBoy/releases/latest)
[![Qt-Framework](https://img.shields.io/badge/Qt-Core-green.svg)](http://qt.io)
[![Builds correctly](https://img.shields.io/badge/build-passing-green.svg)]()

## Content
- [Features](#features)
- [Build](#build)
- [Using the code](#code)

## <a name="features"></a>Features
- Variable option indicator (default: dash)
- Named arguments
- Argument validation

## <a name="build"></a>Build
If you downloaded the entire Qt SDK with QtCreator, you might just open the project file (`*.pro`) instead of using the terminal.

### Library
Before doing all those steps, make sure that qmake and the compiler you are going to use are added to the `PATH`
environment variable.

1. Go to the root directory of QArgumentParser where `QArgumentParser.pro` is located in.
2. If you have not already, open a terminal/cmd at this location.

```
$ qmake
$ Project MESSAGE: Library path is {path}
$ cd {path}
$ qmake -spec {spec} "CONFIG+=release" -o Makefile ../../../QArgumentParser.pro
$ make
```
#### Explanation
1. We execute qmake the first time in order to get the estimated path to our library file.
2. We cd into the directory that will contain our library file.
3. We execute qmake again in order to generate a Makefile for the release configuration.
4. We finally use make/ming32-make/nmake to compile the code.

#### {spec}
The spec must be a valid pre-defined qmake configuration. Some examples:
* linux-g++
* win32-g++
* win32-msvc

#### Static library
It is possible to compile QArgumentParser statically by changing the call to qmake:
```
$ qmake -spec {spec} "CONFIG+=static" "CONFIG+=release" -o Makefile ../../../QArgumentParser.pro
```

#### /!\ Attention /!\
When using the MSVC compiler, you might need to execute Microsoft's batch file at `C:\Program Files (x86)\Microsoft Visual Studio <version>\VC\vcvarsall.bat`
before running qmake.

### Example
To build the example, do the following steps:

1. Go to the directory of the QArgumentParserExample (`QArgumentParser/examples/`).
2. If you have not already, open a terminal/cmd at this location.
```
$ qmake
$ Project MESSAGE: Library path is {path}
$ cd {path}
$ qmake -spec {spec} "CONFIG+=release" -o Makefile ../../../QArgumentParserExample.pro
$ make
```
As we use the `platforms.pri` submodule to standardize our path conventions, the example can link to the correct library automatically!

## <a name="code"></a>Using the code
A complete example can be found [here](https://github.com/NicolasKogler/QArgumentParser/blob/master/examples/main.cpp).
