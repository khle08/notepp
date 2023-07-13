#pragma once
#ifndef _BUZZER_H_
#define _BUZZER_H_

#include "led.h"


BUFFER_INFO buzzer_on()
{
    BUFFER_INFO b;
    int nArrIndex = 0;

    b.arrchBuffer[nArrIndex++] = (char)0x01;
    b.arrchBuffer[nArrIndex++] = (char)0x05;
    b.arrchBuffer[nArrIndex++] = (char)0x00;
    b.arrchBuffer[nArrIndex++] = (char)0x00;
    b.arrchBuffer[nArrIndex++] = (char)0xFF;
    b.arrchBuffer[nArrIndex++] = (char)0x00;
    b.arrchBuffer[nArrIndex++] = (char)0x8C;
    b.arrchBuffer[nArrIndex++] = (char)0x3a;
    b.nLen = nArrIndex;
    return b;
}


BUFFER_INFO buzzer_off()
{
    BUFFER_INFO b;
    int nArrIndex = 0;

    b.arrchBuffer[nArrIndex++] = (char)0x01;
    b.arrchBuffer[nArrIndex++] = (char)0x05;
    b.arrchBuffer[nArrIndex++] = (char)0x00;
    b.arrchBuffer[nArrIndex++] = (char)0x00;
    b.arrchBuffer[nArrIndex++] = (char)0x00;
    b.arrchBuffer[nArrIndex++] = (char)0x00;
    b.arrchBuffer[nArrIndex++] = (char)0xCD;
    b.arrchBuffer[nArrIndex++] = (char)0xCA;
    b.nLen = nArrIndex;
    return b;
}


BUFFER_INFO buzzer_isOn()
{
    BUFFER_INFO b;
    int nArrIndex = 0;

    b.arrchBuffer[nArrIndex++] = (char)0x01;
    b.arrchBuffer[nArrIndex++] = (char)0x01;
    b.arrchBuffer[nArrIndex++] = (char)0x01;
    b.arrchBuffer[nArrIndex++] = (char)0x01;
    b.arrchBuffer[nArrIndex++] = (char)0x90;
    b.arrchBuffer[nArrIndex++] = (char)0x48;
    b.nLen = nArrIndex;
    return b;
}


BUFFER_INFO buzzer_isOff()
{
    BUFFER_INFO b;
    int nArrIndex = 0;

    b.arrchBuffer[nArrIndex++] = (char)0x01;
    b.arrchBuffer[nArrIndex++] = (char)0x01;
    b.arrchBuffer[nArrIndex++] = (char)0x01;
    b.arrchBuffer[nArrIndex++] = (char)0x00;
    b.arrchBuffer[nArrIndex++] = (char)0x51;
    b.arrchBuffer[nArrIndex++] = (char)0x88;
    b.nLen = nArrIndex;
    return b;
}


BUFFER_INFO buzzer_status()
{
    BUFFER_INFO b;
    int nArrIndex = 0;

    b.arrchBuffer[nArrIndex++] = (char)0x01;
    b.arrchBuffer[nArrIndex++] = (char)0x01;
    b.arrchBuffer[nArrIndex++] = (char)0x00;
    b.arrchBuffer[nArrIndex++] = (char)0x00;
    b.arrchBuffer[nArrIndex++] = (char)0x00;
    b.arrchBuffer[nArrIndex++] = (char)0x01;
    b.arrchBuffer[nArrIndex++] = (char)0xFD;
    b.arrchBuffer[nArrIndex++] = (char)0xCA;
    b.nLen = nArrIndex;
    return b;
}



#endif // _FILES_H_

