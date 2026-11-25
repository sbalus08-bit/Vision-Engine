
cmake_minimum_required(VERSION 3.20)

project(VisionEngine VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV REQUIRED)

# Main application
add_executable(vision-engine
    src/main.cpp
    src/image_analyzer.cpp
    src/image_validator.cpp
)

target_link_libraries(vision-engine PRIVATE
    ${OpenCV_LIBS}
)

target_include_directories(vision-engine PRIVATE
    ${OpenCV_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# GoogleTest configuration
include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

FetchContent_MakeAvailable(googletest)

enable_testing()

# ImageValidator unit tests
add_executable(image-validator-tests
    tests/image_validator_tests.cpp
    src/image_validator.cpp
    src/image_analyzer.cpp
)

target_include_directories(image-validator-tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${OpenCV_INCLUDE_DIRS}
)

target_link_libraries(image-validator-tests PRIVATE
    GTest::gtest_main
    ${OpenCV_LIBS}
)

include(GoogleTest)

gtest_discover_tests(image-validator-tests)

# Command-line integration tests
add_executable(command-line-tests
    tests/command_line_tests.cpp
)

target_link_libraries(command-line-tests PRIVATE
    GTest::gtest_main
)

gtest_discover_tests(command-line-tests
    PROPERTIES
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
)

add_dependencies(command-line-tests vision-engine)
