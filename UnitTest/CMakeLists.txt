cmake_minimum_required(VERSION 3.10)
#add_executable(CameraTest CameraTest.cpp
#        ../src/renderer/Camera.cpp
#)
add_executable(LoggerTest LoggerTest.cpp
        ../src/Log.cpp
)
target_link_libraries(
    LoggerTest
    Qt6::Test
)

add_test(NAME projectionMatrixTest COMMAND UnitTest)