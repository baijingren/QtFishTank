//
// Created by Jingren Bai on 25-3-22.
//

#ifndef QTFISHTANK_VEC4_H
#define QTFISHTANK_VEC4_H


class Vec4 {
public:
	Vec4();
	Vec4(double x, double y, double z, double w);
	Vec4(const Vec4 &v);
	double x();
	double y();
	double z();
	double w();
	Vec4 operator+(const Vec4 &v) const;
	Vec4 operator-(const Vec4 &v) const;
	Vec4 operator*(double t) const;
	Vec4 operator/(double t) const;
	Vec4 operator-() const;
	Vec4 &operator+=(const Vec4 &v);
	Vec4 &operator-=(const Vec4 &v);
	Vec4 &operator*=(double t);
	Vec4 &operator/=(double t);
	bool operator==(const Vec4 &v) const;
	bool operator!=(const Vec4 &v) const;
	double operator[](int i) const;
	double& operator[](int i);
	[[nodiscard]] double length() ;
	[[nodiscard]] double lengthSquared() ;
	~Vec4();
public:
	double e[4]{};
};

Vec4 operator*(double t, const Vec4 &v);

#endif//QTFISHTANK_VEC4_H
