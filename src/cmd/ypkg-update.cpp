#include "src/ypkg-common.h"
#include "src/cmd/ypkg-update.h"
#include "src/inc/ypkg-curl.h"
#include "src/inc/ypkg-srclist.h"
#include "src/conf/ypkg-apt-config.h"

int UpdateCommand(int argc,char** argv){
    
    int ret=0;
    vector<char*> src_list=ReadSourcesList(&ret);
    if(ret!=0) return ret;

   
    int len=(src_list).size();    
    
    for(int i=0;i<len;i++){
        char* conf=(src_list)[i];
        struct SrcConfig sconf=SourceToConfig(conf);
        string release_url=sconf.baseUrl;
        release_url+="/dists/";
        release_url+=sconf.codeName;
        release_url+="/Release";

        string fn=ParseURLAsFileName(release_url);

        string release_file=SOURCE_CACHE_DIR;
        release_file+=fn;
        long size=0;
        long p=DownloadFiles(StringToCharPointer(release_url),StringToCharPointer(release_file),&size,true);
        if(p!=200)
        {
            printf("Hit:%d %s %s %s \n",i+1,sconf.baseUrl,sconf.codeName,"Release");
        }
        else
        {
            printf("Get:%d %s %s %s [%ld Bytes]\n",i+1,sconf.baseUrl,sconf.codeName,"Release",size);
            DownloadFiles(StringToCharPointer(release_url),StringToCharPointer(release_file),&size,false);            
        }
    }
    return 0;
}