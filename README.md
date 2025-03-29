# C++ Embedded Systems Exercise

## Overview
This exercise tests your ability to develop a real-time system using C++ with focus on memory management, thread safety, and performance optimization.

## Requirements

### Core Features
1. Thread-Safe Queue Implementation
   - Lock-free queue design
   - Memory management
   - Thread synchronization
   - Performance optimization

2. Real-time Event Processing
   - Event queue management
   - Priority handling
   - Deadline management
   - Resource allocation

3. Memory Management
   - Custom memory pool
   - Memory allocation strategies
   - Memory leak prevention
   - Performance monitoring

4. Hardware Interaction
   - GPIO simulation
   - Interrupt handling
   - Device communication
   - Error handling

### Technical Requirements
- C++17 or later
- CMake build system
- Google Test framework
- Valgrind for memory analysis
- Docker for containerization

## Project Structure
```
src/
├── include/
│   └── assessment/
│       ├── queue/
│       ├── memory/
│       ├── event/
│       └── hardware/
├── src/
│   ├── queue/
│   ├── memory/
│   ├── event/
│   └── hardware/
└── test/
    ├── queue/
    ├── memory/
    ├── event/
    └── hardware/
```

## Getting Started

1. Clone the repository
2. Install dependencies
3. Build the project
4. Run tests

## Evaluation Criteria

### Code Quality (30%)
- Modern C++ practices
- Memory safety
- Thread safety
- Code organization

### Performance (30%)
- Response time
- Memory usage
- CPU utilization
- Resource efficiency

### Testing (20%)
- Unit tests
- Integration tests
- Memory leak tests
- Performance tests

### Documentation (20%)
- Code documentation
- API documentation
- Design decisions
- Performance analysis

## Time Limit
- 4 hours for implementation
- 1 hour for testing and optimization

## Submission
1. Push your code to your fork
2. Create a pull request
3. Include test results
4. Add performance analysis

## Notes
- Focus on real-time performance
- Implement proper error handling
- Use modern C++ features
- Document design decisions
- Write meaningful commit messages 
## Note on CI/CD

This repository is configured with GitHub Actions for continuous integration. Your code will be automatically built and tested when you submit a pull request.
