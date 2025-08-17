cmake_minimum_required(VERSION 3.10)
project(Algorithms)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(GTest REQUIRED)

set(CMAKE_OSX_ARCHITECTURES "arm64")

include_directories(include/)
include_directories(/opt/homebrew/include)
link_directories(/opt/homebrew/lib)

file(GLOB SOURCES 
    "src/*.cpp"
    "src/tests/*.cpp"
)

add_executable(algorithms ${SOURCES})

target_link_libraries(algorithms
    GTest::gtest
    GTest::gtest_main
    gmp
    gmpxx
)

# Path
add_definitions(-DSOURCE_DIR="${CMAKE_SOURCE_DIR}")

enable_testing()
include(GoogleTest)
gtest_discover_tests(algorithms)