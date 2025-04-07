#include <glm/gtc/type_ptr.hpp>
#include "Renderer.h"
#include "objects/Ball.h"
#include "objects/Fish.h"
#include "fluid/FluidSimulator.h"

void Renderer::initializeGL() {
	initializeOpenGLFunctions();
	glEnable(GL_DEPTH_TEST); // 启用深度测试
	glEnable(GL_BLEND); // 启用混合
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // 设置混合函数
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // 设置清除颜色
	camera.setProjectionMatrix(45.0f, static_cast<float>(screen_x) / screen_y, 0.1f, 100.0f); // 设置投影矩阵
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
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	camera.setViewMatrix(camera.getCamPos(), camera.getCameraTarget(), camera.getCameraUp()); // 设置视图矩阵
	glLoadMatrixf(glm::value_ptr(camera.getViewMatrix())); // 加载视图矩阵
	drawFish(); // 绘制鱼
	drawBall(); // 绘制球
	drawFluid(); // 绘制流体
	glFlush(); // 刷新缓冲区
	glFinish(); // 等待所有OpenGL命令完成
	glPopMatrix(); // 恢复模型视图矩阵
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glLoadMatrixf(glm::value_ptr(camera.getProjectionMatrix())); // 加载投影矩阵
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glLoadMatrixf(glm::value_ptr(camera.getViewMatrix())); // 加载视图矩阵
	glPushMatrix(); // 保存当前矩阵
	glLoadIdentity(); // 重置当前矩阵
	glMatrixMode(GL_PROJECTION); // 切换到投影矩阵模式
	glLoadIdentity(); // 重置投影矩阵
}

void Renderer::drawBall() {
	Ball ball(1.0f, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
	glPushMatrix();
	glTranslatef(ball.getPosition().x, ball.getPosition().y, ball.getPosition().z); // 平移到球的位置
	glColor4f(ball.getColor().r, ball.getColor().g, ball.getColor().b, ball.getColor().a); // 设置颜色
	glBegin(GL_QUADS); // 绘制球的四边形
	glVertex3f(-ball.getR(), -ball.getR(), 0.0f);
	glVertex3f(ball.getR(), -ball.getR(), 0.0f);
	glVertex3f(ball.getR(), ball.getR(), 0.0f);
	glVertex3f(-ball.getR(), ball.getR(), 0.0f);
	glEnd();
}

void Renderer::drawFish() {
	Fish fish("fish.obj", glm::vec3(0.0f, 0.0f, 0.0f), 0.0f);
	glPushMatrix();
	glTranslatef(fish.getPosition().x, fish.getPosition().y, fish.getPosition().z); // 平移到鱼的位置
	glRotatef(fish.getAlpha(), 0.0f, 1.0f, 0.0f); // 绕y轴旋转
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f); // 设置颜色
	glBegin(GL_TRIANGLES); // 绘制鱼的三角形
	glVertex3f(-0.5f, -0.5f, 0.0f);
	glVertex3f(0.5f, -0.5f, 0.0f);
	glVertex3f(0.0f, 0.5f, 0.0f);
	glEnd();
	glPopMatrix();
}

void Renderer::drawFluid() {
	Simulator simulator(1000); // 创建流体模拟器
	simulator.runPBF(); // 运行PBF算法
	const auto &particles = simulator.getParticles(); // 获取粒子列表
	glPushMatrix();
	for (const auto &particle: particles) {
		glPushMatrix();
		glTranslatef(particle.pos.x, particle.pos.y, particle.pos.z); // 平移到粒子的位置
		glColor4f(0.0f, 0.0f, 1.0f, 1.0f); // 设置颜色
		glBegin(GL_POINTS); // 绘制粒子
		glVertex3f(0.0f, 0.0f, 0.0f);
		glEnd();
		glPopMatrix();
	}
	glPopMatrix();
}