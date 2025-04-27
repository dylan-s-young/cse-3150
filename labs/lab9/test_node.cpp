#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "include/doctest.h"
#include "Node.h"
#include <vector>

TEST_CASE("Test shared_ptr cycle memory leak")
{
    // In this test we're verifying that with shared_ptr cycles,
    // destructors are not called when objects go out of scope

    int destructorCallCount = 0;

    // Create a custom node type to track destructor calls
    struct TestNode
    {
        string name;
        shared_ptr<TestNode> next;
        int *destructorCounter;

        TestNode(string name, int *counter) : name{name}, destructorCounter{counter} {}

        ~TestNode()
        {
            (*destructorCounter)++;
            cout << "TestNode [" << name << "] destructor called" << endl;
        }
    };

    {
        // Create a circular list with 5 nodes
        string names[] = {"one", "two", "three", "four", "five"};
        int numberOfNodes = sizeof(names) / sizeof(names[0]);

        shared_ptr<TestNode> root = make_shared<TestNode>(names[0], &destructorCallCount);
        shared_ptr<TestNode> node = root;

        for (int i = 1; i < numberOfNodes; i++)
        {
            node->next = make_shared<TestNode>(names[i], &destructorCallCount);
            node = node->next;
        }

        // Create the cycle
        node->next = root;
    }

    // After scope ends, no destructors should be called due to circular references
    CHECK(destructorCallCount == 0);
}

TEST_CASE("Test weak_ptr cycle proper cleanup")
{
    // In this test we're verifying that with weak_ptr cycles,
    // destructors are properly called when objects go out of scope

    int destructorCallCount = 0;

    // Create a custom node type to track destructor calls
    struct TestNode
    {
        string name;
        weak_ptr<TestNode> next;
        int *destructorCounter;

        TestNode(string name, int *counter) : name{name}, destructorCounter{counter} {}

        ~TestNode()
        {
            (*destructorCounter)++;
            cout << "TestNode [" << name << "] destructor called" << endl;
        }
    };

    {
        // Create a circular list with 5 nodes
        string names[] = {"one", "two", "three", "four", "five"};
        int numberOfNodes = sizeof(names) / sizeof(names[0]);

        // Store all shared_ptr references
        vector<shared_ptr<TestNode>> nodes;

        shared_ptr<TestNode> root = make_shared<TestNode>(names[0], &destructorCallCount);
        nodes.push_back(root);
        shared_ptr<TestNode> node = root;

        for (int i = 1; i < numberOfNodes; i++)
        {
            shared_ptr<TestNode> newNode = make_shared<TestNode>(names[i], &destructorCallCount);
            nodes.push_back(newNode);
            node->next = newNode; // Store weak reference
            node = newNode;
        }

        // Create the cycle with weak_ptr
        node->next = root;
    }

    // After scope ends, all destructors should be called
    CHECK(destructorCallCount == 5);
}

TEST_CASE("Test weak_ptr behavior when target is destroyed")
{
    // Fix for the failing test: We need to ensure proper scope
    {
        shared_ptr<Node> nodeA = make_shared<Node>("A");
        weak_ptr<Node> weakToA = nodeA;

        CHECK_FALSE(weakToA.expired());

        // Create a shared_ptr from the weak_ptr
        shared_ptr<Node> sharedToA = weakToA.lock();
        CHECK(sharedToA != nullptr);
        CHECK(sharedToA->name == "A");

        // Reset all shared_ptrs to the object
        sharedToA.reset();
        nodeA.reset();

        // Now the weak_ptr should be expired since all shared_ptrs are gone
        CHECK(weakToA.expired());

        // Attempting to lock should return nullptr
        shared_ptr<Node> nullPtr = weakToA.lock();
        CHECK(nullPtr == nullptr);
    }
}