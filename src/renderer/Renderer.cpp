#include <glm/gtc/type_ptr.hpp>
#include "Renderer.h"
#include "objects/Ball.h"
#include "objects/Fish.h"
#include "fluid/FluidSimulator.h"
#include "Log.cpp"
#include "input/ShaderInput.h"

void Renderer::initializeGL() {
	initializeOpenGLFunctions();
	glEnable(GL_DEPTH_TEST); // 启用深度测试
	glEnable(GL_BLEND); // 启用混合
	glEnable(GL_PROGRAM_POINT_SIZE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // 设置混合函数
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // 设置清除颜色

	setShaders(); // 设置着色器
	setFluidParticles(); // 设置流体粒子

	camera.setProjectionMatrix(45.0f, static_cast<float>(screen_x) / screen_y, 0.1f, 100.0f); // 设置投影矩阵
}

void Renderer::setShaders() {
	std::string vertexShaderSource = ShaderInput::readShaderFile("../src/shader/VertexShader.glsl").c_str();
	std::string fragmentShaderSource = ShaderInput::readShaderFile("../src/shader/FragmentShader.glsl").c_str();
	const char *vertexShaderCode = vertexShaderSource.c_str();
	const char *fragmentShaderCode = fragmentShaderSource.c_str();

	// -----------定义顶点着色器和片段着色器------------
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderCode, nullptr);
	glCompileShader(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderCode, nullptr);
	glCompileShader(fragmentShader);

	// -----------创建着色器程序------------
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}
void Renderer::setFluidParticles() {
	Simulator simulator;
	simulator.init(1000);
	simulator.runPBF();
	particles = simulator.getParticlePos();


}
void Renderer::resizeGL(int w, int h) {
	screen_x = w;
	screen_y = h;
	glViewport(0, 0, w, h); // 设置视口
	camera.setProjectionMatrix(45.0f, static_cast<float>(w) / h, 0.1f, 100.0f); // 更新投影矩阵
}

void Renderer::paintGL() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 清除颜色和深度缓冲区
	drawScene(); // 绘制场景
}

void Renderer::drawScene() {
}