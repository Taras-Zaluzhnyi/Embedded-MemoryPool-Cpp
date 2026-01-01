# **Static Block Allocator (Memory Pool)**

A deterministic, O(1) memory allocator designed for embedded systems and real-time applications.

## **Description**

In embedded systems, dynamic memory allocation (```malloc```/```new```) is often avoided due to fragmentation risks and non-deterministic execution time.

This **Static Block Allocator** solves these issues by pre-allocating a fixed memory pool at compile time. It splits memory into equal-sized blocks and tracks their usage using a bitmask. This ensures **O(1)** allocation speed and **zero fragmentation**, which is critical for safety-critical and real-time applications (RTOS, Automotive, Medical devices).

## **Features**

- Deterministic Timing (O(1)): Allocation and deallocation time is constant, regardless of the pool size.
- No External Fragmentation: Blocks are fixed-size, eliminating the issue of memory holes.
- Memory Safety: Includes bounds checking to prevent corruption when freeing invalid pointers.
- Efficiency: Uses bitwise operations for low overhead memory management.
- Zero Dependencies: Written in pure C++, compatible with bare-metal environments.

## **Usage Example**

Here is how the allocator reuses freed memory slots:

```
#include <iostream>
#include "BlockAllocator.h"

int main() {
    // 1. Initialize the pool
    BlockAllocator allocator;

    // 2. Allocate blocks
    void* p1 = allocator.allocate(); // Allocates Block 0
    void* p2 = allocator.allocate(); // Allocates Block 1
    void* p3 = allocator.allocate(); // Allocates Block 2

    // 3. Free a block in the middle
    allocator.free(p2); // Block 1 is now free

    // 4. Allocate again
    // The allocator should immediately find and reuse Block 1
    void* p4 = allocator.allocate(); 

    if (p4 == p2) {
        std::cout << "SUCCESS: Block reused correctly!\n";
    } else {
        std::cout << "FAIL: Address mismatch.\n";
    }

    return 0;
}
```

## **Project Structure**

BlockAllocator.h: Class interface and Doxygen documentation.
BlockAllocator.cpp: Implementation of allocation logic.
main.cpp: Unit tests and demonstration.

## **Build & Run**

Since this project has no external dependencies, you can compile it with any C++ compiler (g++, clang, msvc).
```
g++ -o memory_pool main.cpp BlockAllocator.cpp
./memory_pool
```
