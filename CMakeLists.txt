cmake_minimum_required(VERSION 3.14)
project(hashTable C)
set(CMAKE_C_STANDARD 11)

add_subdirectory(hashtable)
include_directories(hashtable)

add_subdirectory(external)
include_directories(external/Unity/src)


add_executable(main main/main.c )
add_executable(testss tests/test.c)

find_library(hashtable
        hashtable cmake-build-debug)
target_link_libraries(main LINK_PUBLIC hashtable)

find_library(Unity
        Unity cmake-build-debug)
target_link_libraries(testss LINK_PUBLIC Unity)
target_link_libraries(testss LINK_PUBLIC hashtable)