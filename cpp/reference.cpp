#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#define print(x) std::cout << x << std::endl


/*
使用引用的时候不需要测试其有效性，只需要注意引用的值如果是个常量，则需要注记
const double& d = 12.3;

否则报错，所以引用比指针的效率高。引用并不是创建新的对象，而是对一个已经存在的
变量另起一个别名，把引用变量当作参数时，函数将处理原始数据，因此当数据占用内存
较多比例的时候，建议引用参数而非另外赋值（拷贝）。

注意
引用操作过程中千万注意不要返回局部变量的引用，因为局部变量一旦那个模块执行完毕
内存就会被回收，回收的是存取内存的唯一权限失去了，变成大家都能存取，里面的值很
可能随时被其他东西取代，在引用的钩子还没和内存脱离的情况下，很可能随时找到其他
本来不属于这个变量的值出现，这时候程序就崩溃了。
 */


int& sum()
{
	int num = 10;
	int& rNum = num;
	return rNum;
}


int& func(int& a, int& b)
{
	// const int& func(int& a, int& b)
	a++;
	b++;
}


void swap_copy(int, int);
void swap_ptr(int*, int*);
void swap_ref(int&, int&);


int main()
{
	// init a variable under int type.
	int num = 1024;
	int& refNum = num;
	print(refNum);
	print("");

	refNum = 2048;
	print(num);

	// 指向常量的引用是错误写法
	// i.e. double& ref = 100;
	// 应该写成如下形式，在前面添加 "const"
	const double& ref = 100;
	print(ref);
	print("");

	int n1 = 3, n2 = 9;
	swap_copy(n1, n2);
	print(n1 << "\t" << n2);

	swap_ptr(&n1, &n2);
	print(n1 << "\t" << n2);

	swap_ref(n1, n2);
	print(n1 << "\t" << n2);
	print("");

	// 
	int& res = sum();
	int x = 1000;
	int y = 2000;
	int z = 10000;
	print(res);
	print("");

	// 注意如果一个函数没有设定要返回什么值，那就默认返回最后一个处理完的那个数字
	int& ans = func(n1, n2);
	// const int& ans = func(n1, n2);   // 避免能对函数赋值的话就用 const 锁定数字
	print(ans);
	// 这是在C++独有的操作方式，可以对函数赋值，而如果函数结果有一个引用，这时候该结果也会同时被修改
	func(n1, n2) = 9999;
	print(ans);

	return 0;
}


void swap_copy(int a, int b)
{
	int temp = a;
	a = b;
	b = temp;
}


void swap_ptr(int* a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}


void swap_ref(int& a, int& b)
{
	// 可以直接传递某个对象，而不是复制，但写法和最基础的函数一样
	// 不过要注意的是，在某些函数里面我们可能并不希望传入的参数被修改
	// 但同时又想直接调用引用的参数，这时候就需要用下面方法传入参数：
	// void swap_ref(const int& a, const int& b)...

	int temp = a;
	a = b;
	b = temp;
}