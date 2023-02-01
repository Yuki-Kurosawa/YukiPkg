#include "src/ypkg-common.h"
#include "src/ypkg-parser.h"

int ParseCommand(int argc,char** argv)
{
    if(argc==1)
    {
        char* help[]={{(char*)"help"}};
        return ShowHelpCommand(1,help);
    }

    int cmdlen=sizeof(cmds)/sizeof(CommandObject);

    int cmdindex=0;
    char* cmd=argv[1];
    argv++;
    argc--;

    while(cmdindex < cmdlen)
    {
        if(strcmp(cmd,cmds[cmdindex].long_cmd)==0 ||
         (cmds[cmdindex].short_cmd && strcmp(cmd,cmds[cmdindex].short_cmd)==0)
         )
        {
            if(cmds[cmdindex].delegate)
            {
                return cmds[cmdindex].delegate(argc,argv);
            }
            else
            {
                printf("Command[%s] is not declared\n",cmds[cmdindex].long_cmd);
                return -1;
            }
        }
        cmdindex++;
    }

    printf("Command [%s] is not usable.\n",cmd);

    return -1;
}