cmake_minimum_required(VERSION 3.20)
project(lob CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(lob INTERFACE)
target_include_directories(lob INTERFACE include)

include(FetchContent)
FetchContent_Declare(Catch2 GIT_REPOSITORY https://github.com/catchorg/Catch2.git GIT_TAG v3.5.2)
FetchContent_MakeAvailable(Catch2)

add_executable(tests tests/test_smoke.cpp tests/test_types.cpp)
target_link_libraries(tests PRIVATE lob Catch2::Catch2WithMain)
enable_testing()
add_test(NAME tests COMMAND tests)