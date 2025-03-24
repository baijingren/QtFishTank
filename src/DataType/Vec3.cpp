//
// Created by Jingren Bai on 25-3-22.
//

#include "Vec3.h"
#include <cmath>

Vec3::Vec3():e{0, 0, 0}{}
Vec3::Vec3(double x, double y, double z):e{x, y, z} {}
Vec3::Vec3(const Vec3 &v) {
    this->e[0] = v.e[0];
    this->e[1] = v.e[1];
    this->e[2] = v.e[2];
}
double Vec3::x() {
    return e[0];
}
double Vec3::y() {
    return e[1];
}
double Vec3::z() {
    return e[2];
}
Vec3& Vec3::operator=(const Vec3 &v) {
    if(*this == v) {
        return *this;
    }
    this->e[0] = v.e[0];
    this->e[1] = v.e[1];
    this->e[2] = v.e[2];
    return *this;
}
Vec3 Vec3::operator+(const Vec3 &v) const {
    return {this->e[0] + v.e[0], this->e[1] + v.e[1], this->e[2] + v.e[2]};
}
Vec3 Vec3::operator-(const Vec3 &v) const {
    return {this->e[0] - v.e[0], this->e[1] - v.e[1], this->e[2] - v.e[2]};
}
Vec3 Vec3::operator*(double t) const {
    return {e[0] * t, e[1] * t, e[2] * t};
}
Vec3 operator* (double t, const Vec3& v) {
    return v * t;
}
Vec3 Vec3::operator/(double t) const {
    return {e[0] / t, e[1] / t, e[2] / t};
}

Vec3 Vec3::operator+=(const Vec3 &v) const {
    return {this->e[0] + v.e[0], this->e[1] + v.e[1], this->e[2] + v.e[2]};
}
Vec3 Vec3::operator-=(const Vec3 &v) const {
    return {this->e[0] - v.e[0], this->e[1] - v.e[1], this->e[2] - v.e[2]};
}
Vec3 Vec3::operator*=(const Vec3 &v, double t) const {
    return {this->e[0] * t, this->e[1] * t, this->e[2] * t};
}
bool Vec3::operator==(const Vec3& v) const {
    return (this->e[0] == v.e[0] && this->e[1] == v.e[1] && this->e[2] == v.e[2]);
}
bool Vec3::operator!=(const Vec3& v) const {
    return (this->e[0] != v.e[0] || this->e[1] != v.e[1] || this->e[2] != v.e[2]);
}
Vec3 Vec3::operator-() const {
    return {-this->e[0], -this->e[1], -this->e[2]};
}
double Vec3::operator[](int i) const {
    return e[i];
}
double& Vec3::operator[](int i) {
    return e[i];
}
double Vec3::length() const {
    return std::sqrt(lengthSquared());
}
double Vec3::lengthSquared() const {
    return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
}
Vec3::~Vec3() = default;

