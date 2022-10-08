#include <iostream>
#include <cmath>

#define print(x) std::cout << x << std::endl


// before actually defining a function, it is a good habit to 
// make a statement in advance even though this is not necessary.
int sum(int, int);    // 函数原型
void calcCube();
void calcCylinder();

/*
内联函数：是C++语言独有的新技术，为了提高程序运行速度所作的一项改进，
		和常规的方法差异在于编写方式，本来在 main 函数里面执行代码，
		遇到新的函数是通过查找该函数的地址去读取函数里面的机制，而
		内联函数则直接在运行前就直接把需要的代码复制到 main 函数里面，
		因此执行过程中无需查找地址。如果执行函数代码的时间比处理函数调用机制
		的时间长，则节省的时间将只占整个过程的很小一部分，此trick就
		相对而言失效了。
 */

void change(int& num)
{
	// 传入参数的引用，这样在函数里改参数，传进来的原参数也能被修改
	num++;
}


void testing(double arr[], int len)
{
	// 定义的数组名+[] 就直接是这个数组的地址，就如同这里传入的第一个参数
	// The values that saved in the array can be modified.
	// If we do not want to modify the array, use "const double arr[]" instead.
	print(arr[0]);
}


int power(int a, int b)
{
	int res = 1;
	for (int i = 0; i < b; i++)
	{
		res *= a;
	}
	return res;
}


int main()
{
	double arr[4] = {3.3, 5.2, 6.2, 2.9};
	print(arr);
	testing(arr, 4);
	print("");

	// 函数指针定义方式
	print(power(3, 4));
	int (*ptrPower)(int, int);
	ptrPower = power;
	// both calling method is fine to use.
	print(ptrPower(3, 5));
	print((*ptrPower)(3, 3));
	print("");


	int res = sum(5, 6);
	print(res);
	change(res);
	print(res);

	// when "while" condition is not 0, the loop will keep going on.
	int choice = -1;
	while (choice)
	{
		print("1. Cube");
		print("2. Cylinder");
		print("0. Exit");

		std::cin >> choice;
		switch (choice)
		{
		case 1:
			calcCube();
			break;
		case 2:
			calcCylinder();
			break;
		}
	}
	return 0;
}


int sum(int a, int b)
{
	// 在 C++ 中无法返回数组类型，如果真的要返回，只能以复杂类型放在结构体里面操作
	// 或者返回数组的指针
	return a + b;
}


void calcCube()
{
	double length, width, height;
	print("Please enter length, width, and height: ");
	std::cin >> length >> width >> height;
	double v = length * width * height;
	print(v);
}


void calcCylinder()
{
	double radius, height;
	print("Please enter radius and height");
	std::cin >> radius >> height;
	double pi = 4 * atan(1.0);
	double v = pi * pow(radius, 2) * height;
	print(v);
}
