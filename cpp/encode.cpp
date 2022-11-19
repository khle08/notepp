// https://www.cnblogs.com/bigben0123/p/13728595.html
// https://sf-zhou.github.io/programming/chinese_encoding.html
// https://blog.csdn.net/wanggao_1990/article/details/113973730

#include <codecvt>
#include <fstream>
#include <iostream>

#define print(x) std::cout << x << std::endl


int main() {
    const std::locale utf8( std::locale(), new std::codecvt_utf8<wchar_t> );
    const std::wstring love_cpp = L"\x6211\x7231""C++";  // 我爱C++

    std::wcout.imbue(utf8);
    std::wcout << love_cpp << std::endl;  // 输出 "我爱C++"
    std::wcout << love_cpp.length() << std::endl;  // 输出 5
    std::wcout << love_cpp.substr(0, 2) << std::endl;  // 输出 "我爱"

    const auto k_output_filename = "test_02.txt";
    std::wofstream f_out(k_output_filename, std::ios::out);
    f_out.imbue(utf8);
    f_out << love_cpp << std::endl;
    f_out.close();

    std::wifstream f_in(k_output_filename, std::ios::in);
    f_in.imbue(utf8);
    std::wstring value;
    f_in >> value;
    std::wcout << (value == love_cpp ? "Yes": "Opps") << std::endl;  // 输出 "Yes"
    f_in.close();
}