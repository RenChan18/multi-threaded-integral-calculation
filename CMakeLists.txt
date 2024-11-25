cmake_minimum_required(VERSION 3.10)

project(MultiThreadedIntegralCalc)

file(GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)

add_executable(app ${SOURCES})

target_include_directories(app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

find_package(Threads REQUIRED)

target_link_libraries(app PRIVATE Threads::Threads)

set(CMAKE_C_FLAGS_DEBUG "-g -Wall -Wextra -fsanitize=address -pthread")
set(CMAKE_C_FLAGS_RELEASE "-O3 -Wall -Wextra -pthread")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
