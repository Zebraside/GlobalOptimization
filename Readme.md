# Global Optimization Project

## Build
- Create directory `build`
- `cd build`
- `cmake ..`

## Cmake options
- ENABLE_GUI - enables Qt based UI. OFF by default. (require Qt5 libraries) 

To enable Qt libraries in your build add path to Qt cmake folder in your CMAKE_PREFIX_PATH (ex. `-DCMAKE_PREFIX_PATH=%path_to_qt%/Qt/5.12.6/gcc_64/lib/cmake`)

Note: to generate project for Visual Studio use `cmake -G "Visual Studio 15 2017 Win64 ..`