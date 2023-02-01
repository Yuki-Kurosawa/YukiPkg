#include "src/ypkg-common.h"
#include "src/inc/ypkg-curl.h"

static int ProgressCallback(void *clientp, double dltotal, double dlnow, double ultotal, double ulnow)  
{  
    if ( dltotal > -0.1 && dltotal < 0.1 )  
        return 0;  
    double nPos = (dlnow/dltotal)*100;   

	//printf("%.0lf / %.0lf (%.2lf %%)\r",dlnow,dltotal,nPos);
    return 0;  
}  

int DownloadFiles(char* url,char* filename,bool dryrun)
{
	try
	{
		CURLcode res = curl_global_init(CURL_GLOBAL_ALL);
		if (CURLE_OK != res)
		{
			cout << "curl init failed" << endl;
			return -1;
		}

		CURL* pCurl = NULL;
		pCurl = curl_easy_init();

		if (NULL == pCurl)
		{
			cout << "Init CURL failed..." << endl;
			return -1;
		}


		FILE *fp=fopen(filename,"wb");

		if(!fp)
		{
			cout<<"open file failed";
			return -1;
		}

		curl_easy_setopt(pCurl, CURLOPT_SSL_VERIFYPEER, 0L);//ignore ssl/tls certificate errors

		curl_easy_setopt(pCurl, CURLOPT_SSL_VERIFYHOST, 0L);

		curl_easy_setopt(pCurl, CURLOPT_TIMEOUT, 0L);//request time out
		curl_easy_setopt(pCurl, CURLOPT_CONNECTTIMEOUT, 10L); //connect time out
		curl_easy_setopt(pCurl, CURLOPT_FOLLOWLOCATION, 1L);//allow 30x request
		curl_easy_setopt(pCurl, CURLOPT_HEADER, 0L);  //write header to output
		curl_easy_setopt(pCurl, CURLOPT_WRITEDATA, fp);  //response callback

		if(dryrun)
		{
			curl_easy_setopt(pCurl, CURLOPT_CUSTOMREQUEST,"HEAD");	
			curl_easy_setopt(pCurl, CURLOPT_NOBODY, 1L);	
		}	

		curl_easy_setopt(pCurl, CURLOPT_NOSIGNAL, 1L); //
		curl_easy_setopt(pCurl, CURLOPT_VERBOSE, 0L); //
		curl_easy_setopt(pCurl, CURLOPT_URL, url); //
		curl_easy_setopt(pCurl, CURLOPT_NOPROGRESS, 0);
		curl_easy_setopt(pCurl, CURLOPT_PROGRESSFUNCTION, ProgressCallback); 

		curl_slist* pList = NULL;

		//公共头
		pList = curl_slist_append(pList, "Accept-Encoding:");
		pList = curl_slist_append(pList, "Accept-Language:zh-CN,zh;q=0.8");
		pList = curl_slist_append(pList, "Connection:keep-alive");

		curl_easy_setopt(pCurl, CURLOPT_HTTPHEADER, pList);

		res = curl_easy_perform(pCurl);  //执行请求

		long res_code = 0;
		res = curl_easy_getinfo(pCurl, CURLINFO_RESPONSE_CODE, &res_code);

		//printf("%ld\n",res_code);
		
		curl_slist_free_all(pList);
		curl_easy_cleanup(pCurl);
		fclose(fp);

		return (int)res_code;
	}
	catch (exception& e) {
		printf("%s",e.what());
		return -1;
	}
}
