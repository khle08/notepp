//
// Created by shile on 2022/11/24.
//

#ifndef STRUCTURE_TEST_TEST_H
#define STRUCTURE_TEST_TEST_H

#include <thread>
#include <iostream>

class class_with_thread{
public:
    class_with_thread(){
        t = new std::thread(fun,10, this);
//        t_non = new std::thread(non_fun,this,10, this);
        t->join();
        t_non->join();
    }
    std::thread * t;
    std::thread * t_non;
    int m=100;
    int n=140;
    static void fun(int a, class_with_thread *tet);
    void non_fun(int a, class_with_thread *tet);
};



#endif //STRUCTURE_TEST_TEST_H
