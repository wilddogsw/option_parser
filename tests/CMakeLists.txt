find_package(GTest)

add_executable(basic_test basic_test.cpp)
target_link_libraries(basic_test option_parser CLI11::CLI11 spdlog::spdlog)

add_executable(gtests gtests.cpp)
target_link_libraries(gtests option_parser gtest::gtest)
