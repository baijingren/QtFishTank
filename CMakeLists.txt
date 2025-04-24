cmake_minimum_required(VERSION 3.14)  # 提升版本要求以支持更完整的Qt6特性

project(QtFishTank LANGUAGES CXX)

# 现代CMake设置
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# 平台特定配置
if(WIN32)
    # Windows平台配置
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
    set(OpenGL_GL_PREFERENCE "GLVND")
elseif(UNIX AND NOT APPLE)
    # Linux平台配置
    set(CMAKE_POSITION_INDEPENDENT_CODE ON)
endif()

# 查找依赖
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Network Test OpenGL OpenGLWidgets)
find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)  # 使用官方GLFW包配置
find_package(GLEW REQUIRED)
find_package(glm REQUIRED)

# 添加可执行文件
add_executable(QtFishTank
        src/main.cpp
        src/core/MainWindow.cpp
        src/fluid/FluidSimulator.cpp
        src/input/UserInputHandler.cpp
        src/renderer/Renderer.cpp
        src/objects/Ball.cpp
        src/objects/Fish.cpp
        src/fluid/Particle.cpp
        src/renderer/Camera.cpp
        src/renderer/Ray.cpp
        src/renderer/screen.cpp
        src/Log.cpp
)

# 包含目录（使用现代CMake目标方式）
target_include_directories(QtFishTank PRIVATE
        ${CMAKE_SOURCE_DIR}/src
        ${Qt6Widgets_INCLUDE_DIRS}
        ${Qt6OpenGL_INCLUDE_DIRS}
)

# 链接库
target_link_libraries(QtFishTank PRIVATE
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
        Qt6::Network
        Qt6::Test
        Qt6::OpenGL
        Qt6::OpenGLWidgets
        glfw
        GLEW::GLEW
        OpenGL::GL
        glm::glm
)

# 启用测试
enable_testing()
add_subdirectory(UnitTest)

# 平台特定配置
if(WIN32)
    # Windows特定设置
    target_compile_definitions(QtFishTank PRIVATE WIN32)
    set_property(TARGET QtFishTank PROPERTY WIN32_EXECUTABLE TRUE)
elseif(UNIX AND NOT APPLE)
    # Linux特定设置
    target_compile_options(QtFishTank PRIVATE -Wall -Wextra)
endif()