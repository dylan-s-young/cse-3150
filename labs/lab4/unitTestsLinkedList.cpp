#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
/*
  https://hackingcpp.com/cpp/tools/testing_frameworks.html
 */

#include <iostream>
#include "./include/doctest.h"
#include "LinkedList.h"

using namespace std;

TEST_CASE("Linked List Insertion Edge Cases")
{

  SUBCASE("empty and almost-empty linked lists")
  {

    LinkedList ll_0, ll_start, ll_end;

    ll_start.insertAtBeginning(5);
    ll_end.insertAtEnd(-55);

    CHECK(0 == ll_0.getSize());
    CHECK(1 == ll_start.getSize());
    CHECK(1 == ll_end.getSize());
  };

  SUBCASE("insertion and deletion")
  {

    LinkedList ll_0, ll_1;

    ll_0.insertAtBeginning(2);
    ll_0.insertAtEnd(3);
    ll_0.insertAtBeginning(1);

    CHECK(1 == ll_0.getValueAt(1));
    CHECK(2 == ll_0.getValueAt(2));
    CHECK(3 == ll_0.getValueAt(3));
  };
};

TEST_CASE("Linked List Move Operations")
{
  SUBCASE("Move Constructor")
  {
    // Create and populate a source list
    LinkedList source;
    source.insertAtBeginning(3);
    source.insertAtBeginning(2);
    source.insertAtBeginning(1);

    // Check source list before move
    CHECK(source.getSize() == 3);
    CHECK(source.getValueAt(0) == 1);
    CHECK(source.getValueAt(1) == 2);
    CHECK(source.getValueAt(2) == 3);

    // Use move constructor to create a new list
    LinkedList destination(std::move(source));

    // Check that destination received all elements
    CHECK(destination.getSize() == 3);
    CHECK(destination.getValueAt(0) == 1);
    CHECK(destination.getValueAt(1) == 2);
    CHECK(destination.getValueAt(2) == 3);

    // Check that source was properly emptied
    CHECK(source.root == nullptr);
    CHECK(source.getSize() == 0);
  }

  SUBCASE("Move Assignment Operator")
  {
    // Create and populate a source list
    LinkedList source;
    source.insertAtBeginning(30);
    source.insertAtBeginning(20);
    source.insertAtBeginning(10);

    // Create a destination list with different content
    LinkedList destination;
    destination.insertAtBeginning(5);
    destination.insertAtBeginning(4);

    // Check both lists before move
    CHECK(source.getSize() == 3);
    CHECK(destination.getSize() == 2);

    // Use move assignment to transfer ownership
    destination = std::move(source);

    // Check that destination received all elements from source
    CHECK(destination.getSize() == 3);
    CHECK(destination.getValueAt(0) == 10);
    CHECK(destination.getValueAt(1) == 20);
    CHECK(destination.getValueAt(2) == 30);

    // Check that source was properly emptied
    CHECK(source.root == nullptr);
    CHECK(source.getSize() == 0);

    // Check that there are no memory leaks (implicit via destructor)
  }

  SUBCASE("Move Operations with Empty Lists")
  {
    // Test move constructor with empty source
    LinkedList empty_source;
    LinkedList destination1(std::move(empty_source));

    CHECK(destination1.getSize() == 0);
    CHECK(destination1.root == nullptr);
    CHECK(empty_source.root == nullptr);

    // Test move assignment with empty source
    LinkedList destination2;
    destination2.insertAtBeginning(5);
    destination2 = std::move(LinkedList()); // Move from temporary empty list

    CHECK(destination2.getSize() == 0);
    CHECK(destination2.root == nullptr);
  }

  SUBCASE("Self-Assignment Protection")
  {
    LinkedList list;
    list.insertAtBeginning(1);
    list.insertAtBeginning(2);

    // Store pointer to first node before self-assignment
    Node *original_root = list.root;

    // Perform self-assignment (using a temporary to simulate move)
    list = std::move(list);

    // Verify list is still intact
    CHECK(list.root == original_root);
    CHECK(list.getSize() == 2);
  }
}
