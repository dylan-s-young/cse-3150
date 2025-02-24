#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "node.h"

TEST_CASE("Build and initialize linked list")
{
    int arr[] = {1, 2, 3};
    LinkedList list;
    list.build_from_array(arr, 3);
    CHECK(list.get_value_at(0) == 1);
    CHECK(list.get_value_at(1) == 2);
    CHECK(list.get_value_at(2) == 3);
}

TEST_CASE("Copy constructor")
{
    int arr[] = {4, 5, 6};
    LinkedList original;
    original.build_from_array(arr, 3);
    LinkedList copy(original);
    CHECK(copy.get_value_at(0) == 4);
    CHECK(copy.get_value_at(1) == 5);
    CHECK(copy.get_value_at(2) == 6);
}

TEST_CASE("Delete ith node")
{
    int arr[] = {10, 20, 30, 40};
    LinkedList list;
    list.build_from_array(arr, 4);
    list.delete_ith_node(1);
    CHECK(list.get_value_at(0) == 10);
    CHECK(list.get_value_at(1) == 30);
    CHECK(list.get_value_at(2) == 40);
}

TEST_CASE("Prefix sum checks")
{
    int arr1[] = {1, 2, 3};
    LinkedList list1;
    list1.build_from_array(arr1, 3);
    CHECK(list1.has_positive_prefix_sum() == true);
    CHECK(list1.has_negative_prefix_sum() == false);

    int arr2[] = {-1, -2, -3};
    LinkedList list2;
    list2.build_from_array(arr2, 3);
    CHECK(list2.has_positive_prefix_sum() == false);
    CHECK(list2.has_negative_prefix_sum() == true);
}

TEST_CASE("Pointer jumping")
{
    int arr[] = {7, 8, 9};
    LinkedList list;
    list.build_from_array(arr, 3);
    list.perform_pointer_jumping();
    CHECK(list.get_value_at(0) == 7);
    CHECK(list.get_value_at(1) == 9);
    CHECK(list.get_value_at(2) == 9);
}