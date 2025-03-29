#pragma once

#include <mutex>
#include <queue>
#include <condition_variable>
#include <chrono>
#include <optional>
#include <memory>
#include <atomic>

namespace assessment {
namespace queue {

/**
 * @brief Thread-safe queue implementation for the assessment.
 * 
 * Candidates should implement a thread-safe queue that provides the following features:
 * - Thread-safe enqueue and dequeue operations
 * - Timed wait for dequeue
 * - Non-blocking tryDequeue operation
 * - Ability to check if queue is empty
 * - Ability to get current size
 * - Ability to clear the queue
 * - Proper shutdown mechanism
 */
template <typename T>
class ThreadSafeQueue {
public:
    ThreadSafeQueue() = default;
    virtual ~ThreadSafeQueue() = default;
    
    // Non-copyable
    ThreadSafeQueue(const ThreadSafeQueue&) = delete;
    ThreadSafeQueue& operator=(const ThreadSafeQueue&) = delete;
    
    // Non-movable
    ThreadSafeQueue(ThreadSafeQueue&&) = delete;
    ThreadSafeQueue& operator=(ThreadSafeQueue&&) = delete;
    
    /**
     * @brief Enqueue an item
     * @param item The item to enqueue
     */
    virtual void enqueue(const T& item) = 0;
    
    /**
     * @brief Enqueue an item (move semantics)
     * @param item The item to enqueue
     */
    virtual void enqueue(T&& item) = 0;
    
    /**
     * @brief Dequeue an item
     * @return The dequeued item or nullopt if queue is shut down
     */
    virtual std::optional<T> dequeue() = 0;
    
    /**
     * @brief Try to dequeue an item (non-blocking)
     * @param[out] item The dequeued item
     * @return true if an item was dequeued, false otherwise
     */
    virtual bool tryDequeue(T& item) = 0;
    
    /**
     * @brief Wait for an item with timeout
     * @param timeout The maximum time to wait
     * @return The dequeued item or nullopt if timeout or queue is shut down
     */
    virtual std::optional<T> waitDequeue(std::chrono::milliseconds timeout) = 0;
    
    /**
     * @brief Check if the queue is empty
     * @return true if the queue is empty, false otherwise
     */
    virtual bool empty() const = 0;
    
    /**
     * @brief Get the current size
     * @return The current size
     */
    virtual size_t size() const = 0;
    
    /**
     * @brief Clear the queue
     */
    virtual void clear() = 0;
    
    /**
     * @brief Shut down the queue
     */
    virtual void shutdown() = 0;
    
    /**
     * @brief Check if the queue is shut down
     * @return true if the queue is shut down, false otherwise
     */
    virtual bool isShutDown() const = 0;
};

} // namespace queue
} // namespace assessment 