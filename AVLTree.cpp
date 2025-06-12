#include "AVLTree.hpp"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <nlohmann/json.hpp> // Include this if using vcpkg or local json.hpp

using json = nlohmann::json;
using namespace std;

//DB simulation using AVL Trees  Intergratiion with JSON.
//Mannnnnnnnnnnnnnnnnnnnnnn
struct Node {
    string key, value;
    int height;
    Node* left;
    Node* right;

    Node(const string& k, const string& v)
        : key(k), value(v), height(1), left(nullptr), right(nullptr) {}
};

class AVLTreeImpl {
public:
    Node* root = nullptr;

    int height(Node* n) {
        return n ? n->height : 0;
    }

    int balanceFactor(Node* n) {
        return n ? height(n->left) - height(n->right) : 0;
    }

    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = 1 + max(height(y->left), height(y->right));
        x->height = 1 + max(height(x->left), height(x->right));

        return x;
    }

    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = 1 + max(height(x->left), height(x->right));
        y->height = 1 + max(height(y->left), height(y->right));

        return y;
    }

    Node* insert(Node* node, const string& key, const string& value) {
        if (!node) return new Node(key, value);

        if (key < node->key)
            node->left = insert(node->left, key, value);
        else if (key > node->key)
            node->right = insert(node->right, key, value);
        else {
            node->value = value; // Update if key exists
            return node;
        }

        node->height = 1 + max(height(node->left), height(node->right));

        int balance = balanceFactor(node);

        // Left Left
        if (balance > 1 && key < node->left->key)
            return rightRotate(node);

        // Right Right
        if (balance < -1 && key > node->right->key)
            return leftRotate(node);

        // Left Right
        if (balance > 1 && key > node->left->key) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // Right Left
        if (balance < -1 && key < node->right->key) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    string lookup(Node* node, const string& key) {
        if (!node) return "Not found";

        if (key < node->key)
            return lookup(node->left, key);
        else if (key > node->key)
            return lookup(node->right, key);
        else
            return node->value;
    }

    void inorder(Node* node) {
        if (!node) return;
        inorder(node->left);
        cout << node->key << " : " << node->value << endl;
        inorder(node->right);
    }

    void save(Node* node, json& j) {
        if (!node) return;
        save(node->left, j);
        j[node->key] = node->value;
        save(node->right, j);
    }

    void clear(Node* node) {
        if (!node) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }
};

// Global implementation instance
static AVLTreeImpl impl;

// Public AVLTree class methods
void AVLTree::insert(const string& key, const string& value) {
    impl.root = impl.insert(impl.root, key, value);
}

string AVLTree::lookup(const string& key) {
    return impl.lookup(impl.root, key);
}

void AVLTree::display() {
    cout << "Inorder Traversal:\n";
    impl.inorder(impl.root);
}

void AVLTree::saveToFile(const string& filename) {
    json j;
    impl.save(impl.root, j);
    ofstream out(filename);
    out << j.dump(4);
    out.close();
}

void AVLTree::loadFromFile(const string& filename) {
    ifstream in(filename);
    if (!in.is_open()) {
        cerr << "Could not open file: " << filename << endl;
        return;
    }

    json j;
    in >> j;
    in.close();

    impl.clear(impl.root);
    impl.root = nullptr;

    for (auto& [k, v] : j.items()) {
        insert(k, v);
    }
}
