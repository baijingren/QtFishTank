cmake_minimum_required(VERSION 3.10)

project(QtFishTank)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_PREFIX_PATH "D:\\Qt\\6.8.2\\mingw_64\\lib\\cmake")
find_package(Qt6 COMPONENTS Core Gui Widgets Network OpenGL REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${Qt6Widgets_INCLUDE_DIRS})
include_directories(${Qt6OpenGL_INCLUDE_DIRS})

add_executable(QtFishTank src/main.cpp 
src/core/GLWidget.cpp src/core/MainWindow.cpp
src/fluid/FluidSimulator.cpp
src/input/UserInputHandler.cpp
src/renderer/Renderer.cpp 
src/objects/Ball.cpp src/objects/Fish.cpp
        src/fluid/Particle.cpp
        src/fluid/Particle.h
        src/renderer/Camera.cpp
        src/renderer/Camera.h
        src/DataType/Vec3.cpp
        src/DataType/Vec3.h
        src/DataType/Vec3f.cpp
        src/DataType/Vec3f.h
        src/DataType/Vec4f.cpp
        src/DataType/Vec4f.h
        src/DataType/Vec4.cpp
        src/DataType/Vec4.h
        src/DataType/Vec.h
)

target_link_libraries(QtFishTank
    Qt6::Core
    Qt6::Widgets
    Qt6::Network
)

set_target_properties(QtFishTank PROPERTIES
    AUTOMOC ON
)