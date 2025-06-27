cmake_minimum_required(VERSION 3.31)
project(sentinel-agent)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV REQUIRED)

set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -Wall -Wextra -pedantic")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")

include_directories(include)

file(GLOB_RECURSE SOURCES "src/*.cpp")
add_executable(sentinel-agent ${SOURCES})

target_link_libraries(sentinel-agent PRIVATE ${OpenCV_LIBS})