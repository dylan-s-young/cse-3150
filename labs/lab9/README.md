# Weak Pointer Circular Linked List Lab

## Overview
This lab demonstrates the difference between using `shared_ptr` and `weak_ptr` for circular linked lists in C++. 
The goal is to understand how memory management works with these smart pointers and avoid memory leaks in circular reference scenarios.

## Problem
When using `shared_ptr` to create circular references (as in a circular linked list), objects are never destroyed even when they go out of scope. This happens because each object holds a reference to another object, keeping the reference count greater than zero.

## Solution
Using `weak_ptr` for the circular reference solves this problem. A `weak_ptr` does not increase the reference count of the object it points to, allowing proper cleanup when the strong references (`shared_ptr`) go out of scope.

## Files
- `Node.h`: Contains the Node structure with both shared_ptr and weak_ptr implementations
- `main.cpp`: Demonstrates the behavior of circular linked lists with both types of pointers
- `test_node.cpp`: Unit tests using doctest.h framework
- `CMakeLists.txt`: Build configuration file

## Building and Running
```bash
# Create a build directory
mkdir build && cd build

# Configure and build
cmake ..
make

# Run the demo
./weak_ptr_demo

# Run the tests
./weak_ptr_tests
```

## Observations

### Shared Pointer Cycle
When creating a circular linked list with `shared_ptr`:
1. Each node holds a strong reference to the next node
2. This creates a cycle of references where each node keeps the next one alive
3. When the scope ends, no destructors are called because each node still has a reference count > 0
4. This results in a memory leak

Output example:
```
=== DEMONSTRATING SHARED_PTR CYCLE ===
Creating circular linked list with shared_ptr...
Traversing the circular list with shared_ptr:
Node: one
Node: two
Node: three
Node: four
Node: five
Node: one
Node: two
Node: three
Node: four
Node: five
End of shared_ptr scope - no destructors will be called due to cycle
After shared_ptr scope - notice no destructors were called!
```

### Weak Pointer Cycle
When creating a circular linked list with `weak_ptr`:
1. The actual ownership of nodes is maintained in a vector of `shared_ptr`
2. Each node holds a weak reference to the next node, which doesn't increase the reference count
3. When the scope ends and the vector is destroyed, all nodes are properly destroyed
4. No memory leak occurs

Output example:
```
=== DEMONSTRATING WEAK_PTR CYCLE ===
Creating circular linked list with weak_ptr...
Traversing the circular list with weak_ptr:
Node: one
Node: two
Node: three
Node: four
Node: five
Node: one
Node: two
Node: three
Node: four
Node: five
End of weak_ptr scope - destructors will be called when vector is destroyed
Node [five] destructor
Node [four] destructor
Node [three] destructor
Node [two] destructor
Node [one] destructor
After weak_ptr scope - all nodes were properly destroyed!
```

## Conclusion
Using `weak_ptr` for circular references is the correct approach to avoid memory leaks in C++. This pattern allows for circular data structures while ensuring proper memory management and cleanup when objects are no longer needed.
