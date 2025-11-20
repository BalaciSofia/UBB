# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\practice_test3_2_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\practice_test3_2_autogen.dir\\ParseCache.txt"
  "practice_test3_2_autogen"
  )
endif()
