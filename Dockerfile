FROM ubuntu:22.04

# Install required dependencies
RUN apt-get update && apt-get install -y \
    libpthread-stubs0-dev \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

# Copy the built executable
COPY build/real_time_system_app .

# Make the executable runnable
RUN chmod +x real_time_system_app

# Run the application
ENTRYPOINT ["./real_time_system_app"] 