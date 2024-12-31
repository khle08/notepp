
#include <map>
#include <vector>
#include <iostream>


int main() {
    std::map<int, std::string> example = {
        {1, "One"},
        {2, "Two"}, 
        {3, "Three"},
        {42, "Don\'t Panic!!!"}
    };

    std::map<int, std::string>::iterator it = example.begin();
    bool found = false;
    for (it = example.begin(); it != example.end(); it++) {
        if (it->second == "Two") {
            found = true;
            break;
        }
    }

    std::cout << found << std::endl;
    if (found) {
        example.erase(it);
    }

    for (it = example.begin(); it != example.end(); it++) {
        std::cout << it->second << std::endl;
    }
    return 0;
}
