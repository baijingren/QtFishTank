//
// Created by baijingren on 25-5-6.
//

#include "Quat.h"

Quat::Quat(float w, float x, float y, float z) : w(w), x(x), y(y), z(z) {}

Quat::Quat(float angle, const glm::vec3 &axis) {
	float half_angle = angle / 2.0f;
	w = cos(half_angle);
	x = axis.x * sin(half_angle);
	y = axis.y * sin(half_angle);
	z = axis.z * sin(half_angle);
}
Quat Quat::operator*(const Quat& q) const {
	return Quat(
		w * q.w - x * q.x - y * q.y - z * q.z,
		w * q.x + x * q.w + y * q.z - z * q.y,
		w * q.y - x * q.z + y * q.w + z * q.x,
		w * q.z + x * q.y - y * q.x + z * q.w
	);
}
Quat Quat::operator*(float s) const {
	return {w * s, x * s, y * s, z * s};
}
Quat Quat::operator/(float s) const {
	return {w / s, x / s, y / s, z / s};
}
Quat Quat::operator+(const Quat& q) const {
	return {w + q.w, x + q.x, y + q.y, z + q.z};
}
Quat Quat::operator-(const Quat& q) const {
	return {w - q.w, x - q.x, y - q.y, z - q.z};
}
Quat Quat::operator-() const {
	return {-w, -x, -y, -z};
}
glm::vec3 Quat::rotate(const glm::vec3& v) const {
	glm::vec3 u(x, y, z);
	float dot = glm::dot(u, v);
	return v + 2.0f * (dot * u + glm::cross(u, v)) * w; // 旋转向量
}
glm::vec3 rotate(const glm::vec3& v, const Quat& q) {
	return q.rotate(v);
}
glm::vec3 rotate(const glm::vec3& v, const glm::vec3& axis, float angle) {
	glm::vec3 axis_norm = glm::normalize(axis); // 预处理向量，确保向量长度为1
	Quat q(glm::cos(angle / 2.0f), axis_norm * glm::sin(angle / 2.0f));
	return q.rotate(v);
}