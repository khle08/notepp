#ifndef MODEL_H
#define MODEL_H

#include <string>

class Model {
public:
    Model(int id, const std::string& data);
    int getId() const;
    std::string getData() const;

private:
    int id_;
    std::string data_;
};

#endif // MODEL_H
