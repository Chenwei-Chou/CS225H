# CMAKE generated file: DO NOT EDIT!
# Generated by CMake Version 3.22
cmake_policy(SET CMP0009 NEW)

# cs225_sources at lib/CMakeLists.txt:12 (file)
file(GLOB_RECURSE NEW_GLOB LIST_DIRECTORIES false "/workspaces/cs225env/cs225/hw3/lib/cs225/*.cpp")
set(OLD_GLOB
  "/workspaces/cs225env/cs225/hw3/lib/cs225/zstring.cpp"
  )
if(NOT "${NEW_GLOB}" STREQUAL "${OLD_GLOB}")
  message("-- GLOB mismatch!")
  file(TOUCH_NOCREATE "/workspaces/cs225env/cs225/hw3/build/CMakeFiles/cmake.verify_globs")
endif()

# lodepng_sources at lib/CMakeLists.txt:6 (file)
file(GLOB_RECURSE NEW_GLOB LIST_DIRECTORIES false "/workspaces/cs225env/cs225/hw3/lib/lodepng/*.cpp")
set(OLD_GLOB
  "/workspaces/cs225env/cs225/hw3/lib/lodepng/lodepng.cpp"
  )
if(NOT "${NEW_GLOB}" STREQUAL "${OLD_GLOB}")
  message("-- GLOB mismatch!")
  file(TOUCH_NOCREATE "/workspaces/cs225env/cs225/hw3/build/CMakeFiles/cmake.verify_globs")
endif()

# lodepng_sources at lib/CMakeLists.txt:6 (file)
file(GLOB_RECURSE NEW_GLOB LIST_DIRECTORIES false "/workspaces/cs225env/cs225/hw3/lib/lodepng/*.h")
set(OLD_GLOB
  "/workspaces/cs225env/cs225/hw3/lib/lodepng/lodepng.h"
  )
if(NOT "${NEW_GLOB}" STREQUAL "${OLD_GLOB}")
  message("-- GLOB mismatch!")
  file(TOUCH_NOCREATE "/workspaces/cs225env/cs225/hw3/build/CMakeFiles/cmake.verify_globs")
endif()

# src_sources at src/CMakeLists.txt:5 (file)
file(GLOB_RECURSE NEW_GLOB LIST_DIRECTORIES false "/workspaces/cs225env/cs225/hw3/src/*.cpp")
set(OLD_GLOB
  "/workspaces/cs225env/cs225/hw3/src/zalg.cpp"
  )
if(NOT "${NEW_GLOB}" STREQUAL "${OLD_GLOB}")
  message("-- GLOB mismatch!")
  file(TOUCH_NOCREATE "/workspaces/cs225env/cs225/hw3/build/CMakeFiles/cmake.verify_globs")
endif()

# tests_src at CMakeLists.txt:130 (file)
file(GLOB_RECURSE NEW_GLOB LIST_DIRECTORIES false "/workspaces/cs225env/cs225/hw3/tests/*.cpp")
set(OLD_GLOB
  "/workspaces/cs225env/cs225/hw3/tests/tests.cpp"
  )
if(NOT "${NEW_GLOB}" STREQUAL "${OLD_GLOB}")
  message("-- GLOB mismatch!")
  file(TOUCH_NOCREATE "/workspaces/cs225env/cs225/hw3/build/CMakeFiles/cmake.verify_globs")
endif()
