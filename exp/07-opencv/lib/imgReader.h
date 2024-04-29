#ifndef _IMGREADER_H_
#define _IMGREADER_H_

#include <map>
#include <mutex>
#include <thread>
#include <string>
#include <unistd.h>
#include <iostream>

#include <opencv2/opencv.hpp>

#define print(x) std::cout << x << std::endl;


cv::Mat ColorTemperature(cv::Mat& input, int n);


typedef struct Camera
{
    int width;
    int height;
    cv::Mat frame;
    bool took;
}Cam;


class ImgReader
{
public:
    ImgReader(std::string src, int inputId, std::map<int, std::vector<Cam>>& images, std::mutex& m);
    ~ImgReader();

    std::thread reader;

private:
    int inputId = -1;
    std::string src = "";

    // static must be defined here or ...
    // error: reference to non-static member function must be called;
    static bool isInt(std::string s);
    static int read(std::string src, int inputId, std::map<int, std::vector<Cam>>& images, std::mutex& m);
};


#endif
