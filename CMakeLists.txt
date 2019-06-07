cmake_minimum_required(VERSION 3.5)
project(2b-utils VERSION 0.1.0 LANGUAGES CXX)

list(
  APPEND
    CMAKE_MODULE_PATH
    "${CMAKE_SOURCE_DIR}/cmake"
)

set(CMAKE_CXX_STANDARD 17)
add_compile_options(-fconcepts)

include(conan)
conan_cmake_run(
  BASIC_SETUP
  CMAKE_TARGETS
  BUILD missing
  REQUIRES
    boost_asio/1.69.0@bincrafters/stable
    boost_property_tree/1.69.0@bincrafters/stable
    gtest/1.8.1@bincrafters/stable
    spdlog/1.3.1@bincrafters/stable
)

enable_testing()

add_definitions(-DSPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_DEBUG)

add_subdirectory(third_party/better_enums)
add_subdirectory(third_party/cli)

add_subdirectory(2b)
add_subdirectory(2bctl)
