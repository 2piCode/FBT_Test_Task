cmake_minimum_required(VERSION 3.10)
project(motor LANGUAGES CXX)
add_library(${PROJECT_NAME} SHARED)

file(GLOB_RECURSE motor_sources "./*"  ".//home/love-coding/motor/src/*")
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${motor_sources})
target_sources(${PROJECT_NAME} PRIVATE ${motor_sources})
target_link_libraries(${PROJECT_NAME} PUBLIC fbt)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
