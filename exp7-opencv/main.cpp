
#include <string>
#include <iostream>

#include <opencv2/opencv.hpp>


#define print(x) std::cout << x << std::endl;


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

    print(  "===== OpenCV testing [ end ] =====\n");

    return 0;
}
