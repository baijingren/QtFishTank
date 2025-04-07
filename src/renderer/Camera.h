//
// Created by Jingren Bai on 25-3-22.
//

#ifndef QTFISHTANK_CAMERA_H
#define QTFISHTANK_CAMERA_H
#include <glm/glm.hpp>

class Camera {
private:
	glm::vec3 camPos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f); // 指向场景中的原点
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f); // 摄像机的上方向
	glm::mat4 viewMatrix{}; // 视图矩阵
	glm::mat4 projectionMatrix{}; // 投影矩阵
	glm::mat4 orthoProjectionMatrix{}; // 正交投影矩阵
public:
	Camera() = default;
	Camera(glm::vec3 camPos, glm::vec3 cameraTarget, glm::vec3 cameraUp);
	glm::mat4 getViewMatrix();
	glm::mat4 getProjectionMatrix();
	void setProjectionMatrix(float fov, float aspect, float near, float far); // 透视投影
	void setViewMatrix(glm::vec3 m_camPos, glm::vec3 m_cameraTarget, glm::vec3 m_cameraUp); // 设置视图矩阵
	const glm::vec3 &getCamPos() const;

	void setCamPos(const glm::vec3 &camPos);

	const glm::vec3 &getCameraTarget() const;

	void setCameraTarget(const glm::vec3 &cameraTarget);

	const glm::vec3 &getCameraUp() const;

	void setCameraUp(const glm::vec3 &cameraUp);
};
void debug(glm::mat4 ret);

#endif//QTFISHTANK_CAMERA_H
