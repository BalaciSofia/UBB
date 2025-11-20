# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\practice_final3_star__autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\practice_final3_star__autogen.dir\\ParseCache.txt"
  "practice_final3_star__autogen"
  )
endif()
