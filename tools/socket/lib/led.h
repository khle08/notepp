#pragma once
#ifndef _LED_H_
#define _LED_H_

#include <string>
#include <vector>
#include <iostream>

#include "strcvt.hpp"


typedef struct tagBufferInfo
{
    char arrchBuffer[3000];  //2K
    int nLen;
} BUFFER_INFO;


std::string zeroFmt(int num, int n)
{
    std::string s = std::to_string(n);
    if (num > s.length()) {
        return std::string(num - s.length(), '0') + s;
    } else {
        return std::to_string(n);
    }
}


int realTimeBuffer(int uid, const char* content, std::string language)
{
    BUFFER_INFO b;
    int rc;

    // Encode content in GB2312 format
    int len_content;
    if (language == "eng") {
        len_content = (int)strlen(content);               // 显示内容长度
    } else if (language == "chi") {
        len_content = (int)strlen(content) * 2 / 3;       // 显示内容长度
    }
    char buf_content[len_content];  // <= encoded data
    rc = u2g(content, strlen(content), buf_content, len_content);

    int len_packet = len_content + 5;                     // 具体内容长度
    int len_total = len_packet + 19;                      // 总长度

    int nArrIndex = 0;
    // 包头
    b.arrchBuffer[nArrIndex++] = (char)0xFE;
    b.arrchBuffer[nArrIndex++] = (char)0x5C;
    b.arrchBuffer[nArrIndex++] = (char)0x4B;
    b.arrchBuffer[nArrIndex++] = (char)0x89;
    // 总长
    b.arrchBuffer[nArrIndex++] = (char)(len_total % 256);
    b.arrchBuffer[nArrIndex++] = (char)((len_total >> 8) % 256);
    b.arrchBuffer[nArrIndex++] = (char)((len_total >> 16) % 256);
    b.arrchBuffer[nArrIndex++] = (char)((len_total >> 24) % 256);
    // 指令字
    b.arrchBuffer[nArrIndex++] = (char)0x65;
    // 消息id
    b.arrchBuffer[nArrIndex++] = (char)0x00;
    b.arrchBuffer[nArrIndex++] = (char)0x00;
    b.arrchBuffer[nArrIndex++] = (char)0x00;
    b.arrchBuffer[nArrIndex++] = (char)0x00;
    // 具体内容长度
    b.arrchBuffer[nArrIndex++] = (char)(len_packet % 256);
    b.arrchBuffer[nArrIndex++] = (char)((len_packet >> 8) % 256);
    b.arrchBuffer[nArrIndex++] = (char)((len_packet >> 16) % 256);
    b.arrchBuffer[nArrIndex++] = (char)((len_packet >> 24) % 256);
    // 实时采集内容格式
    b.arrchBuffer[nArrIndex++] = (char)(uid);
    b.arrchBuffer[nArrIndex++] = (char)0x00;
    b.arrchBuffer[nArrIndex++] = (char)0xFF;
    b.arrchBuffer[nArrIndex++] = (char)0xFF;
    b.arrchBuffer[nArrIndex++] = (char)(len_content);
    for (int i = 0; i < len_content; i++) {
        b.arrchBuffer[nArrIndex++] = buf_content[i];
        // 显示内容
    }
    // 包尾
    b.arrchBuffer[nArrIndex++] = (char)0xFF;
    b.arrchBuffer[nArrIndex++] = (char)0xFF;
    b.nLen = nArrIndex;
    return 0;
}


BUFFER_INFO interCodeBuffer(int uid, const char* content, std::string language)
{
    BUFFER_INFO b;

    int ledColor = 49;    // 屏幕基色，单基色=49、双基色=50、三基色=51
    int showWidth = 128;  // 区域宽度，需要与模板的一致
    int showHeight = 32;  // 区域宽度，需要与模板的一致
    int showFont = 1;     // 显示字体，1=宋体、2=黑体、3=楷体
    int showSize = 2;     // 显示字体大小，0=12x12、1=16x16、2=32x32、3=48x48
    int showColor = 1;    // 显示颜色，1=红色、2=绿色、3=黄色
    int showStyle = 1;    // 移动方式，1=从右往左、9=静止显示
    int showSpeed = 1;    // 移动速度，1到8，越大越慢
    int holdTime = 1;     // 停留时间，0到255，单位是*5秒

    int rc;
    // Encode UID in GB2312 format
    const char* _uid = zeroFmt(9, uid).c_str();
    int len_uid = (int)strlen(_uid);
    // print("uid: " << len_uid);
    char buf_uid[len_uid];          // <= encoded data
    rc = u2g(_uid, strlen(_uid), buf_uid, len_uid);

    // Encode content in GB2312 format
    int len_content;
    if (language == "eng") {
        len_content = (int)strlen(content);               // 显示内容长度
    } else if (language == "chi") {
        len_content = (int)strlen(content) * 2 / 3;       // 显示内容长度
    }
    char buf_content[len_content];  // <= encoded data
    rc = u2g(content, strlen(content), buf_content, len_content);

    len_content += 10;
    int len_packet = len_content + 52;                    // 具体内容长度
    int len_total = len_packet + 19;                      // 总长度

    int nArrIndex = 0;
    // 包头
    b.arrchBuffer[nArrIndex++] = (char)0xFE;
    b.arrchBuffer[nArrIndex++] = (char)0x5C;
    b.arrchBuffer[nArrIndex++] = (char)0x4B;
    b.arrchBuffer[nArrIndex++] = (char)0x89;
    // 总长
    b.arrchBuffer[nArrIndex++] = (char)(len_total % 256);
    b.arrchBuffer[nArrIndex++] = (char)((len_total >> 8) % 256);
    b.arrchBuffer[nArrIndex++] = (char)((len_total >> 16) % 256);
    b.arrchBuffer[nArrIndex++] = (char)((len_total >> 24) % 256);
    // 指令字
    b.arrchBuffer[nArrIndex++] = (char)0x31;
    // 消息id
    b.arrchBuffer[nArrIndex++] = (char)0x00;
    b.arrchBuffer[nArrIndex++] = (char)0x00;
    b.arrchBuffer[nArrIndex++] = (char)0x00;
    b.arrchBuffer[nArrIndex++] = (char)0x00;
    // 具体内容长度
    b.arrchBuffer[nArrIndex++] = (char)(len_packet % 256);
    b.arrchBuffer[nArrIndex++] = (char)((len_packet >> 8) % 256);
    b.arrchBuffer[nArrIndex++] = (char)((len_packet >> 16) % 256);
    b.arrchBuffer[nArrIndex++] = (char)((len_packet >> 24) % 256);
    // 实时采集内容格式
    for (int i = 0; i < len_uid; i++) {
        b.arrchBuffer[nArrIndex++] = buf_uid[i];
    }
    b.arrchBuffer[nArrIndex++] = (char)0x2C;       // 分隔符
    b.arrchBuffer[nArrIndex++] = (char)(showStyle);  // 显示方式
    b.arrchBuffer[nArrIndex++] = (char)(showSpeed);  // 显示速度
    b.arrchBuffer[nArrIndex++] = (char)(holdTime);   // 停留时间
    // 播放日期，固定即可
    b.arrchBuffer[nArrIndex++] = (char)0x30;       // 播放起始结束日期
    b.arrchBuffer[nArrIndex++] = (char)0x31;
    b.arrchBuffer[nArrIndex++] = (char)0x30;
    b.arrchBuffer[nArrIndex++] = (char)0x31;
    b.arrchBuffer[nArrIndex++] = (char)0x30;
    b.arrchBuffer[nArrIndex++] = (char)0x31;
    b.arrchBuffer[nArrIndex++] = (char)0x39;
    b.arrchBuffer[nArrIndex++] = (char)0x39;
    b.arrchBuffer[nArrIndex++] = (char)0x31;
    b.arrchBuffer[nArrIndex++] = (char)0x32;
    b.arrchBuffer[nArrIndex++] = (char)0x33;
    b.arrchBuffer[nArrIndex++] = (char)0x31;
    // 属性长度
    b.arrchBuffer[nArrIndex++] = (char)0x13;
    b.arrchBuffer[nArrIndex++] = (char)0x00;
    b.arrchBuffer[nArrIndex++] = (char)0x00;
    b.arrchBuffer[nArrIndex++] = (char)0x00;

    b.arrchBuffer[nArrIndex++] = (char)0x55;
    b.arrchBuffer[nArrIndex++] = (char)0xAA;
    b.arrchBuffer[nArrIndex++] = (char)0x00;
    b.arrchBuffer[nArrIndex++] = (char)0x00;
    b.arrchBuffer[nArrIndex++] = (char)0x37;
    b.arrchBuffer[nArrIndex++] = (char)0x32;
    b.arrchBuffer[nArrIndex++] = (char)0x32;
    b.arrchBuffer[nArrIndex++] = (char)0x31;
    b.arrchBuffer[nArrIndex++] = (char)ledColor;
    b.arrchBuffer[nArrIndex++] = (char)0x31;
    b.arrchBuffer[nArrIndex++] = (char)0x00;
    b.arrchBuffer[nArrIndex++] = (char)0x00;
    // 宽度
    int _showWidth = int(showWidth / 8);
    b.arrchBuffer[nArrIndex++] = (char)(_showWidth % 256);
    b.arrchBuffer[nArrIndex++] = (char)((_showWidth >> 8) % 256);
    // 高度
    b.arrchBuffer[nArrIndex++] = (char)(showHeight % 256);
    b.arrchBuffer[nArrIndex++] = (char)((showHeight >> 8) % 256);
    b.arrchBuffer[nArrIndex++] = (char)(showColor);
    b.arrchBuffer[nArrIndex++] = (char)((showFont << 4) + showSize);
    b.arrchBuffer[nArrIndex++] = (char)0x00;

    // 显示内容长度
    b.arrchBuffer[nArrIndex++] = (char)(len_content % 256);
    b.arrchBuffer[nArrIndex++] = (char)((len_content >> 8) % 256);
    b.arrchBuffer[nArrIndex++] = (char)((len_content >> 16) % 256);
    b.arrchBuffer[nArrIndex++] = (char)((len_content >> 24) % 256);
    for (int i = 0; i < len_content - 10; i++) {
        b.arrchBuffer[nArrIndex++] = buf_content[i];
        // 显示内容
    }
    b.arrchBuffer[nArrIndex++] = (char)0xFF;
    b.arrchBuffer[nArrIndex++] = (char)0x00;
    b.arrchBuffer[nArrIndex++] = (char)0x01;
    b.arrchBuffer[nArrIndex++] = (char)0x00;
    b.arrchBuffer[nArrIndex++] = (char)0x01;
    b.arrchBuffer[nArrIndex++] = (char)0x00;
    b.arrchBuffer[nArrIndex++] = (char)0x01;
    b.arrchBuffer[nArrIndex++] = (char)0x00;
    b.arrchBuffer[nArrIndex++] = (char)0x10;
    b.arrchBuffer[nArrIndex++] = (char)0x48;
    // 包尾
    b.arrchBuffer[nArrIndex++] = (char)0xFF;
    b.arrchBuffer[nArrIndex++] = (char)0xFF;
    b.nLen = nArrIndex;
    return b;
}


#endif // _FILES_H_

