add_library(
  better_enums
  INTERFACE
)

target_include_directories(
  better_enums
  INTERFACE
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
