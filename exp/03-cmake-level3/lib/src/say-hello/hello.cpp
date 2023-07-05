#include "hello.hpp"
#include <iostream>

int hello::say_hello() {
	std::cout << "[hello.cpp] testing ..." << std::endl;
	return 0;
}


TestAsync::TestAsync()
{

}


TestAsync::~TestAsync()
{

}


bool TestAsync::incr(int& x)
{
    std::this_thread::sleep_for(std::chrono::seconds(2));
    x++;
    return true;
}


bool TestAsync::wrapper()
{
	append("test");

	return true;
}


bool TestAsync::append(std::string s)
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
    strVec.push_back(s);
    return true;
}


bool TestAsync::env()
{
	std::cout << "[TestAsync::env] testing ..." << std::endl;

	chtime t1, t2;
	t1 = std::chrono::high_resolution_clock::now();
	// =================================================================
	std::cout << "ori i: " << i << std::endl;
	std::future<bool> incrAsync = std::async(std::launch::async, incr, std::ref(i));
	this->wrapper("abc");
	bool res = incrAsync.get();
	std::cout << "mdf i: " << i << std::endl;
	// =================================================================
	t2 = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff = t2 - t1;

	std::cout << "[TestAsync::env] use: " << diff.count() << std::endl;
	return true;
}
