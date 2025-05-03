# QtFishTank

这个项目原本的计划是用Qt和OpenGL制作一个鱼缸模拟器，同时应用光线追踪和PBF流体模拟算法。但最终由于时间原因，项目最终只实现了一个简单的流体模拟器。

项目的所有依赖库通过静态连接引入，所以release版本的二进制文件可以直接运行。

项目使用的语言是C++17，依赖库有：
- Qt 用于实现GUI
- OpenGL 用于渲染（最终弃用）
- glm 提供常用的矩阵运算和向量运算库，以及一些其他的数学工具

项目的代码结构如下：
```txt
D:\CODE\QTFISHTANK\SRC
│  Log.cpp
│  main.cpp
│
├─core (已弃用)
│      GLWidget.cpp
│      GLWidget.h
│      MainWindow.cpp
│      MainWindow.h
│
├─fluid
│      FluidSimulator.cpp
│      FluidSimulator.h
│      Particle.cpp
│      Particle.h
│
├─input
│      ShaderInput.cpp
│      ShaderInput.h
│      UserInputHandler.cpp
│      UserInputHandler.h
│
├─objects
│      Ball.cpp
│      Ball.h
│      Fish.cpp
│      Fish.h
│
├─renderer
│      Camera.cpp
│      Camera.h
│      QtRenderer.cpp
│      QtRenderer.h
│      Ray.cpp (光线追踪，未实现)
│      Ray.h
│      Renderer.cpp (使用OpenGL的渲染逻辑，已弃用)
│      Renderer.h
│
└─shader (OpenGL的着色器代码，已弃用)
        FragmentShader.glsl
        random.glsl
        RandomFragment.glsl
        VertexShader.glsl
```
