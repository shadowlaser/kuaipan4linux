/*
 * =====================================================================================
 *       Filename:  url_encode.cpp
 *    Description:  url encode
 *
 *        Created:  07/04/2012 08:32:24 PM
 *
 *         Author:  zhy (), izualzhy@163.com
 * =====================================================================================
 */
#include <stdio.h>
#include <string.h>
#include "url_encode.h"
/**
 * @brief URLEncode 对字符串URL编码
 *
 * @param str 原字符串
 * @param strSize 原字符串长度(不包括最后的\0)
 * @param result 结果缓冲区的地址
 * @param resultSize 结果缓冲区的大小(包括最后的\0)
 *
 * @return: >0:resultstring 里实际有效的长度
 *            0: 解码失败.
 */
int URLEncode(const char* str, const int strSize, char* result, const int resultSize)
{
    int i;
    int j = 0;//for result index
    char ch;

    if ((str==NULL) || (result==NULL) || (strSize<=0) || (resultSize<=0)) {
        return 0;
    }

    for ( i=0; (i<strSize)&&(j<resultSize); ++i) {
        ch = str[i];
        if (((ch>='A') && (ch<'Z')) ||
            ((ch>='a') && (ch<'z')) ||
            ((ch>='0') && (ch<'9'))) {
            result[j++] = ch;
        } else if (ch == ' ') {
            result[j++] = '+';
        } else if (ch == '.' || ch == '-' || ch == '_' || ch == '*') {
            result[j++] = ch;
        } else {
            if (j+3 < resultSize) {
                sprintf(result+j, "%%%02X", (unsigned char)ch);
                j += 3;
            } else {
                return 0;
            }
        }
    }

    result[j] = '\0';
    return j;
}
/*
 * =====================================================================================
 *       Filename:  url_decode.cpp
 *    Description:  url decode
 *
 *        Created:  07/06/2012 07:35:14 PM
 *         Author:  zhy (), izualzhy@163.com
 * =====================================================================================
 */


int hex2num(char c)
{
    if (c>='0' && c<='9') return c - '0';
    if (c>='a' && c<='z') return c - 'a' + 10;//这里+10的原因是:比如16进制的a值为10
    if (c>='A' && c<='Z') return c - 'A' + 10;
    
    printf("unexpected char: %c", c);
    return NON_NUM;
}

/**
 * @brief URLDecode 对字符串URL解码,编码的逆过程
 *
 * @param str 原字符串
 * @param strSize 原字符串大小（不包括最后的\0）
 * @param result 结果字符串缓存区
 * @param resultSize 结果地址的缓冲区大小(包括最后的\0)
 *
 * @return: >0 result 里实际有效的字符串长度
 *            0 解码失败
 */
int URLDecode(const char* str, const int strSize, char* result, const int resultSize)
{
    char ch,ch1,ch2;
    int i;
    int j = 0;//record result index

    if ((str==NULL) || (result==NULL) || (strSize<=0) || (resultSize<=0)) {
        return 0;
    }

    for ( i=0; (i<strSize) && (j<resultSize); ++i) {
        ch = str[i];
        switch (ch) {
            case '+':
                result[j++] = ' ';
                break;
            case '%':
                if (i+2<strSize) {
                    ch1 = hex2num(str[i+1]);//高4位
                    ch2 = hex2num(str[i+2]);//低4位
                    if ((ch1!=NON_NUM) && (ch2!=NON_NUM))
                        result[j++] = (char)((ch1<<4) | ch2);
                    i += 2;
                    break;
                } else {
                    break;
                }
            default:
                result[j++] = ch;
                break;
        }
    }
    
    result[j] = 0;
    return j;
}
/*
int main(int argc, char* argv[])
{
    char* src = argv[1];
    char obj[100] = {0};

    unsigned int len = strlen(src);
    int resultSize = URLDecode(src, len, obj, 100);
    printf("result: %d, %s\n", resultSize, obj);

    return 0;

}
int main(int argc, char* argv[])
{
    char* src = "GEThttps://openapi.kuaipan.cn/requestToken";
    unsigned int srclength = strlen(src);
    printf("src length: %d\n", strlen(src));
    

    char obj[100] = {0};
    URLEncode(src, srclength, obj, 100);

    printf("obj: %s\n", obj);
    printf("obj: %d\n", strlen(obj));

    return 0;
}
*/