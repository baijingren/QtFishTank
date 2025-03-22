#ifndef RENDERER_H
#define RENDERER_H
#include "Camera.h"

class Renderer{
private:
	int screen_x = 800, screen_y = 600;
	float screenToWorldRatio = 10.0;
	Camera camera;
};

#endif
