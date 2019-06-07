add_executable(2bctl src/main.cpp)

target_link_libraries(
  2bctl
  PRIVATE
    2b
    cli
    CONAN_PKG::boost_property_tree
)
