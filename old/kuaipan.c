/*****************************************************************/
/*********** 程序名称：get_http.c ********************************/
/*********** 功能：向固定地址发起请求得到返回页面字符 ************/
/*********** 作者：YZW  ******************************************/
/*********** 时间：2010-10-28 ************************************/
/*****************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>


int htconnect(char *host, int port){
        int white_sock;
        struct hostent * site;
        struct sockaddr_in me;
//        site = gethostbyname(host);
        if (site==NULL){
            printf("site is null\n");
            return -2;
        }
        white_sock = socket(AF_INET,SOCK_STREAM,0);
        if (white_sock <0){
            printf("white_sock is less then 0\n");
            return -1;
        }
        memset(&me, 0, sizeof(struct sockaddr_in));
        memcpy(&me.sin_addr, site->h_addr_list[0], site->h_length);
        me.sin_family = AF_INET;
        me.sin_port = htons(port);
        return (connect(white_sock, (struct sockaddr *)&me,sizeof(struct sockaddr)) <0) ? -1 : white_sock;
}

int htsend(int sock, char *fmt, ...){
        char BUF[1024];
        va_list argptr;
        va_start(argptr,fmt);
        vsprintf(BUF,fmt,argptr);
        va_end(argptr);
        printf("%s",BUF);  //回显
        printf("-->%s<--\n",BUF);
        return send(sock,BUF,strlen(BUF),0);
}


int main(int argc,char **argv){
        int black_sock;
        int M,N;
        char bugs_bunny[3];
        printf("start connect\n");
        char* aa="https://openapi.kuaipan.cn/open/requestToken?oauth_signature=CAj%2B6nKzTOG%2BVyQyHpqvI%2FIuI7w%3D&oauth_consumer_key=xcRFTuyppHYMbmk4&oauth_nonce=g6s6T111&oauth_signature_method=HMAC-SHA1&oauth_timestamp=1347971614&oauth_version=1.0";
        black_sock = htconnect(aa,80);
        if (black_sock <1){
            printf("quit\n");       
            return;
        }

        printf("循环发送请求开始\n");
        htsend(black_sock, "GET / HTTP/1.0\n");
        htsend(black_sock, "Host: %s\n", argv[1]);
        htsend(black_sock, "\n");
        printf("循环发送请求 %d 次\n",M);

        printf("收到信息Start:---->\n");
        while (read(black_sock, bugs_bunny, 1)> 0){
              printf( "%c",bugs_bunny[0]);
        }

        printf( "收到信息End.<----\n ");
        close(black_sock);
}
