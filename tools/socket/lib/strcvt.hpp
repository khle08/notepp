#pragma once
#ifndef _CODEC_H_
#define _CODEC_H_

#include <string>
#include <cerrno>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <iostream>

#define print(x) std::cout << x << std::endl;

// note: https://blog.csdn.net/cabing2005/article/details/52787497
namespace cc{
    // In order to convert utf-8 into gb2312
    #include "iconv.h"
}



// 代码转换: 从一种编码转为另一种编码 
int code_convert(const char *from_charset, const char *to_charset,
                 char *inbuf, size_t inlen, char *outbuf, size_t outlen) 
{
    char **pin = &inbuf; 
    char **pout = &outbuf; 

    cc::iconv_t cd = cc::iconv_open(to_charset, from_charset); 
    if (cd==0) 
        return -1; 

    memset(outbuf, 0, outlen);
    if (cc::iconv(cd, pin, &inlen, pout, &outlen)==-1)
        return -1;

    print(*outbuf);
    cc::iconv_close(cd); 
    return 0; 
} 


// UNICODE 码转为 GB2312 码 
int u2g(const char *inbuf, int inlen, char *outbuf, int outlen) 
{
    return code_convert("utf-8", "gb2312", (char*)inbuf, inlen, outbuf, outlen); 
} 


// GB2312 码转为 UNICODE 码 
int g2u(const char *inbuf, size_t inlen, char *outbuf, size_t outlen) 
{
    return code_convert("gb2312", "utf-8", (char*)inbuf, inlen, outbuf, outlen); 
} 


////////////////////// UTF-8 v1 //////////////////////
std::string byte_to_hex(unsigned char c) {
    char buff[16];
    sprintf(buff, "0x%02hhx", c);
    return std::string(buff);
}


void print_bytes(char* s) {
    int len = strlen(s);
    for (int i = 0; i < len; ++i) {
        std::cout << byte_to_hex((unsigned char)s[i]) << " ";
    }
    std::cout << "\n";
}
////////////////////// UTF-8 v1 //////////////////////


////////////////////// UTF-8 v2 //////////////////////
// char Dec2HexChar(short int n)   
// {  
//     if ( 0 <= n && n <= 9 ) {  
//         return char( short('0') + n );  
//     } else if ( 10 <= n && n <= 15 ) {  
//         return char( short('A') + n - 10 );  
//     } else {  
//         return char(0);  
//     }  
// }  
  
// short int HexChar2Dec(char c)  
// {  
//     if ( '0'<=c && c<='9' ) {  
//         return short(c-'0');  
//     } else if ( 'a'<=c && c<='f' ) {  
//         return ( short(c-'a') + 10 );  
//     } else if ( 'A'<=c && c<='F' ) {  
//         return ( short(c-'A') + 10 );  
//     } else {  
//         return -1;  
//     }  
// }  
  
// std::string EncodeURL(const std::string &URL)  
// {  
//     std::string strResult = "";  
//     for ( unsigned int i=0; i<URL.size(); i++ )  
//     {  
//         char c = URL[i];  
//         if (  
//             ( '0'<=c && c<='9' ) ||  
//             ( 'a'<=c && c<='z' ) ||  
//             ( 'A'<=c && c<='Z' ) ||  
//             c=='/' || c=='.'  
//             ) {  
//                 strResult += c;  
//         }   
//         else   
//         {  
//             int j = (short int)c;  
//             if ( j < 0 )  
//             {  
//                 j += 256;  
//             }  
//             int i1, i0;  
//             i1 = j / 16;  
//             i0 = j - i1*16;  
//             strResult += '%';  
//             strResult += Dec2HexChar(i1);  
//             strResult += Dec2HexChar(i0);  
//         }  
//     }  
  
//     return strResult;  
// }  
  
// std::string DecodeURL(const std::string &URL)  
// {  
//     std::string result = "";  
//     for ( unsigned int i=0; i<URL.size(); i++ )   
//     {  
//         char c = URL[i];  
//         if ( c != '%' )   
//         {  
//             result += c;  
//         }   
//         else   
//         {  
//             char c1 = URL[++i];  
//             char c0 = URL[++i];  
//             int num = 0;  
//             num += HexChar2Dec(c1) * 16 + HexChar2Dec(c0);  
//             result += char(num);  
//         }  
//     }  
  
//     return result;  
// } 
////////////////////// UTF-8 v2 //////////////////////

#endif
