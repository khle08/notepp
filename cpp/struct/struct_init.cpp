//
// Created by shile on 2023/1/7.
//

/***
 *  This project declares a structure named crop_info.
 *  This project shows two fast ways to define a temporary crop_info structure in the line No.31 and 39.
 *  Also, this project shows how to define an array in a fast way.
 *  Also, using nullptr is a literally safe way to initialize a pointer pointing to a class (like the std::vector in this project).
 */

#include <iostream>
#include <vector>

struct crop_info{
    std::string ip;
    std::string rtsp;
    float x1y1x2y2[4];
    float w;
    float h;
    int origin_w;
    int origin_h;
};

int main() {
    std::cout << "Hello, World!" << std::endl;

    std::vector<crop_info> *m = nullptr;
    if(m == nullptr){std::cout<<"-----------------"<<std::endl;}
    m = new std::vector<struct crop_info>;

    m->push_back(crop_info{.ip = "",
            .rtsp = "",
            .x1y1x2y2 = {0,0,0,0},
            .w = 2560,
            .h = 1440,
            .origin_w = 2560,
            .origin_h = 1440});

    m->push_back(crop_info{"",
            "",
            {0,0,0,0},
            2560,
            1440,
            2560,
            1440});
    return 0;
}
