#ifndef _IMGREADER_H_
#define _IMGREADER_H_

#include <map>
#include <mutex>
#include <thread>
#include <string>
#include <unistd.h>
#include <iostream>
#include <condition_variable>

#include <opencv2/opencv.hpp>

#define print(x) std::cout << x << std::endl;


class ImgReader
{
public:
    ImgReader();
    ~ImgReader();

private:
    int inputId = -1;
    std::string src = "";

    int rsWidth = 640;
    int rsHeight = 360;
    bool isRecording = false;
    bool isStreaming = false;
};


#endif
