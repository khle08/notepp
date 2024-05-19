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


cv::Mat ColorTemperature(cv::Mat& input, int n);
std::string rtsp_str(std::string url, int iwidth, int iheight, int bitrate, std::string speed);


typedef struct Camera
{
    int width;
    int height;
    cv::Mat frame;
    bool took;
}Cam;


typedef struct Image
{
    // {{x1, y1}, {x2, y2}, {x3, y3}, ...}
    std::vector<std::vector<float>> coords;
    cv::Mat frame;
    cv::Mat prev;
    cv::Mat flow;
    int status;  // 0: new / 1: processed / 2: ... more
}Img;


class ImgReader
{
public:
    ImgReader(std::string src, int inputId, std::map<int, std::vector<Cam>>& images, std::mutex& m);
    ~ImgReader();

    Img image;
    std::thread reader;
    std::thread algorithm;

    bool firstFrame = true;

    int startRecording(int width, int height, float interval, bool isCycling, float maxStorage, float maxFileNum);
    int stopRecording(float interval);
    int startStreaming(int width, int height, std::string url, std::string protocol);
    int stopStreaming();

    int runAlgo(int width, int height, std::string name, std::mutex& m);
    int stopAlgo(std::string name, bool stopAll, std::mutex& m);

private:
    int inputId = -1;
    std::string src = "";

    int rsWidth = 640;
    int rsHeight = 360;
    bool isRecording = false;
    bool isStreaming = false;

    int algoWidth = 640;
    int algoHeight = 360;
    bool isRunningAlgo = false;
    bool isRunningOpticalFlow = false;

    // static must be defined here or ...
    static bool isInt(std::string s);
    static int read(std::string src, int inputId, ImgReader& obj, 
                    std::map<int, std::vector<Cam>>& images, std::mutex& m);

    static int opticalFlow(ImgReader& obj, std::mutex& m);
    // ... error: reference to non-static member function must be called;
};


#endif
