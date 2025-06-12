# 🌳 AVL Tree + JSON Storage in C++

This is a compact C++ project that uses an **AVL Tree** for storing key-value data and saves/loads it with **JSON files**.  
Perfect for building fast, balanced index systems with persistent storage.

---

## 🚀 Features

- ✅ AVL Tree insertion & balancing  
- 🔍 Fast lookup by key  
- 💾 Save to JSON  
- 📂 Load from JSON  
- 📜 Display all entries (in-order traversal)

---

## 🧱 Requirements

- **C++17** or higher
- [`nlohmann/json`](https://github.com/nlohmann/json) — for reading/writing JSON

---

## 📦 Setup

### 🛠 Option 1: Use vcpkg (Recommended)

Install the JSON library:

```bash
vcpkg install nlohmann-json

----Compile with 
g++ -std=c++17 main.cpp AVLTree.cpp -I./path-to-vcpkg/installed/x64-linux/include -o avl

Project Structure
-----------------------
📦 project/
├── main.cpp         // Your main entry point
├── AVLTree.cpp      // Implementation of the AVL Tree
├── AVLTree.hpp      // AVL Tree class interface
├── json.hpp         // (If using single-header JSON)
└── data.json        // Auto-generated file with saved data
                                                                                                            