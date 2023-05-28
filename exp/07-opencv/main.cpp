
#include <string>
#include <iostream>

#include <opencv2/opencv.hpp>


#define print(x) std::cout << x << std::endl;


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
        print("[ERROR] image size: " << img.size());
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

    print(  "===== OpenCV testing [ end ] =====\n");

    return 0;
}
