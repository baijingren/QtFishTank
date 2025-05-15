//
// Created by Jingren Bai on 25-3-22.
//

#include <cmath>
#include <iostream>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include "Camera.h"
#include "../Log.cpp"

Camera::Camera(glm::vec3 camPos, glm::vec3 cameraTarget, glm::vec3 cameraUp) {
	this->camPos = camPos;
	this->cameraTarget = cameraTarget;
	this->cameraUp = cameraUp;
	setViewMatrix(camPos, cameraTarget, cameraUp);
}

glm::mat4 Camera::getViewMatrix() {
	return viewMatrix;
}

glm::mat4 Camera::getProjectionMatrix() {
//	projectionMatrix = glm::mat4(1.0f);
//	projectionMatrix = glm::perspective(glm::radians(45.0f), 16.0f / 9.0f, 0.1f, 100.0f);
	return projectionMatrix;
}

void debug(glm::mat4 ret){
	std::cerr << ret[0][0] << ' ' << ret[0][1] << ' ' << ret[0][2] << ' ' << ret[0][3] << std::endl;
	std::cerr << ret[1][0] << ' ' << ret[1][1] << ' ' << ret[1][2] << ' ' << ret[1][3] << std::endl;
	std::cerr << ret[2][0] << ' ' << ret[2][1] << ' ' << ret[2][2] << ' ' << ret[2][3] << std::endl;
	std::cerr << ret[3][0] << ' ' << ret[3][1] << ' ' << ret[3][2] << ' ' << ret[3][3] << std::endl;
	std::cerr << std::endl;
}

void Camera::setProjectionMatrix(float fov, float aspect, float near, float far) {
	glm::mat4 ret;
	// fov: 视野角度(角度制)
	// aspect: 宽高比
	// near: 近裁剪面（z坐标）
	// far: 远裁剪面（z坐标）
	/*
	 * 透视投影矩阵的计算方法：
	 * 1.将摄像机与模型的坐标同时平移，使摄像机位于坐标原点
	 * 2.将模型z坐标忽略
	 * 3.压缩所有坐标，使x,y位于[-1,1]^2之间
	 * 4.生成正则投影矩阵
	 * 5.压缩近平面，转化为透视投影矩阵
	 */
//	fov = fov / 180.0f * 3.14159265358979323846f;
	float top = near * std::tan(glm::radians(fov / 2.0f));
	float right = top * aspect; // 利用宽高比计算top
	ret = glm::mat4(1.0f); // 生成单位矩阵
	glm::mat4 pro = glm::mat4(
			1.0f / right, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f / top, 0.0f, 0.0f,
			0.0f, 0.0f, 2.0f / (near - far), -(far + near) / (far - near),
			0.0f, 0.0f, 0.0f, 1.0f
	); // 生成正则投影矩阵
//	glm::mat4 pro1 = glm::mat4(
//			1.0f, 0.0f, 0.0f, 0,
//			0.0f, 1.0f, 0.0f, 0,
//			0.0f, 0.0f, 1.0f, -(near + far) / 2.0f,
//			0.0f, 0.0f, 0.0f, 1.0f
//	);
	glm::mat4 pro2 = glm::mat4{
			near, 0.0f, 0.0f, 0.0f,
			0.0f, near, 0.0f, 0.0f,
			0.0f, 0.0f, near + far, - near * far,
			0.0f, 0.0f, 1.0f, 0.0f
	}; // 压缩近平面，转化为透视投影矩阵
//	debug(ret);
//	LOG_INFO << "projectionMatrix:\n" << pro << "\n" << pro2 << "\n";
	ret = pro * pro2 * ret;
	ret = glm::mat4(
			near / right, 0.0f, 0.0f, 0.0f,
			0.0f, near / top, 0.0f, 0.0f,
			0.0f, 0.0f, -(far + near) / (far - near), 2 * near * far / (near - far),
			0.0f, 0.0f, -1.0f, 0.0f
			);
//	ret = pro2 * pro * ret;
	projectionMatrix = glm::transpose(ret);
//	glm::mat4 pro = glm::perspective(glm::radians(fov), aspect, near, far);
//	projectionMatrix = pro;
}
void Camera::setViewMatrix(glm::vec3 m_camPos, glm::vec3 m_cameraTarget, glm::vec3 m_cameraUp) { // 设置视图矩阵
	if(m_camPos == m_cameraTarget){
		LOG_ERROR << "Camera target is the same as camera position!";
		viewMatrix = glm::mat4(1.0f);
		return;
	}
	camPos = m_camPos;
	cameraTarget = m_cameraTarget;
	cameraUp = m_cameraUp;
	glm::mat4 ret = glm::mat4(1.0f);
	glm::vec3 newUp = glm::normalize(m_cameraUp);
	glm::vec3 lookAt =  glm::normalize(m_cameraTarget - m_camPos); // 指向-z方向
	glm::vec3 GxT = glm::normalize(glm::cross(lookAt, newUp)); // 右向量, 与lookAt和cameraUp垂直
	newUp = glm::normalize(glm::cross(GxT, lookAt)); // 上向量
	glm::mat4 rotation = glm::transpose(glm::mat4(
			glm::vec4(GxT, 0.0f),
			glm::vec4(newUp, 0.0f),
			glm::vec4(-lookAt, 0.0f),
			glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)
	)); // 旋转
	glm::mat4 translation = glm::mat4(
			glm::vec4(1.0f, 0.0f, 0.0f, 0.0f),
			glm::vec4(0.0f, 1.0f, 0.0f, 0.0f),
			glm::vec4(0.0f, 0.0f, 1.0f, 0.0f),
			glm::vec4(-camPos, 1.0f)
	); // 平移
//	LOG_INFO << "Rotation:\n" << rotation << "\nTranslation:\n" << translation << "\n";
	ret = rotation * translation;
//	debug(ret);
	/*
	 * -1 0 0 0
	 * 0 1 0 0
	 * 0 0 1 -3
	 * 0 0 0 1
	 */
//	debug(ret * glm::mat4(
//			0.0f, 0.0f, 3.0f, 1.0f,
//			0.0f, 0.0f, 0.0f, 1.0f,
//			0.0f, 0.0f, 0.0f, 1.0f,
//			0.0f, 0.0f, 0.0f, 1.0f
//	));
	viewMatrix = ret;
//	glm::mat4 view = glm::lookAt(m_camPos, m_cameraTarget, m_cameraUp);
//	viewMatrix = view;
}

const glm::vec3 &Camera::getCamPos() const {
	return camPos;
}

void Camera::setCamPos(const glm::vec3 &camPos) {
	Camera::camPos = camPos;
}

const glm::vec3 &Camera::getCameraTarget() const {
	return cameraTarget;
}

void Camera::setCameraTarget(const glm::vec3 &cameraTarget) {
	Camera::cameraTarget = cameraTarget;
}

const glm::vec3 &Camera::getCameraUp() const {
	return cameraUp;
}

void Camera::setCameraUp(const glm::vec3 &cameraUp) {
	Camera::cameraUp = cameraUp;
}

void Camera::setViewMatrix() {
	setViewMatrix(camPos, cameraTarget, cameraUp);
}
