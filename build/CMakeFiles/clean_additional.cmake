# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/QtFishTank_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/QtFishTank_autogen.dir/ParseCache.txt"
  "QtFishTank_autogen"
  )
endif()
