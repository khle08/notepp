//
// Created by shile on 2022/11/24.
//


/**
 *  In this project, I wanna explain why we don't use a non-static method function as the
 *  callback function of the inside class thread class (A.K.A. std::thread).
 *  Both the external functions and the static class method functions have no implicit passed parameter, while the
 *  non-static class method functions have an implicit passed parameter named "self" or "this", which is very similar
 *  with the python syntax.
 */


#include <thread>
#include <iostream>
#include "ob/test.h"

int main(){
    test a;
    return 0;
}