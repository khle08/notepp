//
// Created by shile on 2023/1/7.
//

/***
 *  This project declares a structure named crop_info.
 *  This project shows two fast ways to define a temporary crop_info structure in the line No.31 and 39.
 *  1. Also, this project shows how to define an array in a fast way.
 *  2. Also, using nullptr is a literally safe way to initialize a pointer pointing to a class (like the std::vector in this project).
 *  3. nullptr provides a more explicit and safer way to represent a null pointer than using the NULL macro, which is simply a #define for the integer 0.
 *  4. line No.53 shows the example given by chatGPT about some advantages of using nullptr.
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
    std::cout<<"NULL:"<<NULL<<std::endl;
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

//int* p = nullptr;  // p is a null pointer
//
//if (p == nullptr)  // check if p is a null pointer
//{
//// do something
//}
//
//void foo(int* p)
//{
//    // do something with p
//}
//
//void foo(std::nullptr_t p)  // overload foo for null pointers
//{
//    // do something different when p is a null pointer
//}
//
//foo(nullptr);  // call the overload for null pointers