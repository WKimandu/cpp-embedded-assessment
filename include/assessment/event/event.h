#pragma once

#include <chrono>
#include <string>
#include <memory>
#include <functional>

namespace assessment {
namespace event {

/**
 * @brief Priority levels for events
 */
enum class Priority {
    LOW,
    MEDIUM,
    HIGH,
    CRITICAL
};

/**
 * @brief Event type
 */
enum class EventType {
    HARDWARE_INTERRUPT,
    TIMER,
    USER_INPUT,
    SYSTEM
};

/**
 * @brief Event class for the real-time system
 */
class Event {
public:
    /**
     * @brief Construct a new Event object
     * @param id Unique event ID
     * @param type Event type
     * @param priority Event priority
     * @param payload Event payload
     */
    Event(uint64_t id, EventType type, Priority priority, std::string payload);
    
    /**
     * @brief Destroy the Event object
     */
    ~Event() = default;
    
    // Movable
    Event(Event&&) = default;
    Event& operator=(Event&&) = default;
    
    // Copyable
    Event(const Event&) = default;
    Event& operator=(const Event&) = default;
    
    /**
     * @brief Get the event ID
     * @return Event ID
     */
    uint64_t getId() const { return id_; }
    
    /**
     * @brief Get the event type
     * @return Event type
     */
    EventType getType() const { return type_; }
    
    /**
     * @brief Get the event priority
     * @return Event priority
     */
    Priority getPriority() const { return priority_; }
    
    /**
     * @brief Get the event payload
     * @return Event payload
     */
    const std::string& getPayload() const { return payload_; }
    
    /**
     * @brief Get the event timestamp
     * @return Event timestamp
     */
    std::chrono::steady_clock::time_point getTimestamp() const { return timestamp_; }
    
    /**
     * @brief Get the event deadline
     * @return Event deadline or max time point if no deadline
     */
    std::chrono::steady_clock::time_point getDeadline() const { return deadline_; }
    
    /**
     * @brief Set event deadline
     * @param deadline Event deadline
     */
    void setDeadline(std::chrono::steady_clock::time_point deadline) { deadline_ = deadline; }
    
    /**
     * @brief Check if event is past deadline
     * @return true if event is past deadline
     */
    bool isPastDeadline() const {
        return deadline_ != std::chrono::steady_clock::time_point::max() && 
               std::chrono::steady_clock::now() > deadline_;
    }

private:
    uint64_t id_;
    EventType type_;
    Priority priority_;
    std::string payload_;
    std::chrono::steady_clock::time_point timestamp_;
    std::chrono::steady_clock::time_point deadline_;
};

// Comparison operators for sorting events by priority
bool operator<(const Event& lhs, const Event& rhs);
bool operator>(const Event& lhs, const Event& rhs);

} // namespace event
} // namespace assessment 