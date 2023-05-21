#include <iostream>
#include <stdio.h>
#include <vector>
#include <typeinfo>

#define print(x) std::cout << x << std::endl

using namespace std;

int main(int argc, char** argv)
{
	// cout << "title\n";

	// //print output to user
	// cout << "hello world\n"
	//      << "next line\n"
	//      << "end line" << endl;

	// // Both print method are feasible, but this one is older.
	// printf("stdio.h\n");
	// printf("'' mind that this is not applicable in C++\n");

	int size = 5;
	float ans = 10 % 4;
	print("ans: " << ans);
	std::string str = "0.1";
	const char *str2char = str.c_str();
	print(str2char);

	// char or str 2 number type.
	float i = std::stoi(str2char);
	print(typeid(i).name());
	print("");

	std::string filename = "/home/pa01/桌面/C++/yolov5/models";
	const size_t idx = filename.rfind('\\');
	print("idx: " << idx << " " << std::string::npos);
	std::string dir = filename.substr(0, idx);
	print(dir);

	double array[5];
	print("array[0]: " << array[0]);
	print("array[1]: " << array[1]);
	print("array[2]: " << array[2]);
	print("array[3]: " << array[3]);
	print("");

	print("argc: " << argc);
	print("argv[0]: " << argv[0]);
	print("argv[1]: " << argv[1]);
	print("argv[2]: " << argv[2]);
	print("argv[3]: " << argv[3]);
	print("");

	print("[!] can not run this line.");
	return 0;
}