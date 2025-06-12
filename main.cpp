#include <iostream>
#include "AVLTree.hpp"

int main() {
    AVLTree tree;

    tree.insert("apple", "fruit");
    tree.insert("carrot", "vegetable");
    tree.insert("dog", "animal");

    std::cout << "Lookup 'carrot': " << tree.lookup("carrot") << std::endl;

    tree.saveToFile("data.json");

    AVLTree newTree;
    newTree.loadFromFile("data.json");
    newTree.display();

    return 0;
}
