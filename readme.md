# 2b-utils

Interface library and remote operation utilities for the [E-Stim Systems 2B](https://store.e-stim.co.uk/index.php?main_page=index&cPath=23_24) powerbox.

## Disclaimer

This is relatively well tested, however perfect function is not guaranteed.

:warning: Use with caution.

## Building

1. Install [CMake](https://cmake.org/) and [Conan](https://conan.io/)
2. `conan remote add bincrafters https://api.bintray.com/conan/bincrafters/public-conan`
3. `mkdir build`
4. `cmake -DCMAKE_BUILD_TYPE=Release /path/to/src` (the first time will take a long time due to the amount of Boost modular dependencies)
5. `cmake --build .`
