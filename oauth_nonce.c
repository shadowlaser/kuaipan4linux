#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "oauth_nonce.h"
static const char* INIT_STR="0123456789qwertyuiopasdfghjklzxcvbnmZXCVBNMASDFGHJKLPPOIUYTREWQ";
static const int LIMIT_NUM=8;
static const int LIMIT_VAL=61;
char* get_nonce()
{
    char* pnonce=(char*)malloc((LIMIT_NUM+1)*sizeof(int));
    int i;
    srand((int)time(0));
    for(i=0;i<LIMIT_NUM;i++)
    {
       pnonce[i]=INIT_STR[rand()%LIMIT_VAL];
    }
    return pnonce;
}
/*
int main(int argc,char* argv[])
{
    char nonce[32]="";
    strcpy(nonce,get_nonce());
    printf("nonce:%s\n",nonce);
    return 0;
}
*/
