cmake_minimum_required(VERSION "3.1")

project("GAS-ssg" LANGUAGES CXX)

include_directories(
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/src
)

file(GLOB all_SRCS
        "${PROJECT_SOURCE_DIR}/include/*.hpp"
        "${PROJECT_SOURCE_DIR}/src/*.cpp"
        )

add_executable(GAS-ssg ${all_SRCS})