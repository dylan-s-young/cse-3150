#ifndef TIMED_SHARED_PTR_H
#define TIMED_SHARED_PTR_H

#include <iostream>
#include <chrono>
#include <thread>
#include <atomic>
#include <memory>

using Clock = std::chrono::steady_clock;
using TimePoint = std::chrono::time_point<Clock>;

/**
 * @brief A shared pointer implementation that expires after a specified duration
 * 
 * TimedSharedPtr is similar to std::shared_ptr but with an expiration feature.
 * After the specified duration, the get() method will return nullptr.
 * 
 * @tparam T The type of object being managed
 */
template<typename T>
class TimedSharedPtr {
private:
    struct ControlBlock {
        T* ptr;                    // Pointer to the managed object
        std::atomic<int> count;    // Reference count
        TimePoint expiry;          // When this pointer expires
        
        // Constructor for control block
        ControlBlock(T* p, int milliseconds = 0) : ptr(p), count(1) {
            // If milliseconds is 0, it means no expiration
            if (milliseconds <= 0) {
                // Set to max time in the future (effectively never expires)
                expiry = TimePoint::max();
            } else {
                // Set expiry to current time + milliseconds
                expiry = Clock::now() + std::chrono::milliseconds(milliseconds);
            }
            
            std::cout << "ControlTimedSharedPtr " << ptr << " start: " 
                      << std::chrono::duration_cast<std::chrono::milliseconds>(
                         Clock::now() - Clock::now()).count() << " ms" << std::endl;
        }
        
        // Destructor
        ~ControlBlock() {
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
                Clock::now() - expiry + std::chrono::milliseconds(
                    expiry == TimePoint::max() ? 0 : 
                    std::chrono::duration_cast<std::chrono::milliseconds>(expiry - Clock::now()).count()
                )
            ).count();
            
            std::cout << "ControlTimedSharedPtr " << ptr << " end: " 
                      << duration << " ms" << std::endl;
            
            delete ptr;
        }
    };
    
    ControlBlock* control_block;
    
public:
    // Default constructor
    TimedSharedPtr() : control_block(nullptr) {}
    
    // Constructor with pointer and optional expiration time
    TimedSharedPtr(T* ptr, int milliseconds = 0) : 
        control_block(ptr ? new ControlBlock(ptr, milliseconds) : nullptr) {}
    
    // Copy constructor
    TimedSharedPtr(const TimedSharedPtr& other) : control_block(other.control_block) {
        if (control_block) {
            control_block->count++;
        }
    }
    
    // Move constructor
    TimedSharedPtr(TimedSharedPtr&& other) noexcept : control_block(other.control_block) {
        other.control_block = nullptr;
    }
    
    // Copy assignment operator
    TimedSharedPtr& operator=(const TimedSharedPtr& other) {
        if (this != &other) {
            // Decrement current control block reference count if exists
            if (control_block && --control_block->count == 0) {
                delete control_block;
            }
            
            // Copy new control block and increment its reference count
            control_block = other.control_block;
            if (control_block) {
                control_block->count++;
            }
        }
        return *this;
    }
    
    // Move assignment operator
    TimedSharedPtr& operator=(TimedSharedPtr&& other) noexcept {
        if (this != &other) {
            // Clean up current control block
            if (control_block && --control_block->count == 0) {
                delete control_block;
            }
            
            // Move control block from other
            control_block = other.control_block;
            other.control_block = nullptr;
        }
        return *this;
    }
    
    // Destructor
    ~TimedSharedPtr() {
        if (control_block && --control_block->count == 0) {
            delete control_block;
        }
    }
    
    // Get raw pointer (with expiry check)
    T* get() const {
        if (!control_block) {
            return nullptr;
        }
        
        // Check if pointer has expired
        if (Clock::now() > control_block->expiry) {
            std::cout << "Yeo! Expired ";
            return nullptr;
        }
        
        return control_block->ptr;
    }
    
    // Get reference count
    int use_count() const {
        return control_block ? control_block->count.load() : 0;
    }
    
    // Check if pointer is expired
    bool is_expired() const {
        return control_block && Clock::now() > control_block->expiry;
    }
    
    // Set new expiration time (in milliseconds from now)
    void reset_expiry(int milliseconds) {
        if (control_block) {
            if (milliseconds <= 0) {
                control_block->expiry = TimePoint::max();
            } else {
                control_block->expiry = Clock::now() + std::chrono::milliseconds(milliseconds);
            }
        }
    }
    
    // Reset pointer with new pointer and expiration
    void reset(T* ptr = nullptr, int milliseconds = 0) {
        // Decrement and potentially delete old control block
        if (control_block && --control_block->count == 0) {
            delete control_block;
        }
        
        // Create new control block if pointer exists
        control_block = ptr ? new ControlBlock(ptr, milliseconds) : nullptr;
    }
    
    // Dereference operator
    T& operator*() const {
        T* p = get();
        if (!p) {
            throw std::runtime_error("Cannot dereference expired or null pointer");
        }
        return *p;
    }
    
    // Arrow operator
    T* operator->() const {
        T* p = get();
        if (!p) {
            throw std::runtime_error("Cannot access member of expired or null pointer");
        }
        return p;
    }
    
    // Boolean conversion
    explicit operator bool() const {
        return get() != nullptr;
    }
};

#endif // TIMED_SHARED_PTR_H
