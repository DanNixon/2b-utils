add_library(
  2b
  src/documentation.cpp
  src/powerbox.cpp
  src/powerbox_digitallink.cpp
  src/powerbox_serial.cpp
  src/protocol.cpp
  src/serial_port.cpp
)

target_include_directories(
  2b
  PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_link_libraries(
  2b
  better_enums
  CONAN_PKG::boost_asio
  CONAN_PKG::spdlog
)

add_executable(documentation_test test/documentation_test.cpp)
target_link_libraries(
  documentation_test
  2b
  CONAN_PKG::gtest
)
add_test(NAME documentation_test COMMAND documentation_test)

add_executable(powerbox_digitallink_test test/powerbox_digitallink_test.cpp)
target_link_libraries(
  powerbox_digitallink_test
  2b
  CONAN_PKG::gtest
)
add_test(NAME powerbox_digitallink_test COMMAND powerbox_digitallink_test)

add_executable(powerbox_test test/powerbox_test.cpp)
target_link_libraries(
  powerbox_test
  2b
  CONAN_PKG::gtest
)
add_test(NAME powerbox_test COMMAND powerbox_test)

add_executable(protocol_test test/protocol_test.cpp)
target_link_libraries(
  protocol_test
  2b
  CONAN_PKG::gtest
)
add_test(NAME protocol_test COMMAND protocol_test)
