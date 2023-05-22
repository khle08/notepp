
#include <cstdio>
#include <memory>
#include <string>
#include <sstream>
#include <fstream>    // getUUID
#include <iostream>
#include <stdexcept>  // executeCommand

#include <cpuid.h>

#define print(x) std::cout << x << std::endl;

#include <random>
#include <chrono>
#include <iomanip>


std::string generateUUID() {
    // Get current time
    auto now = std::chrono::system_clock::now();
    auto timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();

    // Generate a random number
    std::random_device rd;
    std::mt19937_64 generator(rd());
    std::uniform_int_distribution<uint64_t> distribution(0, std::numeric_limits<uint64_t>::max());
    uint64_t randomNum = distribution(generator);

    // Combine timestamp and random number
    uint64_t combined = (timestamp << 32) | (randomNum & 0xFFFFFFFF);

    // Format as UUID
    std::stringstream ss;
    ss << std::hex << std::setfill('0') << std::setw(16) << combined;
    std::string uuid = ss.str();

    // Insert hyphens to match UUID format
    uuid.insert(8, "-");
    uuid.insert(13, "-");
    uuid.insert(18, "-");
    uuid.insert(23, "-");

    return uuid;
}


std::string executeCommand(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}


std::string getUUID()
{
    // std::ifstream uuidFile("sys/class/dmi/id/product_uuid");
    std::ifstream uuidFile("/proc/sys/kernel/random/uuid");
    std::string uuid;
    if (uuidFile.is_open()) {
        std:getline(uuidFile, uuid);
        uuidFile.close();
    }
    return uuid;
}


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
    print("cpu id: " << s);


    std::string uuid = getUUID();
    print("random uuid: " << uuid);

    std::string uuidt = executeCommand("uuidgen -t");
    print("time-base uuid: " << uuidt);

    std::string output = executeCommand("sudo dmidecode -s system-uuid");
    print("system uuid: " << output);

    std::string genuuid = generateUUID();
    print("Generated UUID: " << genuuid);
	return 0;
}