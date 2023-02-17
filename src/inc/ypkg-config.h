#ifndef YPKG_CONFIG_H
#define YPKG_CONFIG_H

#if DEBUG
    #define SOURCES_LIST "./etc/ypkg/sources.list"
    #define SOURCE_CACHE_DIR "./var/lib/ypkg/lists/"
    #define TMP_DIR "./var/lib/ypkg/tmp/"
    #define PACKAGE_CACHE_DIR "./var/lib/ypkg/pkgs/"
    #define PACKAGE_INDEX "./var/lib/ypkg/pkgcache.bin"
#else
    #define SOURCES_LIST "/etc/ypkg/sources.list"
    #define SOURCE_CACHE_DIR "/var/lib/ypkg/lists/"
    #define TMP_DIR "/var/lib/ypkg/tmp/"
    #define PACKAGE_CACHE_DIR "/var/lib/ypkg/pkgs/"
    #define PACKAGE_INDEX "/var/lib/ypkg/pkgcache.bin"
#endif

#define DEBIAN_CONFIG_STR "main contrib non-free"
#define UBUNTU_CONFIG_STR "main universe restricted multiverse"
#define MAINONLY_CONFIG_STR "main"

#endif