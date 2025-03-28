//
// Created by Jingren Bai on 25-3-22.
//

#include <cmath>
#include <iostream>
#include "Camera.h"

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
	float top = near * std::tan(fov / 2.0f) / 2; // 这里为什么必须除以2？
	float right = top * aspect; // 利用宽高比计算top
	ret = glm::mat4(1.0f); // 生成单位矩阵
	ret = ret * glm::mat4(
			2.0f / right, 0.0f, 0.0f, 0.0f,
			0.0f, 2.0f / top, 0.0f, 0.0f,
			0.0f, 0.0f, 2.0f / (far - near), -(far + near) / (far - near),
			0.0f, 0.0f, 0.0f, 1.0f
	); // 生成正则投影矩阵
//	ret = ret * glm::mat4(
//			1.0f, 0.0f, 0.0f, -right,
//			0.0f, 1.0f, 0.0f, -top,
//			0.0f, 0.0f, 1.0f, -(near + far) / 2.0f,
//			0.0f, 0.0f, 0.0f, 1.0f
//	);
	ret = ret * glm::mat4{
			near, 0.0f, 0.0f, 0.0f,
			0.0f, near, 0.0f, 0.0f,
			0.0f, 0.0f, near + far, -near * far,
			0.0f, 0.0f, 1.0f, 0.0f
	}; // 压缩近平面，转化为透视投影矩阵
//	debug(ret);
	projectionMatrix = ret;
}
void Camera::setViewMatrix(glm::vec3 m_camPos, glm::vec3 m_cameraTarget, glm::vec3 m_cameraUp) { // 设置视图矩阵
	camPos = m_camPos;
	cameraTarget = m_cameraTarget;
	cameraUp = m_cameraUp;
	glm::mat4 ret = glm::mat4(1.0f);
	glm::vec3 newUp = glm::normalize(m_cameraUp);
	glm::vec3 lookAt =  glm::normalize(m_cameraTarget - m_camPos); // 指向-z方向
	glm::vec3 GxT = glm::normalize(glm::cross(newUp, lookAt)); // 右向量, 与lookAt和cameraUp垂直
	newUp = glm::normalize(glm::cross(lookAt, GxT)); // 上向量
	glm::mat4 rotation = glm::transpose(glm::mat4(
			glm::vec4(GxT, 0.0f),
			glm::vec4(newUp, 0.0f),
			glm::vec4(-lookAt, 0.0f),
			glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)
	)); // 旋转
	glm::mat4 translation = glm::mat4(
			glm::vec4(1.0f, 0.0f, 0.0f, -m_camPos.x),
			glm::vec4(0.0f, 1.0f, 0.0f, -m_camPos.y),
			glm::vec4(0.0f, 0.0f, 1.0f, -m_camPos.z),
			glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)
	); // 平移
	ret = glm::transpose(rotation * translation);
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
}
