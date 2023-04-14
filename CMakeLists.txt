cmake_minimum_required(VERSION 3.23)
project(xServer)

set(CMAKE_CXX_STANDARD 23)
SET(ADD_SUB_OUT 0)


if(ADD_SUB_OUT)
    add_subdirectory(out/SystemCallsAndBusts)
ELSE()
    add_executable(xServer out/n_h_tons.cpp)
endif()
