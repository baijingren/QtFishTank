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
public:
protected:
	void initializeGL() override;
	void resizeGL(int w, int h) override;
	void paintGL() override;
	void drawScene();
	static void drawFish();
	static void drawBall();
	static void drawFluid();
};

#endif
