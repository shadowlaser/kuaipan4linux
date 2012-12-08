

#include <curl/curl.h>
//#include <curl/types.h>  
#include <curl/easy.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
//const char oauth_nonce
#include "kuaipan.h"
//#include "cJSON.h"


int main(int argc, char *argv[])  
{  
  char consumer_key[]="xcRFTuyppHYMbmk4";
  char consumer_secret[]="h80Jf75D0EVPiGwg&";
  char oauth_signature_method[]="HMAC-SHA1";
  char oauth_signature[2048];
  memset(oauth_signature,0,2048);
  //char request_method[]="GET";
  char http_url1[]="https://openapi.kuaipan.cn/open/requestToken";
  //const char oauth_timestamp;
  char oauth_version[]="1.0";
  char oauth_timestamp[40]="";
  char oauth_nonce[1024]="";
  strcpy(oauth_nonce,(char*)get_nonce());
  sprintf(oauth_timestamp,"%d",(int)time(0));
  //char oauth_signature
  get_signature(http_url1,consumer_key,oauth_nonce,oauth_signature_method, oauth_timestamp, oauth_version,consumer_secret,oauth_signature);
  
  
  CURL *curl;  
  char url_base[2048]="";
  //strncpy(url_base,http_url1,strlen(http_url1));
  
  sprintf(url_base,"%s?oauth_signature=%s&oauth_consumer_key=%s&oauth_nonce=%s&oauth_signature_method=HMAC-SHA1&oauth_timestamp=%s&oauth_version=1.0",http_url1,oauth_signature,consumer_key,oauth_nonce,oauth_timestamp);
  printf("%s\n",url_base);
  curl_global_init(CURL_GLOBAL_ALL);    
  curl=curl_easy_init();  
  curl_easy_setopt(curl, CURLOPT_URL,url_base);    

  if((fp=fopen("touch.txt","w"))==NULL)  
  {  
      curl_easy_cleanup(curl);  
      exit(1);  
  }  
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data); //CURLOPT_WRITEFUNCTION 将后继的动作交给write_data函数处理  
  curl_easy_perform(curl);  
  curl_easy_cleanup(curl);  
  //exit(0);  
  return 0;
}

