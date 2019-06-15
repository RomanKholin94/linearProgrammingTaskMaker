#cmake_minimum_required(VERSION 2.8)
#add_executable(main a.cpp)

cmake_minimum_required(VERSION 3.5)

project(linear_programming_task_maker)

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED on)

include_directories(
../include
    ${GTEST_INCLUDE_DIRS})

add_executable(
    ${PROJECT_NAME} src/main.cpp
)

add_executable(
    test_component ./tests/test_component/test_component.cpp
)

target_link_libraries(
    test_component ${GTEST_LIBRARIES} Threads::Threads
)

add_executable(
    test_graph ./tests/test_graph/test_graph.cpp
)

target_link_libraries(
    test_graph ${GTEST_LIBRARIES} Threads::Threads
)

add_executable(
    test_framework ./tests/test_framework/test_framework.cpp
)

target_link_libraries(
    test_framework ${GTEST_LIBRARIES} Threads::Threads
)

enable_testing()
add_test(test_component "./test_component")
add_test(test_graph "./test_graph")
add_test(test_framework "./test_framework")
