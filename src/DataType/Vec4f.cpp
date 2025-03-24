//
// Created by Jingren Bai on 25-3-22.
//

#include "Vec4f.h"

Vec4f::Vec4f():e{0, 0, 0, 0} {}

Vec4f::Vec4f(float x, float y, float z, float w):e{x, y, z, w} {}

Vec4f::Vec4f(float x, float y, float z):e{x, y, z, 0} {}

Vec4f::Vec4f(const Vec4f &v) {
	this->e[0] = v.e[0];
	this->e[1] = v.e[1];
	this->e[2] = v.e[2];
	this->e[3] = v.e[3];
}

Vec4f Vec4f::operator+(const Vec4f &v) const {
	return {e[0] + v.e[0], e[1] + v.e[1], e[2] + v.e[2], e[3] + v.e[3]};
}

Vec4f Vec4f::operator-(const Vec4f &v) const {
	return {e[0] - v.e[0], e[1] - v.e[1], e[2] - v.e[2], e[3] - v.e[3]};
}

Vec4f Vec4f::operator*(float t) const {
	return {e[0] * t, e[1] * t, e[2] * t, e[3] * t};
}

Vec4f &Vec4f::operator+=(const Vec4f &v) {
	return *this = *this + v;
}

Vec4f &Vec4f::operator-=(const Vec4f &v) {
	return *this = *this - v;
}

Vec4f &Vec4f::operator*=(float t) {
	return *this = *this * t;
}

Vec4f &Vec4f::operator/=(float t) {
	return *this = *this / t;
}

Vec4f Vec4f::operator-() const {
	return {-e[0], -e[1], -e[2], e[3]};
}

Vec4f &Vec4f::operator=(const Vec4f &v) {
	Vec4f x = v;
	this->e[0] = x.e[0];
	this->e[1] = x.e[1];
	this->e[2] = x.e[2];
	this->e[3] = x.e[3];
	return *this;
}

float Vec4f::operator[](int i) const {
	return e[i];
}

float &Vec4f::operator[](int i) {
	return e[i];
}

float Vec4f::x() {
	return e[0];
}

float Vec4f::y() {
	return e[1];
}

float Vec4f::z() {
	return e[2];
}

float Vec4f::w() {
	return e[3];
}

float Vec4f::length() {
	return std::sqrt(lengthSquared());
}

float Vec4f::lengthSquared() {
	e[0] /= e[3];
	e[1] /= e[3];
	e[2] /= e[3];
	e[3] = 1;
	return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
}

Vec4f::~Vec4f() = default;

Vec4f operator*(float t, const Vec4f &v) {
	return v * t;
}
