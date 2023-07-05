#include <iostream>
#include <vector>
#include <string>
#include <future>
#include <thread>


class MyClass
{
public:
	
	void modifyVecAsync() {
		std::future<void> future = std::async(std::launch::async, &MyClass::modifyVec, this);
		std::future<void> f2 = std::async(std::launch::async, &MyClass::modifyStr, this, "Async");

		future.get();  // wait for the async func to complete
	}

	void modifyVec() {
		for (int i = 0 ; i < 10; i++) {
			vec.push_back(i);
			std::cout << "added " << i << " to the vector" << std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
		}
	}

	void modifyStrAsync() {
		std::future<void> future = std::async(std::launch::async, &MyClass::modifyStr, this, "Async");

		// future.get();  // wait for the async func to complete
	}

	void modifyStr(const std::string& suffix) {
		str += suffix;
		std::cout << "modified string: " << str << std::endl;
	}

private:
	std::vector<int> vec;
	std::string str;
};


int main()
{
	MyClass obj;
	obj.modifyVecAsync();
	obj.modifyStrAsync();

	std::this_thread::sleep_for(std::chrono::seconds(5));

	return 0;
}