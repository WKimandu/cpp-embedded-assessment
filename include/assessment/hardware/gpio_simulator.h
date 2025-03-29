#pragma once

#include <memory>
#include <thread>
#include <atomic>
#include <functional>
#include <array>
#include <unordered_map>

#include "assessment/event/event.h"
#include "assessment/queue/thread_safe_queue.h"

namespace assessment {
namespace hardware {

/**
 * @brief Simulates GPIO hardware for testing
 */
class GPIOSimulator {
public:
    static constexpr size_t PIN_COUNT = 16;
    
    /**
     * @brief Construct a new GPIOSimulator
     * @param eventQueue Event queue for sending interrupts
     */
    explicit GPIOSimulator(std::shared_ptr<queue::ThreadSafeQueue<event::Event>> eventQueue);
    
    /**
     * @brief Destroy the GPIOSimulator
     */
    ~GPIOSimulator();
    
    // Non-copyable and non-movable
    GPIOSimulator(const GPIOSimulator&) = delete;
    GPIOSimulator& operator=(const GPIOSimulator&) = delete;
    GPIOSimulator(GPIOSimulator&&) = delete;
    GPIOSimulator& operator=(GPIOSimulator&&) = delete;
    
    /**
     * @brief Start the simulator
     */
    void start();
    
    /**
     * @brief Stop the simulator
     */
    void stop();
    
    /**
     * @brief Simulate an interrupt on a pin
     * @param pin Pin number
     */
    void simulateInterrupt(size_t pin);
    
    /**
     * @brief Set a pin value
     * @param pin Pin number
     * @param value Pin value
     */
    void setPinValue(size_t pin, bool value);
    
    /**
     * @brief Get a pin value
     * @param pin Pin number
     * @return Pin value
     */
    bool getPinValue(size_t pin) const;
    
    /**
     * @brief Register an interrupt handler
     * @param pin Pin number
     * @param handler Interrupt handler function
     */
    void registerInterruptHandler(size_t pin, std::function<void(size_t, bool)> handler);
    
    /**
     * @brief Unregister an interrupt handler
     * @param pin Pin number
     */
    void unregisterInterruptHandler(size_t pin);
    
    /**
     * @brief Enable interrupts for a pin
     * @param pin Pin number
     */
    void enableInterrupts(size_t pin);
    
    /**
     * @brief Disable interrupts for a pin
     * @param pin Pin number
     */
    void disableInterrupts(size_t pin);
    
    /**
     * @brief Check if simulator is running
     * @return true if running
     */
    bool isRunning() const;

private:
    // Simulated GPIO pins
    std::array<std::atomic<bool>, PIN_COUNT> pins_;
    
    // Simulated interrupt enable flags
    std::array<std::atomic<bool>, PIN_COUNT> interruptEnabled_;
    
    // Interrupt handlers
    std::unordered_map<size_t, std::function<void(size_t, bool)>> interruptHandlers_;
    
    // Event queue for sending events
    std::shared_ptr<queue::ThreadSafeQueue<event::Event>> eventQueue_;
    
    // Running state
    std::atomic<bool> running_;
    
    // Simulation thread
    std::thread simulationThread_;
    
    // Mutex for handlers
    mutable std::mutex handlersMutex_;
    
    // Event ID counter
    std::atomic<uint64_t> nextEventId_;
    
    // Simulation loop
    void simulationLoop();
};

} // namespace hardware
} // namespace assessment 