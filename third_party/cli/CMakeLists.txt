add_library(
  cli
  INTERFACE
)

target_include_directories(
  cli
  INTERFACE
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
