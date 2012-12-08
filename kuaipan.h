#ifndef __KUAIPAN__
#define __KUAIPAN__

int get_signature(char* http_url,char* oauth_consumer_key,char* oauth_nonce, char* oauth_signature_method,char* oauth_timestamp, char* oauth_version,char* consumer_secret,char oauth_signature[]);
#endif