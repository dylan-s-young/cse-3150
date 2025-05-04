#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "include/doctest.h"
#include "timed_shared_ptr.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <sstream>

// Redirect cout to capture output for testing
class CaptureOutput
{
private:
    std::streambuf *oldCoutStreamBuf;
    std::ostringstream strCout;

public:
    CaptureOutput()
    {
        oldCoutStreamBuf = std::cout.rdbuf(strCout.rdbuf());
    }

    ~CaptureOutput()
    {
        std::cout.rdbuf(oldCoutStreamBuf);
    }

    std::string getOutput() const
    {
        return strCout.str();
    }
};

struct TestNode
{
    int data;
    explicit TestNode(int d) : data(d) {}
};

TEST_CASE("Basic functionality")
{
    TimedSharedPtr<int> p(new int(42));
    CHECK(*p == 42);
    CHECK(p.use_count() == 1);

    TimedSharedPtr<int> q = p;
    CHECK(p.use_count() == 2);
    CHECK(q.use_count() == 2);
    CHECK(*q == 42);
}

TEST_CASE("Expiration functionality")
{
    TimedSharedPtr<int> p(new int(42), 100); // Expires in 100ms
    CHECK(*p == 42);

    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    CHECK(p.get() != nullptr); // Should still be valid

    std::this_thread::sleep_for(std::chrono::milliseconds(60));
    CHECK(p.get() == nullptr); // Should be expired
    CHECK(p.is_expired() == true);
}

TEST_CASE("Reset expiry")
{
    TimedSharedPtr<int> p(new int(42), 100); // Expires in 100ms
    std::this_thread::sleep_for(std::chrono::milliseconds(50));

    // Reset expiry to another 100ms
    p.reset_expiry(100);

    // Sleep 75ms - should still be valid
    std::this_thread::sleep_for(std::chrono::milliseconds(75));
    CHECK(p.get() != nullptr);

    // Sleep another 50ms - should be expired
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    CHECK(p.get() == nullptr);
}

TEST_CASE("Control block creation and destruction")
{
    CaptureOutput capturer;

    {
        TimedSharedPtr<int> p(new int(42), 50);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    std::string output = capturer.getOutput();
    CHECK(output.find("ControlTimedSharedPtr") != std::string::npos);
    CHECK(output.find("start: 0 ms") != std::string::npos);
    CHECK(output.find("end:") != std::string::npos);
}

TEST_CASE("Multiple copies sharing control")
{
    TimedSharedPtr<TestNode> original(new TestNode(7), 100);

    TimedSharedPtr<TestNode> copy1 = original;
    TimedSharedPtr<TestNode> copy2 = original;
    TimedSharedPtr<TestNode> copy3 = copy1;

    CHECK(original.use_count() == 4);
    CHECK(copy1.use_count() == 4);
    CHECK(copy2.use_count() == 4);
    CHECK(copy3.use_count() == 4);

    // Verify they all point to the same object
    CHECK(original.get() == copy1.get());
    CHECK(copy1.get() == copy2.get());
    CHECK(copy2.get() == copy3.get());

    // Wait for expiration
    std::this_thread::sleep_for(std::chrono::milliseconds(110));

    // All should be expired now
    CHECK(original.get() == nullptr);
    CHECK(copy1.get() == nullptr);
    CHECK(copy2.get() == nullptr);
    CHECK(copy3.get() == nullptr);

    // But reference count should still be intact
    CHECK(original.use_count() == 4);
}

TEST_CASE("Reset with new pointer")
{
    TimedSharedPtr<int> p(new int(42));
    CHECK(*p == 42);
    CHECK(p.use_count() == 1);

    p.reset(new int(100), 100);
    CHECK(*p == 100);
    CHECK(p.use_count() == 1);

    std::this_thread::sleep_for(std::chrono::milliseconds(110));
    CHECK(p.get() == nullptr);
}

TEST_CASE("Move constructor and assignment")
{
    TimedSharedPtr<int> p(new int(42));
    TimedSharedPtr<int> q(std::move(p));

    CHECK(p.get() == nullptr);
    CHECK(*q == 42);
    CHECK(q.use_count() == 1);

    TimedSharedPtr<int> r(new int(100));
    r = std::move(q);

    CHECK(q.get() == nullptr);
    CHECK(*r == 42);
    CHECK(r.use_count() == 1);
}

TEST_CASE("Assignment and destruction")
{
    TimedSharedPtr<int> p(new int(10));
    {
        TimedSharedPtr<int> q(new int(20));
        p = q;
        CHECK(*p == 20);
        CHECK(p.use_count() == 2);
        CHECK(q.use_count() == 2);
    }
    // q is out of scope, control block should still exist with count 1
    CHECK(*p == 20);
    CHECK(p.use_count() == 1);
}

TEST_CASE("Zero or negative expiry time means no expiration")
{
    TimedSharedPtr<int> p(new int(42), 0);    // 0 means no expiration
    TimedSharedPtr<int> q(new int(100), -10); // Negative also means no expiration

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    CHECK(p.get() != nullptr); // Should still be valid
    CHECK(q.get() != nullptr); // Should still be valid

    CHECK(p.is_expired() == false);
    CHECK(q.is_expired() == false);
}