#ifndef HELLO_HPP_INCLUDED
#define HELLO_HPP_INCLUDED

#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include <future>
#include <iostream>

typedef std::chrono::high_resolution_clock::time_point chtime;


namespace hello {
	int say_hello();
}


class TestAsync
{
public:
	TestAsync();
	~TestAsync();

	static bool incr(int& x);
	static bool wrapper();

	bool append(std::string s);
	bool env();

private:
	int i = -1;
	std::vector<std::string> strVec = {};
};


#endif