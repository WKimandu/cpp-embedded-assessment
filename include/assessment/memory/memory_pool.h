#pragma once

#include <cstddef>
#include <mutex>
#include <atomic>
#include <vector>
#include <memory>
#include <stdexcept>

namespace assessment {
namespace memory {

/**
 * @brief Memory pool for efficient memory management.
 * 
 * Candidates should implement a memory pool that efficiently manages memory allocations
 * to avoid dynamic memory allocations during real-time operation. This should include:
 * - Fixed-size block allocation
 * - Thread-safe operations
 * - Memory usage tracking
 * - Efficient allocation and deallocation
 * - Memory leak detection
 */
class MemoryPool {
public:
    /**
     * @brief Construct a new Memory Pool object
     * @param totalSize Total size of the memory pool in bytes
     * @param blockSize Size of each memory block (default: 64 bytes)
     * @throws std::invalid_argument if totalSize is 0 or blockSize is 0
     * @throws std::runtime_error if memory allocation fails
     */
    explicit MemoryPool(size_t totalSize, size_t blockSize = 64);
    
    /**
     * @brief Destroy the Memory Pool object
     * Checks for memory leaks if debug mode is enabled
     */
    ~MemoryPool();
    
    // Non-copyable and non-movable
    MemoryPool(const MemoryPool&) = delete;
    MemoryPool& operator=(const MemoryPool&) = delete;
    MemoryPool(MemoryPool&&) = delete;
    MemoryPool& operator=(MemoryPool&&) = delete;
    
    /**
     * @brief Allocate memory from the pool
     * @param size Size of memory to allocate in bytes
     * @return Pointer to allocated memory
     * @throws std::bad_alloc if pool is full or not enough contiguous blocks
     */
    void* allocate(size_t size);
    
    /**
     * @brief Deallocate memory previously allocated from the pool
     * @param ptr Pointer to memory to deallocate
     * @param size Size of memory to deallocate
     * @throws std::invalid_argument if ptr is null or not from this pool
     */
    void deallocate(void* ptr, size_t size);
    
    /**
     * @brief Get the total size of the memory pool
     * @return Total size in bytes
     */
    size_t getTotalSize() const;
    
    /**
     * @brief Get the size of each block
     * @return Block size in bytes
     */
    size_t getBlockSize() const;
    
    /**
     * @brief Get the number of allocations made
     * @return Number of allocations
     */
    size_t getAllocationCount() const;
    
    /**
     * @brief Get the number of deallocations made
     * @return Number of deallocations
     */
    size_t getDeallocationCount() const;
    
    /**
     * @brief Get the currently used memory size
     * @return Used size in bytes
     */
    size_t getUsedSize() const;
    
    /**
     * @brief Get the available memory size
     * @return Available size in bytes
     */
    size_t getAvailableSize() const;
    
    /**
     * @brief Check if the memory pool is empty
     * @return true if no allocations are active
     */
    bool isEmpty() const;
    
    /**
     * @brief Check if the memory pool is full
     * @return true if no more allocations can be made
     */
    bool isFull() const;
};

} // namespace memory
} // namespace assessment 