#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>

#define print(x) std::cout << x << std::endl


int main()
{
	// create an empty vector initialized with 0.
	std::vector<int> vec1(5);
	for (int x: vec1){
		print("vec1: " << x);
	}
	// create another vector inherit from the existing vector.
	std::vector<int> vec2(vec1);
	print(vec2[4]);
	print("");

	// create a list and put it into a new vector.
	std::list<std::string> listArr;
	listArr.push_back("1st");
	listArr.push_back("2nd");
	listArr.push_back("3rd");
	listArr.push_back("4th");
	std::vector<std::string> vec3(listArr.begin(), listArr.end());
	for (int i = 0; i < vec3.size(); i++){
		print("operator : " << vec3.operator[](i));
	}

	print("");

	std::vector<double> vecDouble = {98.5, 67.9, 43.6, 32.9};
	vecDouble.push_back(100.8);

	for (int i = 0; i < vecDouble.size(); i++){
		print("vecDouble[" << i << "] : " << vecDouble[i]);
	}

	print("");

	// vecDouble.erase(vecDouble.begin());
	std::remove(vecDouble.begin(), vecDouble.end(), vecDouble[0]);

	for (int i = 0; i < vecDouble.size(); i++){
		print("vecDouble[" << i << "] : " << vecDouble[i]);
	}

	print("");

	// use the sort function which is defined in <algorithm>
	sort(vecDouble.begin(), vecDouble.end());
	reverse(vecDouble.begin(), vecDouble.end());

	// general method to iterate through all values in a vector.
	std::vector<double>::iterator it;
	for (it = vecDouble.begin(); it != vecDouble.end(); ++it){
		print(&it << " : " << *it);
	}

	print("");

	// resize the length of a vector
	vecDouble.resize(10);
	print("size of vecDouble : " << vecDouble.size());
	print("max size of vecDouble : " << vecDouble.max_size());

	print("");

	double arrs[3][2][4];
	print(arrs[0][0][0]);

	print("");

	std::vector<int> vvv = {1, 2, 3, 4, 5};
	std::vector<int> vee = {11, 12, 13, 14};
	vvv.assign(vee.begin(), vee.end());
	for (int v: vvv) {
		print(v);
	}

	print("");

	static float fff[3 * 3 * 1];
	for (int i = 0; i < sizeof(fff) / 4; i++) {
		fff[i] = i + 1;
	}
	fff[6] = 99;

	std::vector<float> vf(fff, fff + 1 * 3 * 4);
	for (float f: vf) {
		print(f);
	}

	return 0;
}