//
// Created by baijingren on 25-3-31.
//

#ifndef QTFISHTANK_SCREEN_H
#define QTFISHTANK_SCREEN_H


#include "Renderer.h"

class screen {
private:
	int screen_x = 800, screen_y = 600;
	float screenToWorldRatio = 10.0;
	Renderer *renderer;
public:
	screen();
	screen(int screen_x, int screen_y, float screenToWorldRatio);
	int getScreenX() const;
	int getScreenY() const;
	float getScreenToWorldRatio() const;
	void setScreenX(int screen_x);
	void setScreenY(int screen_y);
	void setScreenToWorldRatio(float screenToWorldRatio);
	void setRenderer(Renderer *renderer);
	Renderer *getRenderer() const;
};


#endif //QTFISHTANK_SCREEN_H
