cmake_minimum_required(VERSION 3.10)
project(Kiwi)

set(CMAKE_CXX_STANDARD 11)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../lib_release/)

aux_source_directory(${PROJECT_SOURCE_DIR}/Network SRC_NETWORK)
aux_source_directory(${PROJECT_SOURCE_DIR}/Reactor SRC_REACTOR)
aux_source_directory(${PROJECT_SOURCE_DIR}/Base SRC_BASE)
aux_source_directory(${PROJECT_SOURCE_DIR}/ThreadPool SRC_THREADPOOL)

add_library(kiwi SHARED ${SRC_NETWORK} ${SRC_BASE} ${SRC_REACTOR} ${SRC_THREADPOOL})
add_library(kiwi_static STATIC ${SRC_NETWORK} ${SRC_BASE} ${SRC_REACTOR} ${SRC_THREADPOOL})

set_target_properties(kiwi_static PROPERTIES OUTPUT_NAME "kiwi")
