// this project shows the example of adding
// 1. ordinary items
// 2. list itesms
// 3. existing json class
// to a new json class.

// To quickly run code with g++ use this cmd below:
//     g++ streamWrite.cpp -ljsoncpp -std=c++11 -o streamWrite
//     ./streamWrite

#include <vector>
#include <fstream>
#include <iostream>
#include "json/json.h"

#define print(x) std::cout << x << std::endl;


int main() {
    Json::Value j1, j2, j3;

    j1["Name"] = "abc";
    j1["age"] = 20;
    // Output:
    // {
    //     "Name" : "abc",
    //     "age" : 20
    // }

    // A vector can not be saved in json format directly like this
    // std::vector<int> v;
    // v.push_back(1);
    // v.push_back(2);
    // j1["vec"] = v;
    
    // But, list of object can be saved in this way below:
    j1["vec"].append(1);
    j1["vec"].append(2);
    // Output:
    // {
    //     "Name" : "abc",
    //     "age" : 20,
    //     "vec" : 
    //     [
    //         1,
    //         2
    //     ]
    // }
    print("===== start =====");
    print("j1[\"vec\"][1] = " << j1["vec"][1]);  // out: 2
    print("=====  end  =====\n");

    // Json also can be assigned into another json
    j2["data"] = 12345;
    j1["j2"] = j2;
    // Output:
    // {
    //     "Name" : "abc",
    //     "age" : 20,
    //     "j2" : 
    //     {
    //         "data" : 12345
    //     },
    //     "vec" : 
    //     [
    //         1,
    //         2
    //     ]
    // }
    print("===== start =====");
    print("j1[\"j2\"][\"data\"] = " << j1["j2"]["data"]);  // out: 12345
    print("=====  end  =====\n");

    // Json value can also be used as vector. Once json obj is append with value,
    // it will no longer be json data but simply vector, which means that the value
    // can not be applied to the other keys.
    j3.append(31);
    j3.append(32);
    j3.append(33);
    // j3["other"] = "other data that saved with json key";  // will be compiled but failed to execute
    print("===== start =====");
    print("j3: \n" << j3);
    print("=====  end  =====\n");

    print("===== start =====");
    print("j1: \n" << j1);
    print("=====  end  =====\n");


    // This method can also print out the json data in either terminal
    // or a file when executing
    std::ofstream fileWrite("file.txt");
    
    Json::StreamWriterBuilder builder;
    Json::StreamWriter* writer(builder.newStreamWriter());
    // writer->write(j1, &std::cout);    // terminal
    writer->write(j1, &fileWrite);       // file (indention == tab)
    delete writer;

    // Json::StyledWriter writer;        // file (indention == space x 4)
    // fileWrite << writer.write(j1);

    fileWrite.close();


    // To read the json data back to json object
    std::ifstream fileRead("file.txt");
    Json::Value j4;
    fileRead >> j4;
    print("===== start =====");
    print("j4: \n" << j4);
    print("=====  end  =====\n");

    return EXIT_SUCCESS;
}
