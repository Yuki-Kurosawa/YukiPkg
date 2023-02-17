#ifndef YPKG_APTCONFIG_H
#define YPKG_APTCONFIG_H

enum SrcRepoType
{
    Unknown=0,
    Debian=1,
    Ubuntu=2,
    MainOnly=3
};

struct SrcConfig
{
    SrcRepoType repoType;
    char* baseUrl;
    char* codeName;
};


#endif