#include "src/ypkg-common.h"
#include "src/cmd/ypkg-update.h"
#include "src/inc/ypkg-curl.h"
#include "src/inc/ypkg-srclist.h"
#include "src/conf/ypkg-apt-config.h"
#include "src/inc/ypkg-lzma.h"
#include "src/inc/ypkg-sqlite.h"

int UpdateCommand(int argc,char** argv){
    
    int ret=0;
    vector<char*> src_list=ReadSourcesList(&ret);
    if(ret!=0) return ret;

   
    int len=(src_list).size(); 

    int i=0;   
    int process=0;
    vector<AptSource> plists;
    
    for(i=0;i<len;i++){
        process++;

        char* conf=(src_list)[i];
        struct SrcConfig sconf=SourceToConfig(conf);
        string release_url=ParseConfigToURL(sconf.baseUrl,sconf.codeName,StringToCharPointer("Release"));

        string fn=ParseURLAsFileName(release_url);

        string release_file=SOURCE_CACHE_DIR;
        release_file+=fn;
        long size=0;
        long p=DownloadFiles(StringToCharPointer(release_url),StringToCharPointer(release_file),&size,true);
        if(p != 200)
        {
            printf("Hit:%d %s %s %s \n",process,sconf.baseUrl,sconf.codeName,"Release");
        }
        else
        {
            printf("Get:%d %s %s %s [%ld Bytes]\n",process,sconf.baseUrl,sconf.codeName,"Release",size);
            DownloadFiles(StringToCharPointer(release_url),StringToCharPointer(release_file),&size,false);   

            {
                char* repos=ParseConfigToAptConfigRepoStr(sconf);

                vector<char*> rlist=StrSplit(repos," ");
                int rlen=(rlist).size();

                for(int j=0;j<rlen;j++)
                {
                    process++;
                    char* repo=rlist[j];
                    string rfn=repo;
                    rfn+="/";
                    rfn+="binary-amd64/Packages.xz";
                    string plist_url=ParseConfigToURL(sconf.baseUrl,sconf.codeName,StringToCharPointer(rfn));
                    
                    string fn=ParseURLAsFileName(plist_url);

                    string plist_file=SOURCE_CACHE_DIR;
                    plist_file+=fn;
                    long size=0;
                    long p=DownloadFiles(StringToCharPointer(plist_url),StringToCharPointer(plist_file),&size,true);
                    if(p!=200)
                    {
                        printf("Hit:%d %s %s/%s %s \n",process,sconf.baseUrl,sconf.codeName,repo,"Packages.xz");
                    }
                    else
                    {
                        printf("Get:%d %s %s/%s %s [%ld Bytes]\n",process,sconf.baseUrl,sconf.codeName,repo,"Packages.xz",size);
                        DownloadFiles(StringToCharPointer(plist_url),StringToCharPointer(plist_file),&size,false); 
                        AptSource src=  {.config=sconf,.source=plist_url};
                        plists.push_back(src);        
                    }
                }
            }
         
        }
    }

    for(i=0;i<plists.size();i++)
    {
        string u=ParseURLAsFileName(plists[i].source);

        string xz=SOURCE_CACHE_DIR;
        xz+=u;

        string p=SOURCE_CACHE_DIR;
        p+=u;

        StringReplace(p,".xz","");

        unxz(StringToCharPointer(xz),StringToCharPointer(p));
    }
    
    return 0;
}