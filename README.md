# lv_example
A template for Omega2 Dash programs using the LittleV Graphics Library

Out of the box it supports:

* All configuration (`lv_conf.h` and `lv_drv_conf.h`) required for:
    * The Linux Framebuffer - will draw to the Omega2 Dash display
    * The XPT7603 touch input device on the Omega2 Dash
* A small demo (provided by `main.c`)
* A script to cross compile the code for the Omega2 Dash (using Docker and the OpenWRT SDK)
* A makefile and instructions to build it as an OpenWRT package (see `openwrt` directory)

## Using Docker to Compile for the Omega2 Dash

**A quick and easy method for cross-compiling this code for the Omega2 Dash**

It's possible to use the OpenWRT SDK in a Docker container to compile this code for the Omega2 Dash. The first time you do this might take a few minutes since image files will need to be downloaded. Afterwards, the compilation will be pretty quick.

Make sure you have [Docker installed](https://docs.docker.com/get-docker/), then run:

```
sh compile.sh
```

This will use the OpenWRT SDK in a Docker container to compile the code in your local copy of this repo.

The output, a binary file and an ipk package will be in the `bin` directory.

### Binary File

The binary file can be [copied to the Omega2](http://docs.onion.io/omega2-docs/transferring-files.html) and then executed. Say you copied it to `/root` on the Omega2, it can be executed by running `/root/output`.

### IPK Package File

The ipk file is an OpenWRT software package. It can be [copied to the Omega2](http://docs.onion.io/omega2-docs/transferring-files.html) and used to install the `lv_example` package.
Let's say it was copied to `/tmp/lv_example_0.0.1-1_mipsel_24kc.ipk`, it can be installed by running:

```
cd /tmp
opkg install lv_example_0.0.1-1_mipsel_24kc.ipk
```

The `lv_example` binary will be installed to `/usr/bin`. You can then execute it from anywhere just by running:

```
lv_example
```

> All of the package details are defined in the [OpenWRT Makefile](./openwrt/Makefile), including the package name, installation directory, and more


## Modifying the Template

Feel free to use this as a starting point for your own UI project on the Omega2 Dash. That's exactly what this repo is intended for!

### Using Libraries

If you end up using additional libraries in your project, you'll need to make a few modifications in the [OpenWRT Makefile](./openwrt/Makefile) in order to successfully compile the code using the `compile.sh` script.

All changes to be made in the `openwrt/Makefile` file:

1. Add the package name of the library to the dependencies of this package
2. Add the library to the linking flags used for compilation.

#### An Example

Let's say your UI project is based on the code in this repo and uses `libugpio` to toggle the GPIOs when buttons are pressed on the touchscreen.

In `openwrt/Makefile`, find the [line that defines the DEPENDS for the package](./openwrt/Makefile#L29). Add a `+` and `libugpio`, the name of the package:

```
DEPENDS:=+libugpio
```

> If your updated code has more than one dependency, it would look like this `DEPENDS:=+libugpio +otherdependency`

Then, find the [line where `TARGET_LDFLAGS`, the linker flags to be used compilation](./openwrt/Makefile#L38). Add `-l` and the library name:

```
TARGET_LDFLAGS += -L$(STAGING_DIR)/usr/lib -lugpio
```

### Changing the Package Name

If you build your own software package based on the template, it would make sense to change the package name.

To change the package name, find and replace the text `lv_example` with your given package name in the following files:

* `Dockerfile`
* `openwrt/Makefile`

Note that changing the [install definition in the OpenWRT makefile](./openwrt/Makefile#L50) will change where the binary will be installed on your Omega2 Dash device!

> Learn more about OpenWRT package makefiles here: https://openwrt.org/docs/guide-developer/packages
