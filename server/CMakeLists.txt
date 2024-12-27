cmake_minimum_required(VERSION 3.10)
project(StockMarket)

# Enable testing support
enable_testing()

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add paths for source and test directories
include_directories(include)     # Include directory for headers
file(GLOB SRC_FILES src/*.cpp)   # Find all .cpp files in /src
list(REMOVE_ITEM SRC_FILES ${CMAKE_SOURCE_DIR}/src/main.cpp) # Exclude main.cpp from SRC_FILES
file(GLOB TEST_FILES tests/*.cpp) # Find all .cpp files in /tests

# Add Google Test
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Define the executable for the tests
add_executable(stock_tests ${SRC_FILES} ${TEST_FILES})

# Link Google Test libraries and pthread
target_link_libraries(stock_tests ${GTEST_LIBRARIES} gtest_main pthread)

# Define the executable for the main program
add_executable(stock_main ${SRC_FILES} src/main.cpp) # Ensure main.cpp is in /src

# Link pthread to the main executable
target_link_libraries(stock_main pthread)

# Create custom target for running Valgrind (memory analysis)
add_custom_target(
    valgrind
    COMMAND valgrind --leak-check=full --track-origins=yes --verbose ./stock_tests
    DEPENDS stock_tests
    COMMENT "Running Valgrind to check for memory issues"
)

# Optional: Add an option to enable Valgrind
option(RUN_VALGRIND "Run Valgrind for memory analysis" OFF)
if(RUN_VALGRIND)
    add_dependencies(valgrind stock_tests)  # Ensure Valgrind runs after the tests
endif()
