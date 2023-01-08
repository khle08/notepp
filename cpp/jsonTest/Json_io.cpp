//
// Created by shile on 2022/12/27.
//
/***
 * this project shows the example of adding
 * 1. ordinary items
 * 2. list itesms
 * 3. existing json class
 * to a new json class.
 */


#include "json/json.h"
#include <iostream>
/** \brief Write the Value object to a stream.
 * Example Usage:
 * $g++ streamWrite.cpp -ljsoncpp -std=c++11 -o streamWrite
 * $./streamWrite
 * {
 *     "Age" : 20,
 *     "Name" : "robin"
 * }
 */
int main() {
    Json::Value root;
    Json::Value root2;
    Json::Value root3;
    Json::StreamWriterBuilder builder;
    Json::StreamWriter* writer(builder.newStreamWriter());
    std::vector<int> m;
    m.push_back(1);
    m.push_back(2);

    // ordinary items
    root["Name"] = "robin";
    root2["Name"] = "robin";
    root["Age"] = 20;

    // json class items
    root["sub"] = root2;

    // list items
    root["li"].append(1);
    root["li"].append("1000000000000000000000");
    root["li"].append(1.5f);

    // list items
    root3.append(1);
    root3.append(2);
    root3.append(3);

    // add json class items as list items
    root["S"].append(root3);
    root["S"].append(root3);

    // showing the final json string
    std::cout<<  root.getMemberNames()[2]<<std::endl;
    //root["l2"].
    writer->write(root, &std::cout);
    delete writer;
    return EXIT_SUCCESS;
}
