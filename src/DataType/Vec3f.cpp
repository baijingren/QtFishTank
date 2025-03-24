//
// Created by Jingren Bai on 25-3-22.
//

#include "Vec3f.h"

Vec3f::Vec3f():e{0.0f, 0.0f, 0.0f} {}
Vec3f::Vec3f(float x, float y, float z): e{x, y, z} {}

Vec3f::Vec3f(const Vec3f &v) {
    this->e[0] = v.e[0];
    this->e[1] = v.e[1];
    this->e[2] = v.e[2];
}

float Vec3f::x() const {
    return e[0];
}

float Vec3f::y() const {
    return e[1];
}

float Vec3f::z() const {
    return e[2];
}

Vec3f & Vec3f::operator=(const Vec3f &v) {
    Vec3f x = Vec3f(v);
    this->e[0] = v.e[0];
    this->e[1] = v.e[1];
    this->e[2] = v.e[2];
    return *this;
}

Vec3f Vec3f::operator+(const Vec3f &v) const {
	return {this->e[0] + v.e[0], this->e[1] + v.e[1], this->e[2] + v.e[2]};
}

Vec3f Vec3f::operator-(const Vec3f &v) const {
	return {this->e[0] - v.e[0], this->e[1] - v.e[1], this->e[2] - v.e[2]};
}

Vec3f & Vec3f::operator*(float t) const {
	return {e[0] * t, e[1] * t, e[2] * t};
}

Vec3f Vec3f::operator/(float t) const {
	return 1/t * (*this);
}

Vec3f & Vec3f::operator+=(const Vec3f &v) {
	return *this = *this + v;
}

Vec3f & Vec3f::operator-=(const Vec3f &v) {
	return *this = *this - v;
}

Vec3f & Vec3f::operator*=(float t) {
	return *this = *this * t;
}

Vec3f & Vec3f::operator/=(float t) {
	return *this = *this / t;
}

bool Vec3f::operator==(const Vec3f &v) const {
	return (this->e[0] == v.e[0] && this->e[1] == v.e[1] && this->e[2] == v.e[2]);
}

bool Vec3f::operator!=(const Vec3f &v) const {
	return !(*this == v);
}

Vec3f Vec3f::operator-() const {
	return {-this->e[0], -this->e[1], -this->e[2]};
}

float Vec3f::operator[](int i) const {
	return e[i];
}

float & Vec3f::operator[](int i) {
	return e[i];
}

float Vec3f::length() const {
	return std::sqrt(lengthSquared());
}

float Vec3f::lengthSquared() const {
	return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
}

Vec3f::~Vec3f() = default;

Vec3f operator*(double t, const Vec3f &v) {
    return v * t;
}
