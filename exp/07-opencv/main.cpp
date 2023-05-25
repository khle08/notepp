
#include <string>
#include <iostream>

#include <opencv2/opencv.hpp>


#define print(x) std::cout << x << std::endl;


struct Object
{
    cv::Rect_<double> rect;
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

    cv::Rect_<double> rect(0.3, 0.4, 3.11, 3.22);
    print(rect.x);           // 0.3
    print(rect.y);           // 0.4
    print(rect.width);       // 3.11
    print(rect.height);      // 3.22
    print(rect.tl());        // [0.3, 0.4]
    print(rect.br());        // [3.41, 3.62]
    print(rect.tl().x);      // 0.3
    print(rect.br().y);      // 3.62
    print(rect.area());      // 10.0142 == 3.11 * 3.22

    // 2 ways to init a struct
    Object obj1 = Object{rect, 1, 0.88};
    Object obj2{rect, 1, 0.99};

    print(  "===== OpenCV testing [ end ] =====\n");

    return 0;
}
