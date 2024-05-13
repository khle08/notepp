
#include "imgReader.h"


cv::Mat ColorTemperature(cv::Mat& input, int n)
{
    cv::Mat result = input.clone();
    int row = input.rows;
    int col = input.cols;
    int level = n / 2;
    for (int i = 0; i < row; ++i)
    {
        uchar* a = input.ptr<uchar>(i);
        uchar* r = result.ptr<uchar>(i);
        for (int j = 0; j < col; ++j)
        {
            int R, G, B;
            // R通道
            R = a[j * 3 + 2];
            R = R + level;
            if (R > 255) {
                r[j * 3 + 2] = 255;
            }
            else if (R < 0) {
                r[j * 3 + 2] = 0;
            }
            else {
                r[j * 3 + 2] = R;
            }
            // G通道
            G = a[j * 3 + 1];
            G = G + level;
            if (G > 255) {
                r[j * 3 + 1] = 255;
            }
            else if (G < 0) {
                r[j * 3 + 1] = 0;
            }
            else {
                r[j * 3 + 1] = G;
            }
            // B通道
            B = a[j * 3];
            B = B - level;
            if (B > 255) {
                r[j * 3] = 255;
            }
            else if (B < 0) {
                r[j * 3] = 0;
            }
            else {
                r[j * 3] = B;
            }
        }
    }
    return result;
}


ImgReader::ImgReader(std::string src, int inputId, std::map<int, std::vector<Cam>>& images, std::mutex& m)
        : src(src), inputId(inputId)
{
    print("start: " << this->image.frame.size());

    this->image.status = 0;
    reader = std::thread(this->read, src, inputId, std::ref(*this), std::ref(images), std::ref(m));
    reader.detach();
}


ImgReader::~ImgReader()
{
    print(" end : " << this->image.frame.size());
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


int ImgReader::read(std::string src, int inputId, ImgReader& obj,
                    std::map<int, std::vector<Cam>>& images, std::mutex& m)
{
    int cnt = 1;
    cv::Mat frame;
    cv::VideoCapture cap;
    Cam cam = {-1, -1, frame, false};

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

        if (!cap.read(cam.frame)) {
            std::cout << "\ncap.read: false | from: " << src << std::endl;
            cap.release();
            if (isInt(src)) {
                cap = cv::VideoCapture(std::stoi(src));
            } else {
                cap = cv::VideoCapture(src);
            }
            usleep(0.1 * 1000 * 1000);
        }

        if (cam.frame.data == NULL) {
            std::cout << "\nframe.data: false | from: " << src << std::endl;
            cap.release();
            if (isInt(src)) {
                cap = cv::VideoCapture(std::stoi(src));
            } else {
                cap = cv::VideoCapture(src);
            }
            usleep(0.1 * 1000 * 1000);
        }

        if (!cam.frame.empty()) {
            cv::resize(cam.frame, cam.frame, cv::Size(640, 320), 0, 0, cv::INTER_LINEAR);
        }

        if (cam.frame.size().width > 0 && cam.frame.size().height > 0) {
            m.lock();                                 // method 1
            // std::lock_guard<std::mutex> mutex(m);  // method 2

            cam.took = false;
            cam.width = cam.frame.size().width;
            cam.height = cam.frame.size().height;

            if (cnt == 1) {
                images[inputId] = {cam};
                cnt += 1;
            } else {
                images[inputId] = {cam};
                // images[inputId].push_back(cam);
            }

            if (obj.isRunningAlgo) {
                cv::resize(cam.frame, obj.image.frame, cv::Size(obj.algoWidth, obj.algoHeight), 0, 0, cv::INTER_LINEAR);
                if (obj.image.status == 1) {
                    obj.image.status = 0;  // new
                }
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


int ImgReader::runAlgo(int width, int height, std::string name, std::mutex& m)
{
    m.lock();
    this->algoWidth = width;
    this->algoHeight = height;
    this->image.status = 0;      // new
    this->isRunningAlgo = true;
    m.unlock();

    if (name.compare("opticalFlow") == 0) {
        algorithm = std::thread(this->opticalFlow, std::ref(*this), std::ref(m));
        algorithm.detach();
        return 0;
    }

    return -1;
}


int ImgReader::opticalFlow(ImgReader& obj, std::mutex& m)
{
    while (true) {
        if (obj.firstFrame || obj.image.status == 0) {
            if (obj.image.frame.empty()) {
                std::cout << "~~~~ empty ~~~~~ !!!" << std::endl;
                usleep(0.1 * 1000 * 1000);
                continue;
            }

            cv::Mat gray;
            cv::cvtColor(obj.image.frame, gray, cv::COLOR_BGR2GRAY);

            if (!obj.image.prev.empty()) {
                m.lock();
                cv::calcOpticalFlowFarneback(obj.image.prev, gray, obj.image.flow, 0.5, 3, 15, 3, 5, 1.2, 0);
                obj.image.status = 1;  // processed

                if (obj.firstFrame) {
                    obj.firstFrame = false;
                }

                std::cout << "~~~ finished ~~~ OOO" << std::endl;
                // std::cout << obj.image.flow.size() << std::endl;

                // for (int y = 0; y < gray.rows; y+=10) {
                //     for (int x = 0; x < gray.cols; x += 10) {
                //         const cv::Point2f flowatxy = obj.image.flow.at<cv::Point2f>(y, x) * 4;
                //         cv::line(obj.image.frame, cv::Point(x, y), cv::Point(
                //             cvRound(x + flowatxy.x), cvRound(y + flowatxy.y)), cv::Scalar(0, 0, 255));
                //         cv::circle(obj.image.frame, cv::Point(x, y), 1, cv::Scalar(0, 0, 0), -1);
                //     }
                // }
                m.unlock();

            } else {
                std::cout << "~~~~~ skip ~~~~~ XXX" << std::endl;
                usleep(0.1 * 1000 * 1000);
            }

            std::swap(obj.image.prev, gray);
        }
    }

    return 0;
}

