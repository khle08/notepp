
#include <map>
#include <mutex>
#include <thread>
#include <string>
#include <chrono>
#include <fstream>
#include <iostream>
#include <unistd.h>    // for "usleep"

#include <opencv2/opencv.hpp>

#include "imgReader.h"
typedef std::chrono::high_resolution_clock::time_point chtime;


struct Object
{
    cv::Rect_<double> rect1;
    int label;
    float conf;
};


void testRtspPushStream()
{
    cv::VideoCapture cap("/Users/kcl/Documents/Cpp_Projects/_algorithm/adasAlgo/data/video/IMG_4468-p2.mp4");

    cv::VideoWriter writer;
    std::string rtsp = rtsp_str("rtsp://192.168.110.224:8554/test/video", 640, 360, 600, "ultrafast");
    writer.open(rtsp, 0, 20, cv::Size(640, 360), true);

    int n = 0;
    cv::Mat frame;

    while (true) {
        if (cap.isOpened()) {
            cap.read(frame);
        }

        if (frame.data == NULL) {
            break;
        }

        cv::resize(frame, frame, cv::Size(640, 360), 0, 0, cv::INTER_LINEAR);
        cv::imshow("push stream", frame);
        writer << frame;
        cv::waitKey(10);
    }
}


void testOpticalFlow()
{
    cv::Mat prev, gray, now, res;
    // cv::VideoCapture cap("/home/ubt/Documents/c++/adasAlgo/data/video/IMG_4468.mov");
    cv::VideoCapture cap("/Users/kcl/Documents/Cpp_Projects/_algorithm/adasAlgo/data/video/IMG_4468.MOV");

    int n = 0;
    while (cap.isOpened()) {
        if (n >= 0) {
            cap.read(now);
        }

        if (now.data == NULL) {
            break;
        }

        cv::cvtColor(now, gray, cv::COLOR_BGR2GRAY);
        cv::resize(gray, gray, cv::Size(640, 320), 0, 0, cv::INTER_LINEAR);
        // cv::resize(gray, gray, cv::Size(1024, 576), 0, 0, cv::INTER_LINEAR);

        if (!prev.empty()) {
            chtime t1 = std::chrono::high_resolution_clock::now();
            cv::calcOpticalFlowFarneback(prev, gray, res, 0.5, 3, 15, 3, 5, 1.2, 0);
            chtime t2 = std::chrono::high_resolution_clock::now();

            std::chrono::duration<double> diff = t2 - t1;
            print("use " << diff.count() << " s\n");
            // bool res = diff.count() > 0.0;
            // print(res);
            // std::cout << res.size() << std::endl;

            for (int y = 0; y < gray.rows; y+=10) {
                for (int x = 0; x < gray.cols; x += 10) {
                    const cv::Point2f flowatxy = res.at<cv::Point2f>(y, x) * 4;
                    cv::line(now, cv::Point(x, y), cv::Point(
                        cvRound(x + flowatxy.x), cvRound(y + flowatxy.y)), cv::Scalar(0, 0, 255));
                    cv::circle(now, cv::Point(x, y), 1, cv::Scalar(0, 0, 0), -1);
                }
            }
        }

        cv::imshow("flow", now);
        cv::waitKey(10);

        std::swap(prev, gray);
    }
}


void testColorTemperature()
{
    // std::string pth = "/Users/kcl/Desktop/family.jpg";
    std::string pth = "/home/ubt/Documents/c++/adasAlgo/data/image/pX.jpg";
    cv::Mat img = cv::imread(pth, 1);

    if (img.empty()) {
        print("[ERROR] Failed to load image: " << pth << " " << img.size());

    } else {
        print("[SUCCESS] image size: " << img.size());

        img = ColorTemperature(img, 20);
        cv::imshow("abc", img);
        cv::waitKey(0);
    }
};


int main(int argc, char const *argv[])
{
    // std::string pth = "/Users/kcl/Desktop/family.jpg";
    // // std::string pth = "/home/ubt/Documents/c++/adasAlgo/data/image/pX.jpg";
    // cv::Mat img = cv::imread(pth, 1);

    print("\n===== OpenCV YUV [start] =====");

    int width = 1280;
    int height = 640;

    // Size for YUV420: width * height for Y + (width/2 * height/2) for U and V
    size_t frameSize = width * height + 2 * (width / 2) * (height / 2);

    // Read YUV file
    std::ifstream yuvFile("../data/test1.yuv", std::ios::binary);
    if (!yuvFile.is_open()) {
        std::cerr << "Error opening YUV file!" << std::endl;
    }

    // Allocate buffer to hold raw YUV data
    std::vector<uint8_t> buffer(frameSize);
    yuvFile.read(reinterpret_cast<char*>(buffer.data()), frameSize);

    if (buffer.empty()) {
        std::cerr << "Error reading YUV file!" << std::endl;
    }

    // Create OpenCV Mat for YUV image
    cv::Mat yuvImage(height + height / 2, width, CV_8UC1, buffer.data());

    // Convert YUV to BGR
    cv::Mat bgrImage;
    cv::cvtColor(yuvImage, bgrImage, cv::COLOR_YUV2BGR_I420);

    // Save as JPEG
    cv::imwrite("output_image.jpg", bgrImage);

    print("\n===== OpenCV YUV [ end ] =====");


    print("\n===== OpenCV testing [start] =====");

    // [!] Test RTSP push stream
    // testRtspPushStream();

    // [!] Test optical flow
    // testOpticalFlow();

    // [!] Change color temperature
    // testColorTemperature();

    print("\n===== OpenCV rotating [start] =====");

   //  // cv::imshow("abc", img);
   //  // cv::waitKey(0);

   //  int angle = 90;
   //  cv::Point2f center((img.cols - 1) / 2.0, (img.rows - 1) / 2.0);
   //  cv::Mat rot = cv::getRotationMatrix2D(center, angle, 1.0);

   // // determine bounding rectangle, center not relevant
   //  cv::Rect2f bbox = cv::RotatedRect(cv::Point2f(), img.size(), angle).boundingRect2f();
   //  // adjust transformation matrix
   //  rot.at<double>(0,2) += bbox.width / 2.0 - img.cols / 2.0;
   //  rot.at<double>(1,2) += bbox.height / 2.0 - img.rows / 2.0;

   //  // cv::Mat img;
   //  cv::warpAffine(img, img, rot, bbox.size());

   //  cv::imshow("abc", img);
   //  cv::waitKey(0);

    print("\n===== OpenCV rotating [ end ] =====");

    // cv::Rect_<double> rect1(0.3, 0.4, 3.11, 3.22);
    // print(rect1.x);           // 0.3
    // print(rect1.y);           // 0.4
    // print(rect1.width);       // 3.11
    // print(rect1.height);      // 3.22
    // print(rect1.tl());        // [0.3, 0.4]
    // print(rect1.br());        // [3.41, 3.62]
    // print(rect1.tl().x);      // 0.3
    // print(rect1.br().y);      // 3.62
    // print(rect1.area());      // 10.0142 == 3.11 * 3.22
    // cv::Rect_<double> rect2(1.4, 2.5, 3.11, 3.22);

    // cv::Rect_<double> inter = rect1 & rect2;
    // cv::Rect_<double> unite = rect1 | rect2;
    // print(inter);
    // print(unite);


    // // 2 ways to init a struct
    // Object obj1 = Object{rect1, 1, 0.88};
    // Object obj2{rect1, 1, 0.99};

    print("\n===== OpenCV thread [ start ] =====");

    // std::vector<ImgReader*> imrVec;
    // // std::vector<std::string> srcVec = {"/home/ubt/Documents/c++/adasAlgo/data/video/IMG_4468.mov"};
    // std::vector<std::string> srcVec = {"/Users/kcl/Documents/Cpp_Projects/_algorithm/adasAlgo/data/video/IMG_4468.MOV"};

    // std::mutex imgMutex;
    // std::condition_variable cvMutex;
    // std::map<int, std::vector<Cam>> images = {};

    // for (int i = 0; i < srcVec.size(); i++) {
    //     // ImgReader imr(srcVec[i], i + 1, images, imgMutex);
    //     ImgReader* imr = new ImgReader(srcVec[i], i + 1, images, imgMutex);
    //     imr->runAlgo(640, 360, "opticalFlow", imgMutex);

    //     imrVec.push_back(imr);
    // }
    // usleep(3 * 1000 * 1000);    // 1s
    // print(imrVec[0]->image.frame.size());  // check if the frame is being copied to class struct attribute

    // cv::Mat mainFrame;

    // int ZZZ = 0;
    // while (true) {
    //     print(imrVec[0]->image.prev.size() << " " << ZZZ);
    //     ZZZ += 1;

    //     // [!] Test if the algo can be stopped successfully here
    //     // if (ZZZ > 50) {
    //     //     imrVec[0]->stopAlgo("opticalFlow", false, imgMutex);
    //     // }

    //     // [!] Should not put algo here since it needs to init new thread everytime when started, which is inefficient.
    //     // if (imrVec[0]->firstFrame || imrVec[0]->image.status == 1) {
    //     //     int res = imrVec[0]->runAlgo(640, 360, "opticalFlow", imgMutex);
    //     //     print("in algo ~~~~~~~~ OOO");
    //     // }

    //     // [!] Visualize the optical flow
    //     // if (!imrVec[0]->image.flow.empty()) {
    //     //     imgMutex.lock();
    //     //     for (int y = 0; y < imrVec[0]->image.prev.rows; y+=10) {
    //     //         for (int x = 0; x < imrVec[0]->image.prev.cols; x += 10) {
    //     //             // cv::Mat flow = imrVec[0]->image.flow.clone();

    //     //             cv::Point2f flowatxy = imrVec[0]->image.flow.at<cv::Point2f>(y, x) * 4;
    //     //             cv::line(images[1][0].frame, cv::Point(x, y), cv::Point(
    //     //                 cvRound(x + flowatxy.x), cvRound(y + flowatxy.y)), cv::Scalar(0, 0, 255));
    //     //             cv::circle(images[1][0].frame, cv::Point(x, y), 1, cv::Scalar(0, 0, 0), -1);
    //     //         }
    //     //     }
    //     //     imgMutex.unlock();
    //     // }

    //     // // [!] "imshow" can not be run on MAC with the following error info:
    //     // //      Terminating app due to uncaught exception 'NSInternalInconsistencyException',
    //     // //      reason: 'nextEventMatchingMask should only be called from the Main Thread!'
    //     // cv::imshow("flow", images[1][0].frame);
    //     // cv::waitKey(30);
    //     usleep(0.01 * 1000 * 1000);    // 1s
    // }

    // [!] Test if frame data is loaded into map successfully in thread

    // std::map<int, std::vector<Cam>>::iterator it;
    // for (it = images.begin(); it != images.end(); it++) {
    //     print("first: " << it->first << " || second: " << it->second.size());
    // }

    // usleep(1 * 1000 * 1000);    // 1s

    // std::map<int, std::vector<Cam>>::iterator it2;
    // for (it2 = images.begin(); it2 != images.end(); it2++) {
    //     print("first: " << it2->first << " || second: " << it2->second.size());
    // }

    // usleep(1 * 1000 * 1000);    // 1s

    // std::map<int, std::vector<Cam>>::iterator it_debug;
    // for (it_debug = images.begin(); it_debug != images.end(); it_debug++) {
    //     print("first: " << it_debug->first << " || second: " << it_debug->second.size());
    //     print(it_debug->second[0].frame.size());
    // }


    // // 3 ways to put element into map.
    // Cam cam = {-1, -1, img, false};
    // std::vector<Cam> imgVec = {cam};
    // images[0] = imgVec;
    // images.insert({1, imgVec});  // if the key is the same, value will be replaced
    // images.insert(std::map<int, std::vector<Cam>>::value_type(2, imgVec));

    print("\n===== OpenCV thread [  end  ] =====\n");

    // cv::Rect r(300, 20, 5, 5);
    // cv::Mat data = img(r).clone();
    // data.convertTo(data, CV_32FC3);

    // // // we can simply use Scalar to compute with mat channels accordingly
    // // print(data);
    // // data = data / cv::Scalar(10.0, 20.0, 30.0);
    // // print(data);

    // cv::Mat channels[3];
    // cv::split(data, channels);

    // cv::Mat mat = channels[0];

    // // print(mat);
    // // // cv::divide(1 / 10.0, mat, mat, -1);

    // // // cv::subtract(cv::Scalar(10, 10, 10), mat, mat);
    // // print(mat);

    // cv::merge(channels, 3, data);
    // // print(data);

    print(  "===== OpenCV testing [ end ] =====\n");

    cv::destroyAllWindows();
    return 0;
}
