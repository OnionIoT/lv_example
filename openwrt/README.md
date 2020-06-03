# How to compile lv_example using OpenWRT build system

What follows are instructions on compiling lv_example package for Omega2 platform from source code in github repo specified by `PKG_SOURCE_URL` variable in the `Makefile` in this directory.

This might take some time and be work intensive!

**A quicker option to get this code compiled for the Omega2 Dash is to use the OpenWRT SDK with Docker. It's really simplified by a script we've made available. See more details [here](https://github.com/OnionIoT/lv_example#using-docker-to-compile-for-the-omega2-dash).**

## The Instructions

First add this makefile to the Onion feed in the build system:

```
# assuming you're in the build system top directory
mkdir feeds/onion/lv_example
cp <PATH TO THIS REPO>/openwrt/Makefile feeds/onion/lv_example/
```

Then install the package to the build system:

```
# assuming you're in the build system top directory
./scripts/feeds update onion
./scripts/feeds install lv_example
```

Then, you'll need to adjust the build system to enable the `lv_example` package.
Run `make menuconfig`, and go to Onion -> Utilities and select `lv_example` for compilation.

Finally build the package:

```
make package/lv_example/compile V=99
```

The output ipk file will be at `bin/packages/mipsel_24kc/onion/` it will be named something like `lv_example_0.0.1-1_mipsel_24kc.ipk`

Installing this package on an Omega2 device will install the compiled binary to `/usr/bin/lv_example`

# To build the package from local source

During development it is easier to work off a local copy of the source code.

First, run the regular make command for the package:

```
make package/lv_example/compile V=99
```

Then to switch to using the local source code

```
make package/lv_example/clean
make package/lv_example/prepare USE_SOURCE_DIR=<PATH TO lv_example CLONE DIRECTORY> V=s
make package/lv_example/compile V=99
```

On successful compilation, it will produce a file `bin/output` in the `lv_example` directory.

## To go back to using git repo

To move back to using the git repo to build the package:

```
rm -rf dl/lv_example*
make package/lv_example/clean
```

Any future compilations will download the source from the git repo and use that for compilation.
