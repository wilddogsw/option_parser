cmake_minimum_required(VERSION 3.26)
project(untitled)

set(CMAKE_CXX_STANDARD 17)

find_package(CLI11 REQUIRED)
find_package(spdlog REQUIRED)
find_package(Boost REQUIRED COMPONENTS filesystem)

add_library(option_parser option_parser.cpp option_parser.h)
target_link_libraries(option_parser CLI11::CLI11 spdlog::spdlog Boost::filesystem)
target_include_directories(option_parser PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(tests)
