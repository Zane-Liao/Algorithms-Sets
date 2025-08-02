cmake_minimum_required(VERSION 3.31)
project(Algorithms)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(GTest REQUIRED)

set(CMAKE_OSX_ARCHITECTURES "arm64")

include_directories(include/)

file(GLOB SOURCES "src/*.cpp")

add_executable(algorithms ${SOURCES})

target_link_libraries(main
        GTest::GTest
        GTest::Main
)
