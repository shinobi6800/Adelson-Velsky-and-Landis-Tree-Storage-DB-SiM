#pragma once
#include <string>

class AVLTree {
public:
    void insert(const std::string& key, const std::string& value);
    std::string lookup(const std::string& key);
    void display();
    void saveToFile(const std::string& filename);
    void loadFromFile(const std::string& filename);
};
