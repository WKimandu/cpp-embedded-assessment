#pragma once

#include "assessment/queue/thread_safe_queue.h"
#include "lockbased_queue.h"
#include <memory>

namespace assessment {
namespace queue {

/**
 * @brief Factory class for creating LockBasedQueue instances
 */
class LockBasedQueueFactory {
public:
    /**
     * @brief Create a new instance of LockBasedQueue
     * 
     * @tparam T The type of items stored in the queue
     * @return std::unique_ptr<ThreadSafeQueue<T>> A pointer to the created queue
     */
    template <typename T>
    static std::unique_ptr<ThreadSafeQueue<T>> create() {
        return std::make_unique<LockBasedQueue<T>>();
    }
};

} // namespace queue
} // namespace assessment 