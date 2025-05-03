#ifndef RENDERER_H
#define RENDERER_H

#include "Camera.h"
#include <glm/glm.hpp>
#include <QtOpenGLWidgets/QOpenGLWidget>
#include <QOpenGLFunctions>

class Renderer: public QOpenGLWidget, protected QOpenGLFunctions{
	Q_OBJECT
private:
	int screen_x = 800, screen_y = 600;
	Camera camera;

	// -----------OPENGL FUNCTIONS----------
protected:
	void initializeGL() override;
	void resizeGL(int w, int h) override;
	void paintGL() override;

	void mousePressEvent(QMouseEvent *event) override;
	void mouseMoveEvent(QMouseEvent *event) override;
	void wheelEvent(QWheelEvent *event) override;

public:
	void drawScene();
	static void drawFish();
	static void drawBall();
	static void drawFluid();

private:
	void setShaders();
	void setFluidParticles();

	GLuint VAO, VBO, EBO;
	GLuint shaderProgram;

	std::vector<glm::vec3> particles;
	glm::vec3 particleColor = glm::vec3(0.0f, 0.0f, 1.0f);
	QPoint lasrMousePos;
};

#endif
