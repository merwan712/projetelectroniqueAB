# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\proelecm1eea_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\proelecm1eea_autogen.dir\\ParseCache.txt"
  "proelecm1eea_autogen"
  )
endif()
