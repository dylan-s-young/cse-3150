# Week 4 Lab - LinkedList Move Operations

This lab implements the move constructor and move assignment operator for the LinkedList class.

## Files Included

- `LinkedList.h` - Updated header with move operations implemented
- `Node.h` - Node structure (unchanged from previous lab)
- `unitTestsLinkedList.cpp` - Original unit tests for basic operations
- `moveTestsLinkedList.cpp` - New unit tests for move operations
- `basicMain.cpp` - Example program demonstrating list functionality

## Compilation Instructions

To compile and run the basic unit tests:

```bash
g++ -std=c++14 unitTestsLinkedList.cpp -o unit_tests
./unit_tests
```

To compile and run the move operation unit tests:

```bash
g++ -std=c++14 moveTestsLinkedList.cpp -o move_tests
./move_tests
```

To compile and run the example program:

```bash
g++ -std=c++14 basicMain.cpp -o main
./main
```

## Implementation Notes

1. **Move Constructor** - Allows efficient transfer of resources when constructing a new LinkedList from an rvalue (temporary object or object explicitly marked for moving).

2. **Move Assignment Operator** - Allows efficient transfer of resources when assigning from an rvalue to an existing LinkedList.

Both operations ensure that the source list's resources are transferred to the destination list, and the source list is left in a valid but empty state, preventing any resource leaks or double-deletions.
