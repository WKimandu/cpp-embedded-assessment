#pragma once

#include <memory>
#include <thread>
#include <atomic>
#include <functional>
#include <unordered_map>

#include "assessment/event/event.h"
#include "assessment/queue/thread_safe_queue.h"
#include "assessment/memory/memory_pool.h"

namespace assessment {
namespace event {

/**
 * @brief Event processor for handling events in real-time
 */
class EventProcessor {
public:
    /**
     * @brief Construct a new Event Processor
     * @param eventQueue Event queue
     * @param memoryPool Memory pool for allocations
     */
    EventProcessor(
        std::shared_ptr<queue::ThreadSafeQueue<Event>> eventQueue,
        std::shared_ptr<memory::MemoryPool> memoryPool
    );
    
    /**
     * @brief Destroy the Event Processor
     */
    ~EventProcessor();
    
    // Non-copyable and non-movable
    EventProcessor(const EventProcessor&) = delete;
    EventProcessor& operator=(const EventProcessor&) = delete;
    EventProcessor(EventProcessor&&) = delete;
    EventProcessor& operator=(EventProcessor&&) = delete;
    
    /**
     * @brief Start the event processor
     */
    void start();
    
    /**
     * @brief Stop the event processor
     */
    void stop();
    
    /**
     * @brief Register an event handler
     * @param type Event type
     * @param handler Event handler function
     */
    void registerHandler(EventType type, std::function<void(const Event&)> handler);
    
    /**
     * @brief Unregister an event handler
     * @param type Event type
     */
    void unregisterHandler(EventType type);
    
    /**
     * @brief Check if event processor is running
     * @return true if running
     */
    bool isRunning() const;
    
    /**
     * @brief Get the processed event count
     * @return Processed event count
     */
    size_t getProcessedEventCount() const;
    
    /**
     * @brief Get the missed deadline count
     * @return Missed deadline count
     */
    size_t getMissedDeadlineCount() const;

private:
    // Processing thread function
    void processingLoop();
    
    // Process a single event
    void processEvent(const Event& event);
    
    std::shared_ptr<queue::ThreadSafeQueue<Event>> eventQueue_;
    std::shared_ptr<memory::MemoryPool> memoryPool_;
    std::unordered_map<EventType, std::function<void(const Event&)>> handlers_;
    std::atomic<bool> running_;
    std::atomic<size_t> processedEventCount_;
    std::atomic<size_t> missedDeadlineCount_;
    std::thread processingThread_;
    std::mutex handlersMutex_;
};

} // namespace event
} // namespace assessment 