cmake_minimum_required(VERSION 3.10)
add_executable(UnitTest CameraTest.cpp
        ../src/renderer/Camera.cpp
)
target_link_libraries(
    UnitTest
    Qt6::Test
)

add_test(NAME projectionMatrixTest COMMAND UnitTest)