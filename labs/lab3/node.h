#pragma once

#include <iostream>

struct Node
{
    int data;
    Node *next;

    // Constructor
    Node(int value) : data(value), next(nullptr) {}

    // Disable Copy Constructor & Assignment Operator to avoid accidental deep copies
    Node(const Node &) = delete;
    Node &operator=(const Node &) = delete;

    // Default Destructor (let external functions handle deletion)
    ~Node() = default;
};

// Function declarations
Node *build_linked_list(const int arr[], int size);
void print_linked_list(Node *root);
void delete_entire_linked_list(Node *&root);
int get_linked_list_data_item_value(Node *root, int node_number);
void delete_list_element(Node *&root, int node_number);