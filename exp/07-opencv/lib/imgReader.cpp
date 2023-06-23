
#include "imgReader.h"


ImgReader::ImgReader(std::string src, int inputId, std::map<int, std::vector<cv::Mat>>& images)
        : src(src), inputId(inputId)
{
    reader = std::thread(this->read, src, inputId, std::ref(images));
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


int ImgReader::read(std::string src, int inputId, std::map<int, std::vector<cv::Mat>>& images)
{
    int cnt = 1;
    cv::Mat frame;
    cv::VideoCapture cap;
    if (isInt(src)) {
        cap = cv::VideoCapture(std::stoi(src));
    } else {
        cap = cv::VideoCapture(src);
    }
    assert(cap.isOpened());

    while (cap.read(frame)) {
        if (frame.data == NULL) {
            break;
        }

        if (cnt == 1) {
            images[inputId] = {frame};
        } else {
            images[inputId] = {frame};
            // images[inputId].push_back(frame);
        }

        print("get frame: " << cnt);
        cv::waitKey(10);
        cnt += 1;
    }

    return 0;
}

