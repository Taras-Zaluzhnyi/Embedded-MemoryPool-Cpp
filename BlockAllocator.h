#ifndef BLOCK_ALLOCATOR_H
#define BLOCK_ALLOCATOR_H

#include <cstdint>
#include <cstddef> 

/**
 * @brief Static block memory allocator.
 * * This class manages a fixed memory buffer, dividing it into blocks of equal size.
 * Uses a bitmap (bitmask) to track the state of the blocks, which provides
 * O(1) complexity for memory allocation and deallocation.
 */
class BlockAllocator {
private:
    static constexpr size_t POOL_SIZE = 1024;
    static constexpr size_t BLOCK_SIZE = 32;
    static constexpr size_t BLOCK_COUNT = POOL_SIZE / BLOCK_SIZE;

    uint8_t memory[POOL_SIZE];
    uint32_t allocationMap;

public:
    BlockAllocator();

    /**
     * @brief Allocates one free block.
     * @return Pointer to the beginning of the block or nullptr if memory is exhausted.
     */
    void* allocate();

    /**
     * @brief Frees a block, returning it to the pool.
     * @param ptr Pointer to the block to be freed.
     * @note The function includes protection against overflowing the pool.
     */
    void free(void* ptr);
};

#endif // BLOCK_ALLOCATOR_H#pragma once
