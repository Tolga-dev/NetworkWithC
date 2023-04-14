cmake_minimum_required(VERSION 3.23)
project(xServer)

set(CMAKE_CXX_STANDARD 23)
SET(ADD_SUB_OUT 0)

# for threads
set (CMAKE_CXX_FLAGS -pthread)


add_subdirectory(Server)

add_executable(${PROJECT_NAME} Server.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE
        ServerHandle)  # <- alias of sub_lib2_sources, alternative -> sub_lib2_sources

