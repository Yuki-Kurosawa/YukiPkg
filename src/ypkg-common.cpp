#include "src/ypkg-common.h"

int ShowVersionCommand(int argc,char** argv)
{
    printf("ypkg %d.%d.%d%s\n",MAJOR,MINOR,REV,SUFFIX);
    return 0;
}

vector<char*> StrSplit(const string& str, const string& delim) 
{  
    vector<char*> res;  
    if("" == str) return res;  
    //先将要切割的字符串从string类型转换为char*类型  
    char * strs = new char[str.length() + 1] ; //不要忘了  
    strcpy(strs, str.c_str());   
 
    char * d = new char[delim.length() + 1];  
    strcpy(d, delim.c_str());  
 
    char *p = strtok(strs, d);  
    while(p) {  
        string s = p; //分割得到的字符串转换为string类型 
        char* ret=StringToCharPointer(s);  
        res.push_back(ret); //存入结果数组  
        p = strtok(NULL, d);  
    }  
 
    return res;  
}

char* StringToCharPointer(string s)
{
    char* ret=new char[s.length() + 1];
    strcpy(ret, s.c_str());  
    return ret;
}