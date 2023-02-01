#include "src/ypkg-common.h"
#include "src/cmd/ypkg-update.h"
#include "src/inc/ypkg-curl.h"
#include "src/inc/ypkg-srclist.h"

int UpdateCommand(int argc,char** argv){
    
    int ret=0;
    vector<string> src_list=ReadSourcesList(&ret);
    if(ret!=0) return ret;

   
    int len=(src_list).size();    
    
    for(int i=0;i<len;i++){
        printf("%d: %s\n",i+1,((src_list)[i]).c_str());
    }
    //int ret=DownloadFiles((char*)"https://dldir1.qq.com/weixin/Windows/WeChatSetup.exe",(char*)"test.exe",true);
    //printf("%d\n",ret);
    return 0;
}