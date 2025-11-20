# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\a9_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\a9_autogen.dir\\ParseCache.txt"
  "a9_autogen"
  )
endif()
