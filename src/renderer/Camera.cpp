//
// Created by Jingren Bai on 25-3-22.
//

#include "Camera.h"

void Camera::setLookAt(int x, int y, int z) {
	lookAt[0] = x;
	lookAt[1] = y;
	lookAt[2] = z;
	lookAt[3] = 1;
}
void Camera::setPosition(int x, int y, int z) {
	position[0] = x;
	position[1] = y;
	position[2] = z;
	position[3] = 1;
}