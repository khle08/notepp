//
// Created by shile on 2022/11/24.
//

#include "test.h"

void test::fun(int a, test *tet){
    for (int i = 0; i < 10; ++i) {
        std::cout<<a<<std::endl;
        tet->m=2;
        std::cout<<tet->m<<std::endl;
        std::cout<<tet->n<<std::endl;
    }
}

void test::non_fun(int a, test *tet){
    for (int i = 0; i < 10; ++i) {
        std::cout<<a<<std::endl;
        tet->m=2;
        std::cout<<tet->m<<std::endl;
        std::cout<<tet->n<<std::endl;
    }
}