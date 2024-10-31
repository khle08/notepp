#include "Model.h"

Model::Model(int id, const std::string& data) : id_(id), data_(data) {}

int Model::getId() const {
    return id_;
}

std::string Model::getData() const {
    return data_;
}
