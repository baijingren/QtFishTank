//
// Created by baijingren on 25-5-6.
//

#ifndef QTFISHTANK_QUAT_H
#define QTFISHTANK_QUAT_H

#include <glm/glm.hpp>

class Quat { // 四元数
public:
	Quat() = default;
	Quat(float w, float x, float y, float z);
	~Quat() = default;

	float w, x, y, z; // 四元数的四个分量
	Quat operator*(const Quat& q) const; // 四元数乘法
	Quat operator*(float scalar) const; // 四元数与标量乘法
	Quat operator/(float scalar) const; // 四元数与标量除法
	Quat operator+(const Quat& q) const; // 四元数加法
	Quat operator-(const Quat& q) const; // 四元数减法
	Quat operator-() const; // 四元数取反
	glm::vec3 rotate(const glm::vec3& v) const; // 对三维向量进行旋转
};


#endif //QTFISHTANK_QUAT_H
