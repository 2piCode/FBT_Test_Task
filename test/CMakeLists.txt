cmake_minimum_required(VERSION 3.10)
find_package(Boost COMPONENTS system filesystem unit_test_framework REQUIRED)

project(test-motor LANGUAGES CXX)
add_executable(${PROJECT_NAME})

file(GLOB_RECURSE test-motor-sources "./*")
source_group(TREE ${CMAKE_CURRENT_LIST_DIR} PREFIX src FILES ${test-motor-sources})

target_sources(${PROJECT_NAME} PRIVATE ${test-motor-sources})

target_link_libraries(${PROJECT_NAME}
    ${Boost_FILESYSTEM_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
    ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
    motor
)
