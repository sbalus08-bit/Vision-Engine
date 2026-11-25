
cmake_minimum_required(VERSION 3.20)

project(NCRVisionEngine VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV REQUIRED)

add_executable(vision-engine
    src/main.cpp
    src/image_analyzer.cpp
)

target_link_libraries(vision-engine
    PRIVATE ${OpenCV_LIBS}
)

target_include_directories(vision-engine PRIVATE
    ${OpenCV_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
