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