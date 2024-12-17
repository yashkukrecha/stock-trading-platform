cmake_minimum_required(VERSION 3.10)
project(StockTests)

# Enable testing support
enable_testing()

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add paths for source and test directories
include_directories(include)     # Include directory for headers
file(GLOB SRC_FILES src/*.cpp)   # Find all .cpp files in /src
file(GLOB TEST_FILES tests/*.cpp) # Find all .cpp files in /tests

# Add Google Test
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Define the executable for the tests
add_executable(stock_tests ${SRC_FILES} ${TEST_FILES})

# Link Google Test libraries and pthread
target_link_libraries(stock_tests ${GTEST_LIBRARIES} gtest_main pthread)

