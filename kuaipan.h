#ifndef __KUAIPAN__
#define __KUAIPAN__

void get_signature(char* http_url,char* oauth_consumer_key,char* oauth_nonce, char* oauth_signature_method,char* oauth_timestamp, char* oauth_version,char* consumer_secret,char oauth_signature[])
{
  //char* oauth_signature=(char*)malloc(1024*sizeof(char));
  char obj[1024]="",d[1024]="",out[1024]="";
  int lk=0,ld=0,t=0;
  //char url[1024]="";
  char consumer_key[1024]="";
  char nonce[1024]="";	 
  char signature_method[1024]="";  
  char timestamp[1024]="";
  char version[1024]="";
  //sprintf(url,"%s&
  sprintf(consumer_key,"oauth_consumer_key=%s",oauth_consumer_key);
  sprintf(nonce,"&oauth_nonce=");
  sprintf(signature_method,"&oauth_signature_method=%s",oauth_signature_method);
  sprintf(timestamp,"&oauth_timestamp=%s",oauth_timestamp);
  sprintf(version,"&oauth_version=%s",oauth_version);
  
  strcat(d,"GET&");
  //printf("src=%s\n",d);
  //strcat(d,"&",1);
  URLEncode(http_url,strlen(http_url),obj,1024);
  strcat(d,obj);
  //printf("src=%s\n",d);
  strcat(d,"&");
  URLEncode(consumer_key,strlen(consumer_key),obj,1024);
  strcat(d,obj);
  //printf("src=%s\n",d);
  URLEncode(nonce,strlen(nonce),obj,1024);
  strcat(d,obj);
  strcat(d,oauth_nonce);
  //printf("src=%s\n",d);
  URLEncode(signature_method,strlen(signature_method),obj,1024);
  strcat(d,obj);
  //printf("src=%s\n",d);
  URLEncode(timestamp,strlen(timestamp),obj,1024);
  strcat(d,obj);
  URLEncode(version,strlen(version),obj,1024);
  strcat(d,obj);
  printf("src=%s\n%d\n",d,strlen(d));
  ld=strlen(d);
  lk=strlen(consumer_secret);
  char *hmac_shastr=(char*)hmac_sha(consumer_secret,lk,d,ld,out,20);
  int hmac_shalen=strlen(hmac_shastr);
  printf("hmac_shastr=%s\n",hmac_shastr);
  int base64_encodelen=strlen((char*)base64_encode(hmac_shastr, hmac_shalen));
  URLEncode(base64_encode(hmac_shastr,hmac_shalen),base64_encodelen,obj,1024);
  strcat(oauth_signature,obj);
  //strcat(oauth_signature,"\0");
  printf("%s\n%d\n",oauth_signature,strlen(oauth_signature));
  
  //return oauth_signature;
}
FILE *fp; //定义FILE类型指针  

size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream) //这个函数是为了符合CURLOPT_WRITEFUNCTION, 而构造的  
{  
    int written = fwrite(ptr, size, nmemb, (FILE *)fp);  
    return written;  
}  

#endif