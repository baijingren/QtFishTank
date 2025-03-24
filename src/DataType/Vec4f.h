//
// Created by Jingren Bai on 25-3-22.
//

#ifndef QTFISHTANK_VEC4F_H
#define QTFISHTANK_VEC4F_H
#include "Vec3f.h"


class Vec4f{
public:
	Vec4f();
	Vec4f(float x, float y, float z, float w);
	Vec4f(float x, float y, float z);
	Vec4f(const Vec4f &v);
	Vec4f operator+(const Vec4f &v) const;
	Vec4f operator-(const Vec4f &v) const;
	Vec4f operator*(float t) const;
	Vec4f operator/(float t) const;
	Vec4f &operator+=(const Vec4f &v);
	Vec4f &operator-=(const Vec4f &v);
	Vec4f &operator*=(float t);
	Vec4f &operator/=(float t);
	Vec4f operator-() const;
	Vec4f &operator=(const Vec4f &v);
	float operator[](int i) const;
	float& operator[](int i);
	float x();
	float y();
	float z();
	float w();
	float length();
	float lengthSquared();
	~Vec4f();
public:
	float e[4];
};

Vec4f operator*(float t, const Vec4f &v);

#endif//QTFISHTANK_VEC4F_H
