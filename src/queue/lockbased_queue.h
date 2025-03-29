#pragma once

#include "assessment/queue/thread_safe_queue.h"
#include <mutex>
#include <queue>
#include <condition_variable>

namespace assessment {
namespace queue {

/**
 * @brief Lock-based implementation of ThreadSafeQueue
 * 
 * This implementation uses mutex and condition variables to provide thread safety.
 */
template <typename T>
class LockBasedQueue : public ThreadSafeQueue<T> {
public:
    LockBasedQueue() : m_shutdown(false) {}
    ~LockBasedQueue() override = default;

    void enqueue(const T& item) override {
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            if (m_shutdown) {
                return;
            }
            m_queue.push(item);
        }
        m_condition.notify_one();
    }

    void enqueue(T&& item) override {
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            if (m_shutdown) {
                return;
            }
            m_queue.push(std::move(item));
        }
        m_condition.notify_one();
    }

    std::optional<T> dequeue() override {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_condition.wait(lock, [this] { return m_shutdown || !m_queue.empty(); });
        
        if (m_queue.empty()) {
            return std::nullopt;
        }
        
        T item = std::move(m_queue.front());
        m_queue.pop();
        return item;
    }

    bool tryDequeue(T& item) override {
        std::lock_guard<std::mutex> lock(m_mutex);
        if (m_queue.empty()) {
            return false;
        }
        
        item = std::move(m_queue.front());
        m_queue.pop();
        return true;
    }

    std::optional<T> waitDequeue(std::chrono::milliseconds timeout) override {
        std::unique_lock<std::mutex> lock(m_mutex);
        if (!m_condition.wait_for(lock, timeout, [this] { return m_shutdown || !m_queue.empty(); })) {
            return std::nullopt;  // Timeout
        }
        
        if (m_queue.empty()) {
            return std::nullopt;  // Queue is empty (shutdown)
        }
        
        T item = std::move(m_queue.front());
        m_queue.pop();
        return item;
    }

    bool empty() const override {
        std::lock_guard<std::mutex> lock(m_mutex);
        return m_queue.empty();
    }

    size_t size() const override {
        std::lock_guard<std::mutex> lock(m_mutex);
        return m_queue.size();
    }

    void clear() override {
        std::lock_guard<std::mutex> lock(m_mutex);
        std::queue<T> empty;
        std::swap(m_queue, empty);
    }

    void shutdown() override {
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            m_shutdown = true;
        }
        m_condition.notify_all();
    }

    bool isShutDown() const override {
        std::lock_guard<std::mutex> lock(m_mutex);
        return m_shutdown;
    }

private:
    mutable std::mutex m_mutex;
    std::condition_variable m_condition;
    std::queue<T> m_queue;
    bool m_shutdown;
};

} // namespace queue
} // namespace assessment 