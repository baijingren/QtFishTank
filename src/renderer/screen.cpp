//
// Created by baijingren on 25-3-31.
//

#include "screen.h"

screen::screen() {
	screen_x = 800;
	screen_y = 600;
	screenToWorldRatio = 10.0;
	renderer = new Renderer();
}

screen::screen(int screen_x, int screen_y, float screenToWorldRatio) {
	this->screen_x = screen_x;
	this->screen_y = screen_y;
	this->screenToWorldRatio = screenToWorldRatio;
	renderer = new Renderer();
}

int screen::getScreenX() const {
	return screen_x;
}
int screen::getScreenY() const {
	return screen_y;
}
float screen::getScreenToWorldRatio() const {
	return screenToWorldRatio;
}
void screen::setScreenX(int screen_x) {
	screen::screen_x = screen_x;
}
void screen::setScreenY(int screen_y) {
	screen::screen_y = screen_y;
}
void screen::setScreenToWorldRatio(float screenToWorldRatio) {
	screen::screenToWorldRatio = screenToWorldRatio;
}
void screen::setRenderer(Renderer *renderer) {
	screen::renderer = renderer;
}
Renderer *screen::getRenderer() const {
	return renderer;
}
