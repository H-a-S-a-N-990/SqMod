# Use the official Ubuntu image as a base
FROM ubuntu:latest

# Set environment variables
ENV BUILD_TYPE=Release

# Install necessary packages
RUN apt-get update && apt-get install -y \
    cmake \
    build-essential \
    libssl-dev \
    libcurl4-openssl-dev \
    libmysqlclient-dev \
    libpq-dev \
    libsodium-dev \
    libgnutls28-dev \
    zlib1g-dev \
    && rm -rf /var/lib/apt/lists/*

# Create a build directory
RUN mkdir /app/build

# Set the working directory
WORKDIR /app

# Copy the current directory contents into the container at /app
COPY . .

# Configure CMake
RUN cmake -B build -S . -DCMAKE_BUILD_TYPE=$BUILD_TYPE

# Build the project
RUN cmake --build build --config $BUILD_TYPE

# Run tests
CMD ["ctest", "-C", "$BUILD_TYPE"]
