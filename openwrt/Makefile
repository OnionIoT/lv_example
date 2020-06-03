# Copyright (C) 2019 Onion Corporation
#
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk
PKG_NAME:=lv_example
PKG_VERSION:=0.0.1
PKG_RELEASE:=1

PKG_SOURCE_PROTO:=git
PKG_SOURCE_VERSION:=HEAD  # latest commit from master branch
PKG_SOURCE_URL:=https://github.com/OnionIoT/lv_example.git
PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)-$(PKG_VERSION)

include $(INCLUDE_DIR)/package.mk


# application package
define Package/lv_example
	SECTION:=onion
	CATEGORY:=Onion
	SUBMENU:=Utilities
	TITLE:=A template for Omega2 Dash programs using the LittleV Graphics Library
	DEPENDS:=
endef

define Package/lv_example/description
A template for Omega2 Dash programs using the LittleV Graphics Library
endef


TARGET_CFLAGS += -I$(STAGING_DIR)/usr/include
TARGET_LDFLAGS += -L$(STAGING_DIR)/usr/lib

define Build/Compile
	$(MAKE) -C $(PKG_BUILD_DIR)/ \
	CC="$(TARGET_CC)" \
	CFLAGS="$(TARGET_CFLAGS)" \
	LDFLAGS="$(TARGET_LDFLAGS)"
endef

define Package/lv_example/install
	$(INSTALL_DIR) $(1)/usr/bin
	# install the binary
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/bin/output $(1)/usr/bin/lv_example
endef

$(eval $(call BuildPackage,$(PKG_NAME)))
