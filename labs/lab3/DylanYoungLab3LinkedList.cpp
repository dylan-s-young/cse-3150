#include "node.h"
#include <stdexcept>

LinkedList::LinkedList() : head(nullptr), tail(nullptr) {}

LinkedList::LinkedList(const LinkedList &other) : head(nullptr), tail(nullptr)
{
    // Copy constructor should create a new list with the same values
    if (!other.head)
        return; // Nothing to copy

    // Create an array of values from other list
    int size = 0;
    Node *current = other.head;
    while (current)
    {
        size++;
        current = current->next;
        if (current == other.tail->next)
            break;
    }

    int *values = new int[size];
    current = other.head;
    for (int i = 0; i < size; i++)
    {
        values[i] = current->data;
        current = current->next;
        if (current == other.tail->next)
            break;
    }

    // Build the new list
    build_from_array(values, size);

    delete[] values;
}

LinkedList::~LinkedList()
{
    delete_entire_list();
}

void LinkedList::build_from_array(const int arr[], int size)
{
    if (size <= 0)
        return;

    // Clear existing list first
    delete_entire_list();

    head = new Node(arr[0]);
    Node *current = head;
    for (int i = 1; i < size; ++i)
    {
        current->next = new Node(arr[i]);
        current = current->next;
    }
    tail = current;
    // The last element should point to nullptr in a standard linked list
}

void LinkedList::print() const
{
    Node *current = head;
    while (current)
    {
        std::cout << current->data << " -> ";
        current = current->next;
    }
    std::cout << "nullptr\n";
}

void LinkedList::delete_entire_list()
{
    if (!head)
        return;

    // If there's a cycle, break it first
    if (tail && tail->next)
        tail->next = nullptr;

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
    if (!current->next)
        return;

    Node *temp = current->next;
    current->next = temp->next;
    if (temp == tail)
        tail = current; // Update tail if needed
    delete temp;
}

int LinkedList::get_value_at(int index) const
{
    if (index < 0)
        throw std::out_of_range("Index out of range");

    Node *current = head;
    for (int i = 0; i < index && current; ++i)
    {
        current = current->next;
    }
    if (!current)
    {
        throw std::out_of_range("Index out of range");
    }
    return current->data;
}

bool LinkedList::has_positive_prefix_sum() const
{
    int sum = 0;
    Node *current = head;
    while (current)
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
    while (current)
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
    if (!head || !head->next)
        return;

    // Make all non-tail nodes point to the tail
    Node *current = head;
    while (current != tail)
    {
        Node *next = current->next;
        current->next = tail;
        current = next;
    }

    // Make the tail point to itself to create a cycle
    // This allows accessing the tail value at index 2
    tail->next = tail;
}