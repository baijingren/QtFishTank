//
// Created by Jingren Bai on 25-3-22.
//

#ifndef QTFISHTANK_VEC3_H
#define QTFISHTANK_VEC3_H


class Vec3 {
public:
	Vec3();
	Vec3(double x, double y, double z);
	Vec3(const Vec3& v);
	double x();
	double y();
	double z();
	Vec3& operator=(const Vec3& v);
	Vec3 operator+(const Vec3& v) const;
	Vec3 operator-(const Vec3& v) const;
	Vec3 operator*(double x) const;
	Vec3 operator/(double t) const;
	Vec3 operator+=(const Vec3& v) const;
	Vec3 operator-=(const Vec3& v) const;
	Vec3 operator*=(const Vec3& v, double t) const;
	bool operator==(const Vec3& v) const;
	bool operator!=(const Vec3& v) const;
	Vec3 operator-() const;
	double operator[](int i) const;
	double& operator[](int i);
	[[nodiscard]] double length() const;
	[[nodiscard]] double lengthSquared() const;
	~Vec3();
public:
	double e[3]{};
};
Vec3 operator* (double t, const Vec3& v);

#endif//QTFISHTANK_VEC3_H
