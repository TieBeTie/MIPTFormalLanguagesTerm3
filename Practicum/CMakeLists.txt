cmake_minimum_required(VERSION 3.17)
project(Practicum)
set(CMAKE_CXX_STANDARD 20)

add_executable(Practicum main.cpp)

add_subdirectory(${PROJECT_SOURCE_DIR}/googletest)

add_executable(CTest main_test.cpp)
target_link_libraries(CTest gtest)