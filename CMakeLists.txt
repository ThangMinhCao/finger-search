cmake_minimum_required(VERSION 3.12)
project(finger_search)

set(CMAKE_CXX_STANDARD 20)

file(GLOB finger_search_HEADERS CONFIGURE_DEPENDS "./include/*.h")
file(GLOB finger_search_SRC CONFIGURE_DEPENDS "./src/*.cpp")

add_executable(finger_search ${finger_search_HEADERS} ${finger_search_SRC})