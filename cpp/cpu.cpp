
#include <cstdio>
#include <memory>
#include <string>
#include <sstream>
#include <fstream>    // getUUID
#include <iostream>
#include <stdexcept>  // executeCommand

#include <stdio.h>
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

// [!] Useless
// static inline void native_cpuid(unsigned int *eax, unsigned int *ebx,
//                                 unsigned int *ecx, unsigned int *edx)
// {
//         /* ecx is often an input as well as an output. */
//         asm volatile("cpuid"
//             : "=a" (*eax),
//               "=b" (*ebx),
//               "=c" (*ecx),
//               "=d" (*edx)
//             : "0" (*eax), "2" (*ecx));
// }


// int cpuid2()
// {
//     unsigned eax, ebx, ecx, edx;

//     eax = 1; /* processor info and feature bits */
//     native_cpuid(&eax, &ebx, &ecx, &edx);

//     printf("stepping %d\n", eax & 0xF);
//     printf("model %d\n", (eax >> 4) & 0xF);
//     printf("family %d\n", (eax >> 8) & 0xF);
//     printf("processor type %d\n", (eax >> 12) & 0x3);
//     printf("extended model %d\n", (eax >> 16) & 0xF);
//     printf("extended family %d\n", (eax >> 20) & 0xFF);

//     /* EDIT */
//     eax = 3; /* processor serial number */
//     native_cpuid(&eax, &ebx, &ecx, &edx);

//     /** see the CPUID Wikipedia article on which models return the serial 
//         number in which registers. The example here is for 
//         Pentium III */
//     printf("serial number 0x%08x%08x\n", edx, ecx);

//     return 0;
// }


void getPSN(char *PSN)
{
    int varEAX, varEBX, varECX, varEDX;
    char str[9];
    //%eax=1 gives most significant 32 bits in eax 
    __asm__ __volatile__ ("cpuid"   : "=a" (varEAX), "=b" (varEBX), "=c" (varECX), "=d" (varEDX) : "a" (1));
    sprintf(str, "%08X", varEAX); //i.e. XXXX-XXXX-xxxx-xxxx-xxxx-xxxx
    sprintf(PSN, "%C%C%C%C-%C%C%C%C", str[0], str[1], str[2], str[3], str[4], str[5], str[6], str[7]);
    //%eax=3 gives least significant 64 bits in edx and ecx [if PN is enabled]
    __asm__ __volatile__ ("cpuid"   : "=a" (varEAX), "=b" (varEBX), "=c" (varECX), "=d" (varEDX) : "a" (3));
    sprintf(str, "%08X", varEDX); //i.e. xxxx-xxxx-XXXX-XXXX-xxxx-xxxx
    sprintf(PSN, "%s-%C%C%C%C-%C%C%C%C", PSN, str[0], str[1], str[2], str[3], str[4], str[5], str[6], str[7]);
    sprintf(str, "%08X", varECX); //i.e. xxxx-xxxx-xxxx-xxxx-XXXX-XXXX
    sprintf(PSN, "%s-%C%C%C%C-%C%C%C%C", PSN, str[0], str[1], str[2], str[3], str[4], str[5], str[6], str[7]);
}


int main()
{
    char PSN[30]; //24 Hex digits, 5 '-' separators, and a '\0'
    getPSN(PSN);
    printf("%s\n", PSN); //compare with: lshw | grep serial:

    // [!] Useless
    // cpuid2();

    // std::string s = GetCPUId();
    // print("cpu id: " << s);


    // std::string uuid = getUUID();
    // print("random uuid: " << uuid);

    // std::string uuidt = executeCommand("uuidgen -t");
    // print("time-base uuid: " << uuidt);

    // std::string output = executeCommand("sudo dmidecode -s system-uuid");
    // print("system uuid: " << output);

    // std::string genuuid = generateUUID();
    // print("Generated UUID: " << genuuid);
	return 0;
}