#pragma once

#include <iostream>

class LinkedList
{
public:
    struct Node
    {
        int data;
        Node *next;

        Node(int value) : data(value), next(nullptr) {}
        ~Node() = default;

        // Disable copying for Node to prevent accidental deep copies
        Node(const Node &) = delete;
        Node &operator=(const Node &) = delete;
    };

    // Constructor
    LinkedList();

    // Copy constructor
    LinkedList(const LinkedList &other);

    // Destructor
    ~LinkedList();

    // Member functions
    void build_from_array(const int arr[], int size);
    void print() const;
    void delete_ith_node(int i);
    bool has_positive_prefix_sum() const;
    bool has_negative_prefix_sum() const;
    void perform_pointer_jumping();
    int get_value_at(int index) const;

private:
    Node *head;
    Node *tail; // To track the last node for pointer jumping

    void delete_entire_list();
};