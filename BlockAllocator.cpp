#include <cstdint>
#include "BlockAllocator.h"

BlockAllocator::BlockAllocator() : allocationMap(0) {
    // Optional: Clear memory for debugging purposes
    for (size_t i = 0; i < POOL_SIZE; ++i) {
        memory[i] = 0;
    }
}

void* BlockAllocator::allocate() {
    for (uint32_t i = 0; i < BLOCK_COUNT; ++i) {
        // Check if the bit at index i is 0 (free)
        if ((allocationMap & (1U << i)) == 0U) {
            // Mark as used (set bit to 1)
            allocationMap |= (1U << i);
            return &memory[i * BLOCK_SIZE];
        }
    }
    return nullptr;
}

void BlockAllocator::free(void* ptr) {
    // Bounds check: ensure pointer is within the memory pool
    if (ptr >= memory && ptr < memory + POOL_SIZE) {
        size_t offset = (uint8_t*)ptr - memory;
        size_t blockIndex = offset / BLOCK_SIZE;

        // Mark as free (clear bit to 0)
        allocationMap &= ~(1U << blockIndex);
    }
}