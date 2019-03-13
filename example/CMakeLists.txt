cmake_minimum_required(VERSION 3.10)
project(Kiwi_Example)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS -pthread)

include_directories(${PROJECT_SOURCE_DIR}/../lib_release/include/)
link_libraries(${PROJECT_SOURCE_DIR}/../lib_release/libkiwi.a)

add_executable(EchoServer EchoServer.cpp)
add_executable(EchoClient EchoClient.cpp)