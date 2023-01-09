//
// Created by shile on 2022/11/24.
//

#include "class_with_thread.h"

// static function
void class_with_thread::fun(int a, class_with_thread *tet){
    for (int i = 0; i < 10; ++i) {
        std::cout<<a<<std::endl;
        tet->m=2;
        std::cout<<tet->m<<std::endl;
        std::cout<<tet->n<<std::endl;
    }
}

// non_static function
void class_with_thread::non_fun(int a, class_with_thread *tet){
    for (int i = 0; i < 10; ++i) {
        std::cout<<a<<std::endl;
        tet->m=2;
        std::cout<<tet->m<<std::endl;
        std::cout<<tet->n<<std::endl;
    }
}