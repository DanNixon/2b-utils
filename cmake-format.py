autosort = True
dangle_parens = True
max_subargs_per_line = 1

additional_commands = {
  "conan_cmake_run": {
    "flags": [
      "BASIC_SETUP",
      "CMAKE_TARGETS",
    ],
    "kwargs": {
      "REQUIRES": "*",
      "BUILD": "*",
    }
  }
}
