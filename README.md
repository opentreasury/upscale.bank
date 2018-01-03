# Upscale Coin

This is the reference code for [UPSACLECOIN](https://upscalebank.org) UPSCALE COIN protocol.

Copyright (c) 2017 The Upscale Bank Project.

[![Codacy Badge](https://api.codacy.com/project/badge/Grade/4875edfcc7d743e8b86dfaa7ea1f8898)](https://www.codacy.com/app/upscaletech/upscale.bank?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=upscaletech/upscale.bank&amp;utm_campaign=Badge_Grade)


## Development Resources

-  Web: [upscalebank.org](https://upsscalebank.org)
-  Forum: [forum.upscalebank.org](https://forum.upscalebank.org)
-  Mail: [dev@upscalebank.org](mailto:dev@upscalebank.org)
-  Github: [https://github.com/upscaletech/upscale.bank](https://github.com/upscaletech/upscale.bank)
-  IRC/Chat: [upscalcoin.slack.com](https://upscalecoin.slack.com)

## Vulnerability response

- Our [Vulnerability Response Process](https://github.com/upscaltech/meta/blob/master/VULNERABILITY_RESPONSE_PROCESS.md) encourages responsible disclosure
- We are also available via [HackerOne](https://hackerone.com/monero)
 




## Building UPSCALE COIN 

### On *nix

Dependencies: GCC 4.7.3 or later, CMake 2.8.6 or later, and Boost 1.55.

You may download them from:

* http://gcc.gnu.org/
* http://www.cmake.org/
* http://www.boost.org/
* Alternatively, it may be possible to install them using a package manager.

To build, change to a directory where this file is located, and run `make`. The resulting executables can be found in `build/release/src`.

**Advanced options:**

* Parallel build: run `make -j<number of threads>` instead of `make`.
* Debug build: run `make build-debug`.
* Test suite: run `make test-release` to run tests in addition to building. Running `make test-debug` will do the same to the debug version.
* Building with Clang: it may be possible to use Clang instead of GCC, but this may not work everywhere. To build, run `export CC=clang CXX=clang++` before running `make`.

### On Windows
Dependencies: MSVC 2013 or later, CMake 2.8.6 or later, and Boost 1.55. You may download them from:

* http://www.microsoft.com/
* http://www.cmake.org/
* http://www.boost.org/

To build, change to a directory where this file is located, and run theas commands: 
```
mkdir build
cd build
cmake -G "Visual Studio 12 Win64" ..
```

And then do Build.
Good luck!
