cmake_minimum_required(VERSION 3.27)

project(LinkedList)

set(CMAKE_CXX_STANDARD 17)

# Include directories
include_directories(include)

# Add testing
add_subdirectory(testing)

# Sources
add_executable(LinkedList main.cpp)
