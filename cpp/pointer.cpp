// Note: 部分指针测试在 func.cpp 代码中

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <typeinfo>

#include <memory>    // For shared pointer
// #include <opencv2/core/core.hpp>

#define print(x) std::cout << x << std::endl

// 指针是一个值为内存地址的变量，初始化参数的时候以 * 放变量名开头作为标识
// 即便我们也可以通过指针去获取对应内存地址的变量，单最快的方法其实还是直接用变量名的形式

// 注意
// int* p 和 int *p 是有些微差距的，前者偏向地址，p是一个地址变量，
// 后者偏向值，p是一个整型变量，声明中和使用中的 * 含义完全不同
// 且指针保存的是地址，地址不论 type 一律都占 4 个字节
// 虽然指针可以互相加减，但那是没有意义的得尽量避免，只有 ++ 和 -- 会用到，用来移动指针所指向的单元
// 而单元的占位大小和我们定义的指针类型有关，例如 int 是 4 位，而 double 是 8 位

// 动态分配内存
// 指针厉害的地方也在于，运行阶段分配未命名的内存用来存储值，此情况下只能泳指针访问内存
// 使用这个方法切记得在用完的时候把指针释放掉，delete ptr，以免造成内存泄漏

int main()
{
    // init a variable under int type.
    int num = 1024;
    // init a pointer under int type.
    int* pointer;
    // extract the RAM address of the variable and assign to pointer.
    pointer = &num;
    // show the value behind the address. *name 是一个取值写法
    print(*pointer);
    // show the address of the value.
    print(pointer << "\n");

    ////////////////////////////////////////////////////////////////////

    // modify the value according to the address instead of the variable name.
    *pointer = 10000;
    // show the original variable "num" to see if the value is changed or not.
    print(num);
    // show the address of the modified num to see if the address remains the same.
    print(pointer << "\n");

    ////////////////////////////////////////////////////////////////////

    char ch = 'a';
    char* ptr_ch = &ch;
    // 有时候如果是字符串类型的指针打印的时候可能回传的不是个一般格式的地址，得强制转换以下地址
    print((void*)ptr_ch);
    // 不过打印出来格式跑偏并不影响一般我们用指针改变量的操作
    *ptr_ch = 'b';
    print(ch << "\n");

    ////////////////////////////////////////////////////////////////////

    // when a pointer is created, make sure that it has some controllable value.
    // or... it might link to some very dangerous value that crash your computer.
    double* ptr = nullptr;
    print(ptr << "\n");

    ////////////////////////////////////////////////////////////////////

    // mind that if the pointer is "void" type, it can only save the address
    void* ptr_void = &num;
    print(ptr_void << "\n");
    // but it can not obtain value from the address.
    
    ////////////////////////////////////////////////////////////////////
    
    // 动态分配指的是在运行到该句代码的时候才会分配内存出来，并对应到指针去
    int arr[5];
    int* ptr_arr = arr;
    int* ptr_new = new int[5];
    delete ptr_new;    // 表示释放内存而不是把这个变量删了
    print(ptr_new << "\n");

    ////////////////////////////////////////////////////////////////////

    // 通过指针遍历打印数组里面的值
    int arrays[] {15, 23, 30, 40, 50};
    int* ptr_arrs = arrays;

    for (int i = 0; i < 5; i++){
        print(*(ptr_arrs + i));
    }
    print("");

    ////////////////////////////////////////////////////////////////////

    // 创建二维数组，通过指针控制
    int* p1 = new int[10];
    int (*p2)[3] = new int[5][3];
    p2[3][2] = 9876;

    for (int i = 0; i < 5; i++){
        for (int j = 0; j < 3; j++){
            print(p2[i][j] << "\t" << *(*(p2 + i) + j));
        }
    }
    print(p2[0] << "\n");

    ////////////////////////////////////////////////////////////////////

    char str[] = {'t', 'h', 'i', 's', 'i', 's', 'm', 'e'};
    print("string: " << str);

    char arr2[] = "that is great";
    print(arr2[5]);

    char* p_str[] = {"first", "second", "third"};
    print("after warning: " << p_str[0]);
    
    const char* aaa = "abc";
    char b[2] = {'a', 'b'};
    print(b);    

    ////////////////////////////////////////////////////////////////////

    int a = 100;
    
    int *pt1 = &a;
    int **pt2 = &pt1;
    int ***pt3 = &pt2;
    int ****pt4 = &pt3;
    int *****pt5 = &pt4;
    int ******pt6 = &pt5;
    int *******pt7 = &pt6;
    int ********pt8 = &pt7;
    int *********pt9 = &pt8;
    int **********pt10 = &pt9;

    print(**********pt10);

    ////////////////////////////////////////////////////////////////////

    std::string* pNorm = new std::string("normal");
    std::vector<std::string*> container2;
    container2.push_back(pNorm);
    container2.push_back(pNorm);

    for (auto i: container2) {
        print(*i);
    }

    *pNorm = "changed";

    for (auto i: container2) {
        print(*i);
    }

    ////////////////////////////////////////////////////////////////////
    print("\n========== Smart pointer [start] ==========");

    // Please reference to "smartPointer.cpp"

    print("========== Smart pointer  [end]  ==========\n");
    ////////////////////////////////////////////////////////////////////

    return 0;
}

