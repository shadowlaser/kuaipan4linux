#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "base64.h"
#include "url_encode.h"
#include "hmac_sha1.h"
#include "kuaipan.h"

#define MAX_LEN 1024

int get_signature(char* http_url,char* oauth_consumer_key,char* oauth_nonce, char* oauth_signature_method,char* oauth_timestamp, char* oauth_version,char* consumer_secret,char oauth_signature[])
{
    //char* oauth_signature=(char*)malloc(MAX_LEN*sizeof(char));
    char tmp_result[MAX_LEN]="",request_url[MAX_LEN]="",out[MAX_LEN]="";
    int t=0;
    //char url[MAX_LEN]="";
    char consumer_key[MAX_LEN]="";
    char nonce[MAX_LEN]="";
    char signature_method[MAX_LEN]="";
    char time_stamp[MAX_LEN]="";
    char version[MAX_LEN]="";
    //sprintf(url,"%s&
    sprintf(consumer_key,"oauth_consumer_key=%s",oauth_consumer_key);
    sprintf(nonce,"&oauth_nonce=");
    sprintf(signature_method,"&oauth_signature_method=%s",oauth_signature_method);
    sprintf(time_stamp,"&oauth_timestamp=%s",oauth_timestamp);
    sprintf(version,"&oauth_version=%s",oauth_version);

    strcat(request_url,"GET&");
    //http url encode
    URLEncode(http_url,strlen(http_url),tmp_result,MAX_LEN);
    strcat(request_url,tmp_result);
    strcat(request_url,"&");
    
    //consumer_key encode
    URLEncode(consumer_key,strlen(consumer_key),tmp_result,MAX_LEN);
    strcat(request_url,tmp_result);
    
    //nonce encode
    URLEncode(nonce,strlen(nonce),tmp_result,MAX_LEN);
    strcat(request_url,tmp_result);
    strcat(request_url,oauth_nonce);
    
    //signature_method encode
    URLEncode(signature_method,strlen(signature_method),tmp_result,MAX_LEN);
    strcat(request_url,tmp_result);
    
    //time_stamp encode
    URLEncode(time_stamp,strlen(time_stamp),tmp_result,MAX_LEN);
    strcat(request_url,tmp_result);
    
    //oauth encode
    URLEncode(version,strlen(version),tmp_result,MAX_LEN);
    strcat(request_url,tmp_result);

    int request_url_len=strlen(request_url);
    printf("encode url = %s,encode length = %d\n",request_url,request_url_len);

    int consumer_secret_len=strlen(consumer_secret);
    //sha encrypt
    char *hmac_sha_str=(char*)hmac_sha(consumer_secret,consumer_secret_len,request_url,request_url_len,out,20);
    int hmac_sha_str_len=strlen(hmac_sha_str);
    printf("hmac_sha_str = %s, hmac_sha_str_len = %d\n",hmac_sha_str, hmac_sha_str_len);

    //base64 encode
    char* base64_encode_result = base64_encode(hmac_sha_str, hmac_sha_str_len);
    int base64_encode_result_len=strlen(base64_encode_result);
    URLEncode(base64_encode_result,base64_encode_result_len,tmp_result,MAX_LEN);
    strcat(oauth_signature,tmp_result);

    printf("oauth_signature = %s, oauth_signature_len = %d\n",oauth_signature,strlen(oauth_signature));
    return 1;
}


