#include "src/inc/ypkg-config.h"
#include "src/inc/ypkg-srclist.h"


vector<string> ReadSourcesList(int* code)
{
    FILE *fp=fopen(SOURCES_LIST,"rb");
    if(!fp){
        printf("%s\n","failed to lock sources.list");
        *code=-1;
        return vector<string>();
    }

    int line=5;
    char buf[1024];
    int len=0;

    char slist[4096]={0};
   

    while(fgets(buf,line,fp)!= NULL)
    {
        len=strlen(buf);
        strcat(slist,buf);
    }

    vector<string> alist=split(slist,"\n");
    code=0;
    return alist;

}

SrcRepoType String2SrcRepoType(const char* type)
{
    if(strcmp("deb",type)==0) return SrcRepoType::Debian;
    if(strcmp("ubu",type)==0) return SrcRepoType::Ubuntu;
    if(strcmp("soft",type)==0) return SrcRepoType::MainOnly;
    if(strcmp("main",type)==0) return SrcRepoType::MainOnly;
    else return SrcRepoType::Unknown;
}

struct SrcConfig SourceToConfig(char* conf)
{
    vector<string> sconf= split(conf," ");
    try
    {
        SrcRepoType type=String2SrcRepoType(sconf[0].c_str());
        char* url=(char*)sconf[1].c_str();
        char url2[sizeof(url)*(strlen(url)+1)]={0};
        strcat(url2,url);
        strcat(url2,"\0");
        char* name=(char*)sconf[2].c_str();
        char name2[sizeof(name)*(strlen(name)+1)]={0};
        strcat(name2,name);
        strcat(name2,"\0");

        struct SrcConfig confObj=
        {
            type,
            url2,
            name2
        };
        return confObj;
    }
    catch(const std::exception& e)
    {
        printf("ERROR: %s\n",e.what());
        return {SrcRepoType::Unknown,"CONFIG ERROR","ERROR"};
    }
    
}