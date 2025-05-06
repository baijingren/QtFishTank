//
// Created by baijingren on 25-5-6.
//

#include "Quat.h"

Quat::Quat(float w, float x, float y, float z) : w(w), x(x), y(y), z(z) {}
Quat Quat::operator*(const Quat& q) const {
	return Quat(
		w * q.w - x * q.x - y * q.y - z * q.z,
		w * q.x + x * q.w + y * q.z - z * q.y,
		w * q.y - x * q.z + y * q.w + z * q.x,
		w * q.z + x * q.y - y * q.x + z * q.w
	);
}