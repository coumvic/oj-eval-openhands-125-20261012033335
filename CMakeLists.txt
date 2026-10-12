cmake_minimum_required(VERSION 3.10)

project(Debugger)

# Set C++ standard
cmake_policy(SET CMP0014 NEW)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set compiler flags for optimization
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -Wall -Wextra -Wpedantic")

# Add executable
add_executable(code debugger.cpp)

# Set output name
target_link_libraries(code)