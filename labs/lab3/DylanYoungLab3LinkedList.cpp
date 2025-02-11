#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "./include/doctest.h"
#include "node.h"
#include <stdexcept>
#include <iostream>

// Function to build a linked list from an array
Node *build_linked_list(const int arr[], int size)
{
    if (size == 0)
        return nullptr;
    Node *head = new Node(arr[0]);
    Node *current = head;
    for (int i = 1; i < size; ++i)
    {
        current->next = new Node(arr[i]);
        current = current->next;
    }
    return head;
}

// Test for build_linked_list
TEST_CASE("build_linked_list")
{
    int arr[] = {1, 2, 3, 4, 5};
    Node *head = build_linked_list(arr, 5);
    REQUIRE(head != nullptr);
    REQUIRE(head->data == 1);
    REQUIRE(head->next->data == 2);
    REQUIRE(head->next->next->data == 3);
    delete_entire_linked_list(head);
}

// Function to print a linked list
void print_linked_list(Node *root)
{
    Node *current = root;
    while (current)
    {
        std::cout << current->data << " -> ";
        current = current->next;
    }
    std::cout << "nullptr\n";
}

// Test for print_linked_list
TEST_CASE("print_linked_list")
{
    int arr[] = {10, 20, 30};
    Node *head = build_linked_list(arr, 3);
    print_linked_list(head);
    delete_entire_linked_list(head);
}

// Function to delete the entire linked list
void delete_entire_linked_list(Node *&root) // Changed **root to *&root
{
    while (root)
    {
        Node *temp = root;
        root = root->next;
        delete temp;
    }
}

// Test for delete_entire_linked_list
TEST_CASE("delete_entire_linked_list")
{
    int arr[] = {7, 8, 9};
    Node *head = build_linked_list(arr, 3);
    delete_entire_linked_list(head);
    REQUIRE(head == nullptr);
}

// Function to retrieve a node's data by index
int get_linked_list_data_item_value(Node *root, int node_number)
{
    int count = 0;
    while (root)
    {
        if (count == node_number)
            return root->data;
        root = root->next;
        count++;
    }
    throw std::out_of_range("Node number out of range");
}

// Test for get_linked_list_data_item_value
TEST_CASE("get_linked_list_data_item_value")
{
    int arr[] = {100, 200, 300};
    Node *head = build_linked_list(arr, 3);
    REQUIRE(get_linked_list_data_item_value(head, 0) == 100);
    REQUIRE(get_linked_list_data_item_value(head, 1) == 200);
    REQUIRE(get_linked_list_data_item_value(head, 2) == 300);
    delete_entire_linked_list(head);
}

// Function to delete a node at a specific index
void delete_list_element(Node *&root, int node_number) // Changed root to reference
{
    if (!root || node_number < 0)
        return;

    if (node_number == 0)
    {
        Node *temp = root;
        root = root->next;
        delete temp;
        return;
    }

    Node *current = root;
    for (int i = 0; current->next && i < node_number - 1; ++i)
    {
        current = current->next;
    }

    if (!current->next) // If out of bounds
        return;

    Node *temp = current->next;
    current->next = temp->next;
    delete temp;
}

// Test for delete_list_element
TEST_CASE("delete_list_element")
{
    int arr[] = {5, 10, 15, 20};
    Node *head = build_linked_list(arr, 4);
    delete_list_element(head, 1);
    REQUIRE(head->data == 5);
    REQUIRE(head->next->data == 15);
    delete_entire_linked_list(head);
}