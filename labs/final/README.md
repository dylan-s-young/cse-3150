# TimedSharedPtr

## Overview

TimedSharedPtr is a C++ smart pointer template class that extends the functionality of std::shared_ptr by adding a time-based expiration feature. The pointer will automatically "expire" after a specified duration, causing the `get()` method to return `nullptr`. This implementation maintains full reference counting functionality while adding the expiration mechanism.

## Features

- **Time-Based Expiration**: Set an expiration time after which the pointer will be considered invalid
- **Reference Counting**: Multiple copies share ownership with proper resource management
- **Thread Safety**: Uses atomic operations for thread-safe reference counting
- **Compatible API**: Similar interface to std::shared_ptr for easy adoption
- **Reset Functionality**: Ability to reset the expiration time or replace the managed object

## Requirements

- C++17 compatible compiler (g++ or clang++)
- doctest.h (automatically downloaded by the compile script)

## File Structure

- `timed_shared_ptr.h` - The main template class implementation
- `test_timed_shared_ptr.cpp` - Unit tests using doctest.h
- `main.cpp` - Demonstration program showing usage examples
- `compile.sh` - Script to compile both the test and main programs
- `README.md` - This file
- `lab_report.md` - Detailed report on the implementation and design

## Quick Start

### Building the Project

```bash
# Make the compile script executable
chmod +x compile.sh

# Run the compile script
./compile.sh
```

This will download doctest.h if needed and compile both the unit tests and the demonstration program.

### Running the Tests

```bash
./test_timed_shared_ptr
```

### Running the Demonstration Program

```bash
./main_timed_shared_ptr
```

## Usage Examples

### Basic Usage

```cpp
#include "timed_shared_ptr.h"

// Create a timed shared pointer with no expiration
TimedSharedPtr<int> p(new int(42));
std::cout << *p << std::endl;  // Output: 42

// Create a copy - both share ownership
TimedSharedPtr<int> q = p;
std::cout << p.use_count() << std::endl;  // Output: 2
```

### With Expiration

```cpp
// Create a pointer that expires after 100 milliseconds
TimedSharedPtr<int> p(new int(42), 100);

// Still valid before expiration
std::cout << *p << std::endl;  // Output: 42

// Wait for expiration
std::this_thread::sleep_for(std::chrono::milliseconds(110));

// After expiration, get() returns nullptr
if (p.get() == nullptr) {
    std::cout << "Pointer has expired" << std::endl;
}
```

### Resetting Expiration

```cpp
TimedSharedPtr<int> p(new int(42), 100);  // Expires in 100ms

// Reset expiration time to 200ms from now
p.reset_expiry(200);

// Check if expired
if (p.is_expired()) {
    std::cout << "Expired" << std::endl;
} else {
    std::cout << "Not expired" << std::endl;
}
```

### Replacing the Managed Object

```cpp
TimedSharedPtr<int> p(new int(42));
std::cout << *p << std::endl;  // Output: 42

// Replace with a new value and set expiration
p.reset(new int(100), 200);
std::cout << *p << std::endl;  // Output: 100
```

## API Reference

### Constructors

- `TimedSharedPtr()` - Default constructor, creates empty pointer
- `TimedSharedPtr(T* ptr, int milliseconds = 0)` - Creates a pointer with optional expiration
- `TimedSharedPtr(const TimedSharedPtr& other)` - Copy constructor
- `TimedSharedPtr(TimedSharedPtr&& other)` - Move constructor

### Operators

- `operator=` - Assignment operators (copy and move)
- `operator*` - Dereference operator
- `operator->` - Member access operator
- `operator bool` - Boolean conversion

### Methods

- `T* get() const` - Get raw pointer (returns nullptr if expired)
- `int use_count() const` - Get reference count
- `bool is_expired() const` - Check if pointer has expired
- `void reset_expiry(int milliseconds)` - Set new expiration time
- `void reset(T* ptr = nullptr, int milliseconds = 0)` - Replace managed object

## Implementation Notes

The TimedSharedPtr uses a control block to manage the shared state between copies:

- **Raw Pointer**: Points to the managed object
- **Reference Count**: Tracks the number of shared owners
- **Expiry Time**: When the pointer will expire

When the `get()` method is called, it checks if the current time has passed the expiration time. If so, it returns nullptr, but the actual object is not destroyed until all TimedSharedPtr instances referencing it are destroyed.

## License

[Insert your license information here]
