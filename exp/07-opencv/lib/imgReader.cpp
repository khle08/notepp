
#include "imgReader.h"


ImgReader::ImgReader(std::string src, int inputId, std::map<int, std::vector<Cam>>& images, std::mutex& m)
        : src(src), inputId(inputId)
{
    reader = std::thread(this->read, src, inputId, std::ref(images), std::ref(m));
    reader.detach();
}


ImgReader::~ImgReader()
{

}


bool ImgReader::isInt(std::string s)
{
    try {
        std::stoi(s);
    } catch (std::exception& e) {
        return false;
    }
    return true;
}


int ImgReader::read(std::string src, int inputId, std::map<int, std::vector<Cam>>& images, std::mutex& m)
{
    int cnt = 1;
    cv::Mat frame;
    cv::VideoCapture cap;
    if (isInt(src)) {
        cap = cv::VideoCapture(std::stoi(src));
    } else {
        cap = cv::VideoCapture(src);
    }

    while (true) {
        int res;
        if (!cap.isOpened()) {
            std::cout << "\ncap.isOpened: false | from: " << src << std::endl;
            cap.release();
            if (isInt(src)) {
                cap = cv::VideoCapture(std::stoi(src));
            } else {
                cap = cv::VideoCapture(src);
            }
            usleep(0.1 * 1000 * 1000);
        }

        if (!cap.read(frame)) {
            std::cout << "\ncap.read: false | from: " << src << std::endl;
            cap.release();
            if (isInt(src)) {
                cap = cv::VideoCapture(std::stoi(src));
            } else {
                cap = cv::VideoCapture(src);
            }
            usleep(0.1 * 1000 * 1000);
        }

        if (frame.data == NULL) {
            std::cout << "\nframe.data: false | from: " << src << std::endl;
            cap.release();
            if (isInt(src)) {
                cap = cv::VideoCapture(std::stoi(src));
            } else {
                cap = cv::VideoCapture(src);
            }
            usleep(0.1 * 1000 * 1000);
        }

        Cam cam = {-1, -1, frame.clone(), false};
        if (frame.size().width > 0 && frame.size().height > 0) {
            m.lock();                                 // method 1
            // std::lock_guard<std::mutex> mutex(m);  // method 2
            if (cnt == 1) {
                images[inputId] = {cam};
                cnt += 1;
            } else {
                images[inputId] = {cam};
                // images[inputId].push_back(cam);
            }
            m.unlock();                               // method 1
        }

        // print("get frame: " << cnt);
        // cnt += 1;
        cv::waitKey(10);
    }

    cap.release();
    return 0;
}

