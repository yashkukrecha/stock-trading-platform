# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Project name and version
project(ClientApp VERSION 1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the include directory
include_directories(${CMAKE_SOURCE_DIR}/include)

# Add the source files
set(SOURCES
    src/main.cpp
)

# Create the executable
add_executable(client ${SOURCES})