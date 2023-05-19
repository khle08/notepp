
#include <string>
#include <sstream>
#include <iostream>

#include <cpuid.h>


std::string GetCPUId()
{
    std::string strCPUId;

    unsigned int level = 1;
    unsigned eax = 3 /* processor serial number */, ebx = 0, ecx = 0, edx = 0;
    __get_cpuid(level, &eax, &ebx, &ecx, &edx);

    // byte swap
    int first = ((eax >> 24) & 0xff) | ((eax << 8) & 0xff0000) | ((eax >> 8) & 0xff00) | ((eax << 24) & 0xff000000);
    int last = ((edx >> 24) & 0xff) | ((edx << 8) & 0xff0000) | ((edx >> 8) & 0xff00) | ((edx << 24) & 0xff000000);

    // tranfer to string
    std::stringstream ss;
    ss << std::hex << first;
    ss << std::hex << last;
    ss >> strCPUId;

    return strCPUId;
}


int main()
{
	std::string s = GetCPUId();
	std::cout << "cpu id: " << s << std::endl;

	return 0;
}