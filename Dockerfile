FROM onion/owrt-sdk:latest
MAINTAINER Lazar Demin <lazar@onion.io>

# PKG_NAME: lv_example

# add local feed
COPY ./openwrt/ /root/feed/lv_example/
# add local source code
COPY . /root/source

# add local feed, update feed, install package from custom feed, run defconfig to fix dependencies
RUN echo "src-link custom /root/feed" >> feeds.conf.default && \
    ./scripts/feeds update custom && \
    ./scripts/feeds install lv_example && \
    make defconfig

# compile the package and collect the ipk file
CMD make package/lv_example/download  && \
    make package/lv_example/clean V=s  && \
    make package/lv_example/prepare USE_SOURCE_DIR=/root/source  && \
    make package/lv_example/compile -j1 V=s && \
    find bin/packages/ -name "lv_example*" -exec cp {} /root/source/bin/ \;
