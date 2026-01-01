#include <iostream>
#include "BlockAllocator.h"

int main() {
    std::cout << "--- Memory Pool Test Start ---\n";

    // 1. Initialize the pool
    BlockAllocator allocator;

    // 2. Allocate blocks
    void* p1 = allocator.allocate(); // Allocates Block 0
    void* p2 = allocator.allocate(); // Allocates Block 1
    void* p3 = allocator.allocate(); // Allocates Block 2
    (void)p3; // Suppress unused variable warning (we allocated it just to fill the pool)

    if (p1) std::cout << "p1 allocated at: " << p1 << "\n";
    if (p2) std::cout << "p2 allocated at: " << p2 << "\n";

    // 3. Free a block in the middle
    std::cout << "Freeing p2...\n";
    allocator.free(p2); // Block 1 is now free

    // 4. Allocate again
    // The allocator should immediately find and reuse Block 1 (because it scans from index 0)
    void* p4 = allocator.allocate();
    std::cout << "p4 allocated at: " << p4 << "\n";

    if (p4 == p2) {
        std::cout << "SUCCESS: Block reused correctly!\n";
    }
    else {
        std::cout << "FAIL: Address mismatch.\n";
    }

    std::cout << "--- Test End ---\n";
    return 0;
}