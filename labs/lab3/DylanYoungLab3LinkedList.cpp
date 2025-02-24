#include "node.h"
#include <stdexcept>

LinkedList::LinkedList() : head(nullptr), tail(nullptr) {}

LinkedList::LinkedList(const LinkedList &other) : head(nullptr), tail(nullptr)
{
    Node *current = other.head;
    while (current)
    {
        build_from_array(&current->data, 1); // Append one node at a time
        current = current->next;
    }
}

LinkedList::~LinkedList()
{
    delete_entire_list();
}

void LinkedList::build_from_array(const int arr[], int size)
{
    if (size <= 0)
        return;

    head = new Node(arr[0]);
    Node *current = head;
    for (int i = 1; i < size; ++i)
    {
        current->next = new Node(arr[i]);
        current = current->next;
    }
    tail = current;
    tail->next = tail; // Last element points to itself after initialization
}

void LinkedList::print() const
{
    Node *current = head;
    while (current && current != tail->next)
    { // Stop before cycling
        std::cout << current->data << " -> ";
        current = current->next;
    }
    if (current)
        std::cout << current->data << " (cycles)";
    std::cout << "\n";
}

void LinkedList::delete_entire_list()
{
    if (!head)
        return;
    tail->next = nullptr; // Break the cycle
    while (head)
    {
        Node *temp = head;
        head = head->next;
        delete temp;
    }
    tail = nullptr;
}

void LinkedList::delete_ith_node(int i)
{
    if (!head || i < 0)
        return;

    if (i == 0)
    {
        Node *temp = head;
        head = head->next;
        if (!head)
            tail = nullptr;
        else if (temp == tail)
            tail = head; // Update tail if deleting last node
        delete temp;
        return;
    }

    Node *current = head;
    for (int j = 0; j < i - 1 && current->next; ++j)
    {
        current = current->next;
    }
    if (!current->next || current->next == tail->next)
        return;

    Node *temp = current->next;
    current->next = temp->next;
    if (temp == tail)
        tail = current; // Update tail if needed
    delete temp;
}

int LinkedList::get_value_at(int index) const
{
    Node *current = head;
    for (int i = 0; i < index && current && current != tail->next; ++i)
    {
        current = current->next;
    }
    if (!current || current == tail->next)
    {
        throw std::out_of_range("Index out of range");
    }
    return current->data;
}

bool LinkedList::has_positive_prefix_sum() const
{
    int sum = 0;
    Node *current = head;
    while (current && current != tail->next)
    {
        sum += current->data;
        if (sum <= 0)
            return false;
        current = current->next;
    }
    return true;
}

bool LinkedList::has_negative_prefix_sum() const
{
    int sum = 0;
    Node *current = head;
    while (current && current != tail->next)
    {
        sum += current->data;
        if (sum >= 0)
            return false;
        current = current->next;
    }
    return true;
}

void LinkedList::perform_pointer_jumping()
{
    if (!head || !tail)
        return;
    Node *current = head;
    while (current != tail->next)
    {
        current->next = tail;
        current = current->next;
    }
}