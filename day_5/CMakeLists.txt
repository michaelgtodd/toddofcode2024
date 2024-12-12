cmake_minimum_required(VERSION 3.10)

# Project name and language
project(MyProject LANGUAGES CXX)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define the source and include directories
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

# Glob all .cpp files in the source directory
file(GLOB_RECURSE SOURCES ${SRC_DIR}/*.cpp)

# Automatically include the include directory for headers
include_directories(${INCLUDE_DIR})

# Create the executable
add_executable(${PROJECT_NAME} ${SOURCES})