#ifndef _LINKED_LIST_H
#define _LINKED_LIST_H

#include <iostream>

#include "Node.h"

using namespace std;

class LinkedList
{
public:
    Node *root;

    // Default constructor
    LinkedList() : root(nullptr) {}

    // Move constructor
    LinkedList(LinkedList &&other) noexcept : root(nullptr)
    {
        // Take ownership of other's resources
        root = other.root;
        // Set other's pointer to null to avoid double deletion
        other.root = nullptr;
    }

    // Move assignment operator
    LinkedList &operator=(LinkedList &&other) noexcept
    {
        if (this != &other)
        {
            // Clean up existing resources
            this->~LinkedList();

            // Take ownership of other's resources
            root = other.root;

            // Set other's pointer to null to avoid double deletion
            other.root = nullptr;
        }
        return *this;
    }

    void insertAtBeginning(int val)
    {
        Node *newNode = new Node(val);
        newNode->next = root;
        root = newNode;
    }

    void insertAtEnd(int val)
    {
        Node *newNode = new Node(val);
        if (!root)
        {
            root = newNode;
            return;
        }
        Node *current = root;
        while (current->next)
        {
            current = current->next;
        }
        current->next = newNode;
    }

    Node *getLastElement()
    {
        Node *current = root;
        while (current->next)
        {
            current = current->next;
        }
        return current;
    }

    int getSize()
    {
        int size = 0;
        Node *current = root;
        while (current)
        {
            size++;
            current = current->next;
        }
        return size;
    }

    /*
     * -1 if the position is off
     */

    int getValueAt(int position)
    {
        int value = -1;

        if (!root)
            return value;

        if (0 == position)
        {
            return root->data;
        }
        int count = 1;
        Node *current = root;
        while (current->next && count <= position)
        {
            count++;
            value = current->data;
            current = current->next;
        }
        return value;
    }

    void deleteNodeNumber(int nodeNumber)
    {
        if (!root)
            return;

        if (0 == nodeNumber)
        {
            Node *temp = root;
            root = root->next;
            delete temp;
            return;
        }
        int count = 1;
        Node *current = root;
        while (current->next && count != nodeNumber)
        {
            count++;
            current = current->next;
        }
        if (current->next)
        {
            Node *temp = current->next;
            current->next = current->next->next;
            delete temp;
        }
    }

    ~LinkedList()
    {
        Node *current = root;
        while (current)
        {
            Node *next = current->next;
            delete current;
            current = next;
        }
        root = nullptr;
    }
};

ostream &operator<<(ostream &os, const LinkedList &linkedList)
{
    Node *current = linkedList.root;
    while (current)
    {
        os << *current << " ";
        current = current->next;
    }

    return os;
}

#endif