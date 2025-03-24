//
// Created by Jingren Bai on 25-3-22.
//

#include <cmath>
#include "Vec4.h"

Vec4::Vec4() : e{0, 0, 0, 0} {}

Vec4::Vec4(double x, double y, double z, double w):e{x, y, z, w} {}

Vec4::Vec4(const Vec4 &v) {
	this->e[0] = v.e[0];
	this->e[1] = v.e[1];
	this->e[2] = v.e[2];
	this->e[3] = v.e[3];
}

double Vec4::x(){
	return e[0];
}

double Vec4::y(){
	return e[1];
}

double Vec4::z(){
	return e[2];
}

double Vec4::w(){
	return e[3];
}

Vec4 Vec4::operator+(const Vec4 &v) const {
	return {this->e[0] + v.e[0], this->e[1] + v.e[1], this->e[2] + v.e[2], this->e[3] + v.e[3]};
}

Vec4 Vec4::operator-(const Vec4 &v) const {
	return {this->e[0] - v.e[0], this->e[1] - v.e[1], this->e[2] - v.e[2], this->e[3] - v.e[3]};
}

Vec4 Vec4::operator*(double t) const {
	return {e[0] * t, e[1] * t, e[2] * t, e[3] * t};
}
Vec4 Vec4::operator/(double t) const {
	return 1/t * (*this);
}
Vec4 Vec4::operator-() const {
	return {-e[0], -e[1], -e[2], -e[3]};
}

Vec4 &Vec4::operator+=(const Vec4 &v) {
	return *this = *this + v;
}

Vec4 &Vec4::operator-=(const Vec4 &v) {
	return *this = *this - v;
}

Vec4 &Vec4::operator*=(double t) {
	return *this = *this * t;
}

Vec4 &Vec4::operator/=(double t) {
	return *this = *this / t;
}

bool Vec4::operator==(const Vec4 &v) const {
	return (this->e[0] == v.e[0] && this->e[1] == v.e[1] && this->e[2] == v.e[2] && this->e[3] == v.e[3]);
}

bool Vec4::operator!=(const Vec4 &v) const {
	return !(*this == v);
}

double Vec4::operator[](int i) const {
	return e[i];
}

double &Vec4::operator[](int i) {
	return e[i];
}

double Vec4::length() {
	return std::sqrt(lengthSquared());
}

double Vec4::lengthSquared() {
	e[0] /= e[3];
	e[1] /= e[3];
	e[2] /= e[3];
	e[3] = 1;
	return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
}

Vec4::~Vec4() = default;

Vec4 operator*(double t, const Vec4 &v) {
	return v * t;
}
