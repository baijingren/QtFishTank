//
// Created by Jingren Bai on 25-5-1.
//

#ifndef QTFISHTANK_QTRENDERER_H
#define QTFISHTANK_QTRENDERER_H

#include <QWidget>
#include <QTimer>
#include <glm/glm.hpp>

#include "Camera.h"
#include "fluid/Particle.h"
#include "fluid/FluidSimulator.h"

class QtRenderer : public QWidget{
	Q_OBJECT
private:
	int screen_x = 800, screen_y = 600;
	Camera camera;
	std::vector<Particle> particles;
public:
	QtRenderer(QWidget *parent = nullptr);
	QPointF projectToScreen(const glm::vec3& worldPos, Camera camera, int screen_x, int screen_y);
	bool projectToScreen(const glm::vec3 &worldPos, Camera camera, int screen_x, int screen_y, QPointF &out);
	void paintEvent(QPaintEvent *event) override;

private:
	Simulator simulator;
	int particleNum = 4000;
	void init();
	QTimer* simulationTimer;
	void updateSimulation();


};


#endif //QTFISHTANK_QTRENDERER_H
