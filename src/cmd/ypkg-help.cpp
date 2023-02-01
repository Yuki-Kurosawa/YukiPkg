#include "src/ypkg-common.h"
#include "src/cmd/ypkg-help.h"

int ShowHelpCommand(int argc,char** argv){
    printf("%s\n","ypkg command [args...]");
    printf("%s\n","");
    printf("%s\n","Command List:");

    int cmdlen=sizeof(cmds)/sizeof(CommandObject);
    for(int index=0;index<cmdlen;index++){
        if(cmds[index].short_cmd)
        {
            printf("%s - %s (short command: %s)\n",cmds[index].long_cmd,cmds[index].description,cmds[index].short_cmd);
        }
        else
        {
            printf("%s - %s\n",cmds[index].long_cmd,cmds[index].description);
        }
    }
    return 0;
}