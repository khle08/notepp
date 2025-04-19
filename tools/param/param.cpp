
#include "param.h"


int strReplace(std::string& str, const std::string& from, const std::string& to)
{
    size_t start_pos = str.find(from);
    if(start_pos == std::string::npos)
        return -1;

    str.replace(start_pos, from.length(), to);
    return 0;
}


std::string strConcat(std::vector<std::string> strVec)
{
    std::stringstream stream;
    for (int i = 0; i < strVec.size(); i++) {
        stream << strVec[i];
    }
    return stream.str();
}


int strSplit(std::string& str, std::string delim, std::vector<std::string>& strVec)
{
    auto start = 0U;
    auto end = str.find(delim);
    while (end != std::string::npos)
    {
        strVec.push_back(str.substr(start, end - start));
        // print(str.substr(start, end - start));
        start = end + delim.length();
        end = str.find(delim, start);
    }
    strVec.push_back(str.substr(start, end - start));
    return 0;
}


int strip(std::string& str)
{
    while (str.find(" ") != std::string::npos) {
        strReplace(str, " ", "");  // get rid of all space
    }

    while (str.find("\"") != std::string::npos) {
        strReplace(str, "\"", "");  // get rid of all "
    }
    return 0;
}


Param::Param(std::string file, bool save)
        : fileName(file), saveBack(save)
{
    std::ifstream inFile(file, std::ios::in);
    std::string line, prev;
    int repeat = 0;

    int cnt = 0;
    while (true) {
        // Skip the first line
        if (cnt == 0) {
            getline(inFile, line);
            std::vector<std::string> p; strSplit(line, ":", p);
            if (p[0].find("#") != std::string::npos) {
                // Ignore the line if there are "#" has key
                continue;
            }

            // =========================================================
            // If the value behind ":" is not empty
            if (p[0] != "") {
                // Get rid of "space" and ' " ' here
                strip(p[0]); strip(p[1]);
                params[p[0]] = (p[1] == "") ? "null" : p[1];
                totalParam += 1;
            }
            // print(line);  // DEBUG ONLY
            // =========================================================

            prev = line;
            cnt += 1;
            continue;
        }

        if (cnt == 0) {
            print("[ERROR] invalid parameter format in the file");
            break;
        }

        getline(inFile, line);

        if (line == prev) {
            repeat += 1;
            // if there are more than maxSpace repeated things, stop reading file
            if (repeat > maxSpace) {
                break;
            }
            continue;
        }

        std::vector<std::string> p; strSplit(line, ":", p);
        if (p[0].find("#") != std::string::npos) {
            // Ignore the line if there are "#" has key
            continue;
        }

        // =============================================================
        if (p[0] != "") {
            strip(p[0]); strip(p[1]);
            params[p[0]] = (p[1] == "") ? "null" : p[1];
            totalParam += 1;
        }
        // print(line);  // DEBUG ONLY
        // =============================================================

        prev = line;
    }

    // // DEBUG ONLY
    // print(params.size());
    // std::map<std::string, std::string>::iterator it;
    // for (it = params.begin(); it != params.end(); it++) {
    //     print(it->first << "| : |" << it->second);
    // }
}


Param::~Param()
{
    saveParams();
}


int Param::keyExist(std::string key)
{
    int res = std::distance(params.begin(), params.find(key));
    if (res == params.size()) {
        return -1;
    }
    return res;
}


std::string Param::getValue(std::string key)
{
    int res = keyExist(key);
    if (res == -1) {
        return "null";
    }

    return params[key];
}


int Param::updateValue(std::string key, std::string value)
{
    int res = keyExist(key);
    if (res == -1) {
        return -1;  // key does not exist, failed to update
    }

    params[key] = value;
    return 0;
}


int Param::setValue(std::string key, std::string value)
{
    int res = keyExist(key);
    if (res == -1) {
        if (getValue("CONFIG_FIX_PARAM_NUM") == "true") {
            // Refuse to add new parameter to the class
            return -1;
        }

        params[key] = value;
        totalParam += 1;
        return 0;
    }

    params[key] = value;
    // key already exists, same func as "updateValue"
    return -1;
}


int Param::saveParams()
{
    std::string upd = getValue("CONFIG_UPDATE");

    if (saveBack || upd == "true") {
        std::vector<std::string> outLines;

        std::string line, prev;
        std::ifstream inFile(fileName, std::ios::in);
        bool hasEmpty = false;
        int repeat = 0;

        int cnt = 0;
        while (true) {
            // Skip the first line
            if (cnt == 0) {
                getline(inFile, line);
                std::vector<std::string> p; strSplit(line, ":", p);
                if (p[0].find("#") != std::string::npos) {
                    outLines.push_back(line + "\n");
                    continue;
                }

                // =========================================================
                if (p[0] != "") {
                    strip(p[0]); strip(p[1]);
                    std::string update = p[0] + " : " + params[p[0]];
                    outLines.push_back(update + "\n");
                } else {
                    outLines.push_back("\n");
                }
                // print(line);  // DEBUG ONLY
                // =========================================================

                prev = line;
                cnt += 1;
                continue;
            }

            getline(inFile, line);

            if (line == prev) {
                repeat += 1;
                // if there are more than 20 repeated things, stop reading file
                if (repeat > maxSpace) {
                    break;
                }
                if (!hasEmpty) {
                    outLines.push_back(line + "\n");
                    hasEmpty = true;
                }
                continue;
            } else {
                hasEmpty = false;
            }

            std::vector<std::string> p; strSplit(line, ":", p);
            if (p[0].find("#") != std::string::npos) {
                outLines.push_back(line + "\n");
                continue;
            }

            // =============================================================
            if (p[0] != "") {
                strip(p[0]); strip(p[1]);
                std::string update = p[0] + " : " + params[p[0]];
                outLines.push_back(update + "\n");
            } else {
                outLines.push_back("\n");
            }
            // print(line);  // DEBUG ONLY
            // =============================================================

            prev = line;
        }

        std::ofstream outFile(fileName, std::ios::out);
        for (int i = 0; i < outLines.size() - 1; i++) {
            outFile << outLines[i];
        }
        outFile.close();
    }

    return 0;
}

