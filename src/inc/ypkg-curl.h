#ifndef YPKG_CURL_H
#include <curl/curl.h>
#include <iostream>

#define YPKG_CURL_H

long DownloadFiles(char* url,char* filename,long* size,bool dryrun=false);

#endif