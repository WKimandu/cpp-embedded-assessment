#include <iostream>
#include <memory>
#include <thread>
#include <chrono>
#include <vector>
#include <string>
#include <functional>

#include "assessment/queue/thread_safe_queue.h"
#include "assessment/event/event_processor.h"
#include "assessment/memory/memory_pool.h"
#include "assessment/hardware/gpio_simulator.h"
#include "queue/lockbased_queue_factory.h"

int main() {
    std::cout << "Real-time System Simulation" << std::endl;
    std::cout << "============================" << std::endl;

    try {
        // Initialize memory pool
        auto memoryPool = std::make_shared<assessment::memory::MemoryPool>(1024 * 1024); // 1MB pool
        std::cout << "Memory pool initialized with 1MB capacity" << std::endl;

        // Initialize queue using the LockBasedQueueFactory
        auto eventQueue = assessment::queue::LockBasedQueueFactory::create<assessment::event::Event>();
        std::cout << "Event queue initialized" << std::endl;

        // Initialize event processor
        auto eventProcessor = std::make_shared<assessment::event::EventProcessor>(eventQueue, memoryPool);
        std::cout << "Event processor initialized" << std::endl;

        // Initialize GPIO simulator
        auto gpioSimulator = std::make_shared<assessment::hardware::GPIOSimulator>(eventQueue);
        std::cout << "GPIO simulator initialized" << std::endl;

        // Start event processor
        eventProcessor->start();
        std::cout << "Event processor started" << std::endl;

        // Start GPIO simulator
        gpioSimulator->start();
        std::cout << "GPIO simulator started" << std::endl;

        // Generate some events
        std::cout << "\nGenerating events..." << std::endl;
        for (int i = 0; i < 10; ++i) {
            gpioSimulator->simulateInterrupt(i % 4);
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }

        // Wait for a bit to let events process
        std::cout << "\nWaiting for events to process..." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));

        // Stop GPIO simulator
        gpioSimulator->stop();
        std::cout << "GPIO simulator stopped" << std::endl;

        // Stop event processor
        eventProcessor->stop();
        std::cout << "Event processor stopped" << std::endl;

        // Print memory pool statistics
        std::cout << "\nMemory pool statistics:" << std::endl;
        std::cout << "Total size: " << memoryPool->getTotalSize() << " bytes" << std::endl;
        std::cout << "Used: " << memoryPool->getUsedSize() << " bytes" << std::endl;
        std::cout << "Available: " << memoryPool->getAvailableSize() << " bytes" << std::endl;
        std::cout << "Allocations: " << memoryPool->getAllocationCount() << std::endl;
        std::cout << "Deallocations: " << memoryPool->getDeallocationCount() << std::endl;

        std::cout << "\nSimulation completed successfully" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "ERROR: " << e.what() << std::endl;
        return 1;
    }

    return 0;
} 