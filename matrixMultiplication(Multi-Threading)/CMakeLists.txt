cmake_minimum_required(VERSION 3.10)

project(matMultip)

set(CMAKE_C_STANDARD 99)

set(THREADS_PREFER_PTHREAD_FLAG ON)

find_package(Threads REQUIRED)

add_executable(matMultip matMultip.c)

target_link_libraries(matMultip PRIVATE Threads::Threads)
