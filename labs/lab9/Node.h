#pragma once
#include <string>
#include <memory>
#include <iostream>

using namespace std;

struct Node {
    string name;
    Node(string name) : name{name} {}
    
    // We'll make two versions:
    // 1. With shared_ptr (creates memory leak with cycles)
    shared_ptr<Node> next_shared;
    
    // 2. With weak_ptr (solves the cycle problem)
    weak_ptr<Node> next_weak;
    
    ~Node() { 
        cout << "Node [" << name << "] destructor" << endl; 
    }
};
