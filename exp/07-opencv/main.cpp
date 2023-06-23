
#include <map>
#include <thread>
#include <string>
#include <iostream>
#include <unistd.h>    // for "usleep"

#include <opencv2/opencv.hpp>

#include "imgReader.h"


struct Object
{
    cv::Rect_<double> rect1;
    int label;
    float conf;
};


int main(int argc, char const *argv[])
{

    print("\n===== OpenCV testing [start] =====");

    std::string pth = "/Users/kcl/Desktop/family.jpg";

    cv::Mat img = cv::imread(pth, 1);
    if (img.empty()) {
        print("[ERROR] Failed to load image: " << pth << " " << img.size());
    } else {
        print("[SUCCESS] image size: " << img.size());
    }

    cv::Rect_<double> rect1(0.3, 0.4, 3.11, 3.22);
    print(rect1.x);           // 0.3
    print(rect1.y);           // 0.4
    print(rect1.width);       // 3.11
    print(rect1.height);      // 3.22
    print(rect1.tl());        // [0.3, 0.4]
    print(rect1.br());        // [3.41, 3.62]
    print(rect1.tl().x);      // 0.3
    print(rect1.br().y);      // 3.62
    print(rect1.area());      // 10.0142 == 3.11 * 3.22
    cv::Rect_<double> rect2(1.4, 2.5, 3.11, 3.22);

    cv::Rect_<double> inter = rect1 & rect2;
    cv::Rect_<double> unite = rect1 | rect2;
    print(inter);
    print(unite);


    // 2 ways to init a struct
    Object obj1 = Object{rect1, 1, 0.88};
    Object obj2{rect1, 1, 0.99};

    print("\n===== OpenCV thread [ start ] =====\n");
    
    std::map<int, std::vector<cv::Mat>> images = {};
    std::vector<cv::Mat> imgVec = {img};

    std::vector<std::string> srcVec = {"/Users/kcl/Desktop/ADAS.mov", "1"};
    for (int i = 0; i < srcVec.size(); i++) {
        ImgReader imr(srcVec[i], i + 1, images);
    }
    usleep(3 * 1000 * 1000);    // 1s

    std::map<int, std::vector<cv::Mat>>::iterator it;
    for (it = images.begin(); it != images.end(); it++) {
        print("first: " << it->first << " || second: " << it->second.size());
    }

    usleep(1 * 1000 * 1000);    // 1s

    std::map<int, std::vector<cv::Mat>>::iterator it2;
    for (it2 = images.begin(); it2 != images.end(); it2++) {
        print("first: " << it2->first << " || second: " << it2->second.size());
    }

    usleep(1 * 1000 * 1000);    // 1s

    std::map<int, std::vector<cv::Mat>>::iterator it_debug;
    for (it_debug = images.begin(); it_debug != images.end(); it_debug++) {
        print("first: " << it_debug->first << " || second: " << it_debug->second.size());
    }

    // 3 ways to put element into map.
    // images[0] = imgVec;
    // images.insert({1, imgVec});  // if the key is the same, value will be replaced
    // images.insert(std::map<int, std::vector<cv::Mat>>::value_type(2, imgVec));
    print("\n===== OpenCV thread [  end  ] =====\n");

    print(  "===== OpenCV testing [ end ] =====\n");

    return 0;
}
