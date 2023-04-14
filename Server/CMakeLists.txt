project(sub_lib2_sources)

add_library(${PROJECT_NAME} STATIC src/ServerHandle.cpp)

add_library(ServerHandle ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PUBLIC include)

