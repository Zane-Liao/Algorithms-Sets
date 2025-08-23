cmake_minimum_required(VERSION 3.10)
project(Algorithms)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(GTest REQUIRED)

set(CMAKE_OSX_ARCHITECTURES "arm64")
set(CMAKE_BUILD_TYPE Debug)

include_directories(include/)
include_directories(/opt/homebrew/include)
link_directories(/opt/homebrew/lib)

file(GLOB SOURCES 
    "src/*.cpp"
    "src/tests/*.cpp"
)

add_executable(algorithms ${SOURCES})

include(FetchContent)

FetchContent_Declare(
  abseil
  GIT_REPOSITORY https://github.com/abseil/abseil-cpp.git
  GIT_TAG        master
)

FetchContent_MakeAvailable(abseil)

target_link_libraries(algorithms
    GTest::gtest
    GTest::gtest_main
    absl::flat_hash_map
    absl::flat_hash_set
    gmp
    gmpxx
)

add_compile_definitions(RUN_TEST_MINCUT)

# Path
add_definitions(-DSOURCE_DIR="${CMAKE_SOURCE_DIR}")

enable_testing()
include(GoogleTest)
gtest_discover_tests(algorithms)