//
// Created by Jingren Bai on 25-3-22.
//

#ifndef QTFISHTANK_CAMERA_H
#define QTFISHTANK_CAMERA_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Camera {
private:
	glm::vec3 camPos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f); // 指向场景中的原点

public:
	Camera(glm::vec3 camPos, glm::vec3 cameraTarget, glm::vec3 cameraUp);
	void setLookAt(glm::vec3 lookAt);
	void setPosition(glm::vec3 position);
	glm::mat4 getViewMatrix(glm::mat4 modelMatrix);
	glm::mat4 getProjectionMatrix(glm::mat4 );

};


#endif//QTFISHTANK_CAMERA_H
