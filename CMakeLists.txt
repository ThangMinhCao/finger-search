cmake_minimum_required(VERSION 3.16)
project(finger-search)

set(CMAKE_CXX_STANDARD 20)

set(MAIN_HEADERS
        include/Treap.h
        include/Random.h
)

set(MAIN_SOURCE
        src/Treap.cpp
        src/main.cpp
        src/Random.cpp)

add_executable(finger-search ${MAIN_HEADERS} ${MAIN_SOURCE})