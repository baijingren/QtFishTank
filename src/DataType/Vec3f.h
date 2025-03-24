//
// Created by Jingren Bai on 25-3-22.
//

#ifndef QTFISHTANK_VEC3F_H
#define QTFISHTANK_VEC3F_H
#include <fluid/FluidSimulator.h>


class Vec3f {
public:
	Vec3f();
	Vec3f(float x, float y, float z);
	Vec3f(const Vec3f& v);
	float x() const;
	float y() const;
	float z() const;
	Vec3f& operator=(const Vec3f& v);
	Vec3f operator+(const Vec3f& v) const;
	Vec3f operator-(const Vec3f& v) const;
	Vec3f & operator*(float t) const;
	Vec3f operator/(float t) const;
	Vec3f& operator+=(const Vec3f& v);
	Vec3f& operator-=(const Vec3f& v);
	bool operator==(const Vec3f& v) const;
	bool operator!=(const Vec3f& v) const;
	Vec3f operator-() const;
	float operator[](int i) const;
	float& operator[](int i);
	float length() const;
	float lengthSquared() const;
	~Vec3f();


public:
	float e[3]{};
};

Vec3f operator*(double t, const Vec3f &v);

#endif//QTFISHTANK_VEC3F_H
