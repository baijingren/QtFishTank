cmake_minimum_required(VERSION 3.10)

project(QtFishTank)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 17)


find_path(GLFW_INCLUDE_DIR GLFW/glfw3.h)
find_library(GLFW_LIBRARY glfw)
if (NOT GLFW_LIBRARY OR NOT GLFW_INCLUDE_DIR)
    message(FATAL_ERROR "GLFW not found!")
endif()

set(CMAKE_PREFIX_PATH "D:\\Qt\\6.8.2\\mingw_64\\lib\\cmake")
find_package(Qt6 COMPONENTS Core Gui Widgets Network Test REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glm REQUIRED)
find_package(GLEW REQUIRED)

include_directories(${GLFW_INCLUDE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${Qt6Widgets_INCLUDE_DIRS})
include_directories(${Qt6OpenGL_INCLUDE_DIRS})
include_directories(${GLEW_INCLUDE_DIRS})
include_directories(${glm_INCLUDE_DIRS})

add_executable(QtFishTank src/main.cpp
        src/core/MainWindow.cpp
        src/fluid/FluidSimulator.cpp
        src/input/UserInputHandler.cpp
        src/renderer/Renderer.cpp
        src/objects/Ball.cpp src/objects/Fish.cpp
        src/fluid/Particle.cpp
        src/fluid/Particle.h
        src/renderer/Camera.cpp
        src/renderer/Camera.h
        src/renderer/Ray.cpp
        src/renderer/Ray.h
)

enable_testing()
add_subdirectory(UnitTest)

target_link_libraries(QtFishTank
    Qt6::Core
    Qt6::Widgets
    Qt6::Network
    Qt6::Test
    ${GLFW_LIBRARY}
    GLEW::GLEW
)

set_target_properties(QtFishTank PROPERTIES
    AUTOMOC ON
)