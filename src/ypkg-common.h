#include <stdio.h>
#include <string.h>
#include <string>
#include <vector>
#include "src/inc/ypkg-config.h"
#include "src/ypkg-version.h"
#include "src/cmd/ypkg-help.h"
#include "src/cmd/ypkg-update.h"
#include "src/cmd/ypkg-config.h"


#ifndef YPKG_COMMON_H

using namespace std;

typedef int (*command)(int argc,char** argv);

struct CommandObject
{
    const char* long_cmd;
    const char* short_cmd;
    const char* description;
    command delegate;
};

int ShowVersionCommand(int argc,char** argv);

const struct CommandObject cmds[]={
        {"help", "h", "show help message", ShowHelpCommand},//+
        {"config","cf","show config",ConfigCommand},//*
        {"install","i","install or upgrade packages via network",NULL},
        {"download","dn","download packages via network",NULL},
        {"search","s","search packages",NULL},
        {"info","nfo","display package info",NULL},
        {"update","up","update package catalogs via network",UpdateCommand},//*
        {"remove","rm","remove packages",NULL},
        {"purge","rf","remove packages and their datas",NULL},
        {"clean","cl","clear package caches",NULL},
        {"depend","dp","show package dependencies",NULL},
        {"installer","pi","invoke package installer of system if any",NULL},
        {"manage","pm","invoke package manager of system if any ",NULL},
        {"version", "v", "show ypkg version", ShowVersionCommand},//+
    };

vector<char*> StrSplit(const string& str, const string& delim);

char* StringToCharPointer(string s);

void StringReplace(string&s1,const string&s2,const string&s3);

#define YPKG_COMMON_H

#endif
