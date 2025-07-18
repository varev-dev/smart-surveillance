cmake_minimum_required(VERSION 3.20)
project(sentinel-agent)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(DEBUG)
endif()

find_package(OpenCV REQUIRED)
find_package(spdlog REQUIRED)
find_package(GTest REQUIRED)

set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -Wall -Wextra -pedantic")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")

include_directories(include)

file(GLOB_RECURSE SOURCES "src/*.cpp")
message(STATUS "Sources: ${SOURCES}")
add_executable(sentinel-agent ${SOURCES})

target_include_directories(sentinel-agent PRIVATE ${OpenCV_INCLUDE_DIRS})
target_link_libraries(sentinel-agent PRIVATE ${OpenCV_LIBS} spdlog::spdlog)

file(GLOB_RECURSE TEST_SOURCES "tests/*.cpp")
message(STATUS "Test sources: ${TEST_SOURCES}")

list(FILTER SOURCES EXCLUDE REGEX ".*/main\\.cpp$")
add_executable(tests ${SOURCES} ${TEST_SOURCES})

target_include_directories(tests PRIVATE ${OpenCV_INCLUDE_DIRS} ${GTEST_INCLUDE_DIRS})
target_link_libraries(tests PRIVATE ${OpenCV_LIBS} spdlog::spdlog GTest::gtest_main)

enable_testing()
include(GoogleTest)
gtest_discover_tests(tests)