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
	Quat(const Quat& q) = default;
	Quat(float angle, const glm::vec3& axis);
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
glm::vec3 rotate(const glm::vec3& v, const Quat& q);
glm::vec3 rotate(const Quat& q, const glm::vec3& v);
/**
 * @brief 绕指定轴旋转三维向量
 *
 * 使用GLM数学库实现三维向量绕任意轴的旋转变换，采用右手螺旋定则确定旋转方向。
 *
 * @param v        待旋转的三维向量
 * @param axis     旋转轴的向量
 * @param angle    旋转角度（单位：弧度）
 *
 * @return 返回旋转后的三维向量
 *
 * @note 该函数基于Rodrigues' rotation formula实现，适用于计算机图形学中的空间变换
 */
glm::vec3 rotate(const glm::vec3& v, const glm::vec3& axis, float angle);

#endif //QTFISHTANK_QUAT_H
