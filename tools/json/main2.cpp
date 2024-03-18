//
// Created by shile on 2022/12/27.
//

/****
 * this project shows how to build a json class from a existing json format string.
 * this is a Plan B of the Json_io project using in ADAS Program.
 * the advantage:
 * 1. the syntax of the JSON format is konwn
 * the disadvantage:
 * 1. if you use the json communicate with python's json class. Because the single quote and the double quote are not
 *  distinguished in the python string literal, format error may occur.
 * 2. Because the double quote is a reserved word in C++, building a correct json format string is not convenient.
 */


#include "json/json.h"
#include <cstdlib>
#include <iostream>
/**
 * \brief Parse a raw string into Value object using the CharReaderBuilder
 * class, or the legacy Reader class.
 * Example Usage:
 * $g++ readFromString.cpp -ljsoncpp -std=c++11 -o readFromString
 * $./readFromString
 * colin
 * 20
 */
int main() {
    std::string rawJson = "{\"mykey\" : \"myvalue\"}";
    // const std::string rawJson = "{\"Age\": 20, \"Name\": \"colin\"}";
    // const std::string rawJson = "{\"encoding\" : \"UTF-8\", \"plug-ins\" : [\"python\", \"c++\", \"ruby\"\n"
    //                             "        ], \"indent\" : { \"length\" : 3, \"use_space\": true } }";
    // std::const_pointer_c>()
    const int rawJsonLength = static_cast<int>(rawJson.length());
    bool shouldUseOldWay = true;
    JSONCPP_STRING err;
    Json::Value root;

    if (shouldUseOldWay) {
        Json::Reader reader;
        reader.parse(rawJson, root);
    } else {
        Json::CharReaderBuilder builder;
        Json::CharReader* reader(builder.newCharReader());
        if (!reader->parse(rawJson.c_str(), rawJson.c_str() + rawJsonLength, &root,
                           &err)) {
            std::cout << "error" << std::endl;
            return EXIT_FAILURE;
        }
        delete reader;
    }
    // const std::string name = root["plug-ins"][0].asString();
    // const int age = root["indent"]["length"].asInt();

    std::cout << root["mykey"].asString() << std::endl;
    // std::cout << name << std::endl;
    // std::cout << age << std::endl;
    return EXIT_SUCCESS;
}
