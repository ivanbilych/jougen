# jougen - journey generator

Work in progress, for now nothing to show :D

## requirements
I'm using Ubuntu 15.04. Install all required stuff with
```
sudo apt-get install qtcreator cmake
```

## build
To build project with cmake use this commands:
```
mkdir build; cd build
cmake ..
make
```
To build with debug prints add `-DDEBUG=ON` to `cmake`. You can add `-DDEBUG_LEVEL=<0..5>` for different debug prints and `-DENABLE_TESTS=ON` to build test application. `PRINT_DEBUG_POSITION=ON` will print even more information about current debug print.

To build with QtCreator open `jougen.pro` project file and build.

## run
To start program run a `jougen` binary. You can load `default.json` file to see some initial stuff.
