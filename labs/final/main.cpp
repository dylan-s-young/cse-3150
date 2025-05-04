#include <iostream>
#include <chrono>
#include <thread>
#include "timed_shared_ptr.h"

// Define a simple Node structure as used in the example
struct Node
{
    int data;
    explicit Node(int d) : data(d) {}
};

void demonstrateBasicUsage()
{
    std::cout << "\n===== Basic Usage Demonstration =====\n"
              << std::endl;

    TimedSharedPtr<int> p(new int(42));
    std::cout << "Value: " << *p << std::endl;
    std::cout << "p.use_count(): " << p.use_count() << std::endl;

    TimedSharedPtr<int> q = p;
    std::cout << "p.use_count() after copy: " << p.use_count() << std::endl;
    std::cout << "q.use_count(): " << q.use_count() << std::endl;

    std::cout << "Both point to same memory address: " << p.get() << " and " << q.get() << std::endl;
}

void demonstrateExpiryBehavior()
{
    std::cout << "\n===== Expiry Behavior Demonstration =====\n"
              << std::endl;

    int expiryTime = 100; // 100 milliseconds
    std::cout << "Creating TimedSharedPtr with " << expiryTime << "ms expiry time" << std::endl;

    TimedSharedPtr<Node> myNode(new Node(7), expiryTime);
    // Node holds data of 7 and expires in 100 milliseconds

    TimedSharedPtr<Node> myOtherNode = myNode;
    std::cout << "Initial - myNode.get() address: <" << myNode.get() << ">" << std::endl;

    std::cout << "Sleeping for 50ms..." << std::endl;
    std::this_thread::sleep_until(Clock::now() + std::chrono::milliseconds(50));

    std::cout << "After 50ms - myNode.get() address: <" << myNode.get() << ">" << std::endl;
    std::cout << "myNode.use_count(): " << myNode.use_count() << std::endl;
    std::cout << "myOtherNode.use_count(): " << myOtherNode.use_count() << std::endl;

    std::cout << "Sleeping for additional 25ms (75ms total)..." << std::endl;
    std::this_thread::sleep_until(Clock::now() + std::chrono::milliseconds(25));

    std::cout << "After 75ms - myNode.get() address: <" << myNode.get() << ">" << std::endl;

    std::cout << "Sleeping for additional 75ms (150ms total)..." << std::endl;
    std::this_thread::sleep_until(Clock::now() + std::chrono::milliseconds(75));

    std::cout << "After 150ms - The ptr should have expired" << std::endl;
    std::cout << "myNode.get() address: <" << myNode.get() << ">" << std::endl;

    std::cout << "myNode.is_expired(): " << (myNode.is_expired() ? "true" : "false") << std::endl;
    std::cout << "myNode.use_count(): " << myNode.use_count() << " (reference count remains intact)" << std::endl;
}

void demonstrateResetExpiry()
{
    std::cout << "\n===== Reset Expiry Demonstration =====\n"
              << std::endl;

    TimedSharedPtr<int> p(new int(42), 100); // Expires in 100ms
    std::cout << "Initial value: " << *p << std::endl;

    std::cout << "Sleeping for 50ms..." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    std::cout << "After 50ms - value still accessible: " << *p << std::endl;

    std::cout << "Resetting expiry time to 100ms from now" << std::endl;
    p.reset_expiry(100);

    std::cout << "Sleeping for 75ms..." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(75));
    std::cout << "After 75ms (of new expiry) - value still accessible: " << *p << std::endl;

    std::cout << "Sleeping for additional 50ms (125ms total after reset)..." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(50));

    std::cout << "After 125ms (of new expiry) - The ptr should have expired" << std::endl;
    std::cout << "p.get(): " << p.get() << std::endl;
}

void demonstrateReset()
{
    std::cout << "\n===== Reset Pointer Demonstration =====\n"
              << std::endl;

    TimedSharedPtr<int> p(new int(42));
    std::cout << "Initial value: " << *p << std::endl;
    std::cout << "Use count: " << p.use_count() << std::endl;

    std::cout << "Resetting with new value 100" << std::endl;
    p.reset(new int(100));
    std::cout << "New value: " << *p << std::endl;

    TimedSharedPtr<int> q = p;
    std::cout << "Use count after copy: " << p.use_count() << std::endl;

    std::cout << "Resetting with new value 200 and 100ms expiry" << std::endl;
    p.reset(new int(200), 100);
    std::cout << "p value: " << *p << std::endl;
    std::cout << "q value: " << *q << " (q still points to old value)" << std::endl;

    std::cout << "p use count: " << p.use_count() << std::endl;
    std::cout << "q use count: " << q.use_count() << std::endl;
}

void replicateExampleOutput()
{
    std::cout << "\n===== Replicating Expected Output from Assignment =====\n"
              << std::endl;

    TimedSharedPtr<Node> myNode(new Node(7), 100);
    // Node holds data of 7 and expires in 100 milliseconds

    TimedSharedPtr<Node> myOtherNode = myNode;
    std::this_thread::sleep_until(Clock::now() + std::chrono::milliseconds(50));
    // sleep for 50 milliseconds

    std::cout << "myNode.get() address: <" << myNode.get() << ">" << std::endl;
    std::cout << "myNode.use_count(): " << myNode.use_count() << std::endl;
    std::cout << "myOtherNode.use_count(): " << myOtherNode.use_count() << std::endl;

    std::this_thread::sleep_until(Clock::now() + std::chrono::milliseconds(25));
    // sleep for 25 more milliseconds

    std::cout << "myNode.get() address: <" << myNode.get() << ">" << std::endl;

    std::this_thread::sleep_until(Clock::now() + std::chrono::milliseconds(75));
    // sleep for 75 more milliseconds – totaling 150 milliseconds!

    std::cout << "The ptr should have expired: " << std::endl;
    std::cout << "myNode.get() address: <" << myNode.get() << ">" << std::endl;
    std::cout << "-----------" << std::endl;

    TimedSharedPtr<int> p(new int(42));
    std::cout << p.get() << std::endl;
    std::cout << "p.use_count(): " << p.use_count() << std::endl;

    TimedSharedPtr<int> q = p;
    std::cout << "p.use_count(): " << p.use_count() << std::endl;
    std::cout << "q.use_count(): " << q.use_count() << std::endl;
}

int main()
{
    std::cout << "=====================================" << std::endl;
    std::cout << "TimedSharedPtr Demonstration Program" << std::endl;
    std::cout << "=====================================" << std::endl;

    demonstrateBasicUsage();
    demonstrateExpiryBehavior();
    demonstrateResetExpiry();
    demonstrateReset();
    replicateExampleOutput();

    std::cout << "\n===== Program Complete =====\n"
              << std::endl;

    return 0;
}