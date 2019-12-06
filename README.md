# lv_example
A template for Omega2 Dash programs using the LittleV Graphics Library

Out of the box it supports:

* All configuration (`lv_conf.h` and `lv_drv_conf.h`) required for:
    * The Linux Framebuffer - will draw to the Omega2 Dash display 
    * The XPT7603 touch input device on the Omega2 Dash
* A makefile and instructions to build it as an OpenWRT package (see `openwrt` directory)
* A small demo (provided by `main.c`)
