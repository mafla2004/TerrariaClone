#pragma once

#include <cmath>

// ==================================================================
// VECTOR2
// ==================================================================

class Vector_2D
{
public:
	double x, y;

	double length() const;

	friend Vector_2D operator+(const Vector_2D&, const Vector_2D&);
	friend Vector_2D operator-(const Vector_2D&, const Vector_2D&);
	friend Vector_2D operator*(const Vector_2D&, double);
	friend Vector_2D operator/(const Vector_2D&, double);
	friend Vector_2D operator*(double, const Vector_2D&);

	friend double operator*(const Vector_2D&, const Vector_2D&);

	Vector_2D& operator+=(const Vector_2D&);
	Vector_2D& operator-=(const Vector_2D&);
	Vector_2D& operator*=(double);
	Vector_2D& operator/=(double);
	
	Vector_2D operator-();
	Vector_2D operator+();

	Vector_2D(double _x = 0.0, double _y = 0.0) : x(_x), y(_y) {}
	Vector_2D(const Vector_2D& v) : x(v.x), y(v.y) {}
	~Vector_2D() = default;
};

inline double Vector_2D::length() const { return sqrt(x * x + y * y); }

inline Vector_2D operator+(const Vector_2D& v, const Vector_2D& w) { return Vector_2D(v.x + w.x, v.y + w.y); }
inline Vector_2D operator-(const Vector_2D& v, const Vector_2D& w) { return Vector_2D(v.x - w.x, v.y - w.y); }
inline Vector_2D operator*(const Vector_2D& v, double n) { return Vector_2D(v.x * n, v.y * n); }
inline Vector_2D operator/(const Vector_2D& v, double n) { return Vector_2D(v.x / n, v.y / n); }
inline Vector_2D operator*(double n, const Vector_2D& v) { return Vector_2D(v.x * n, v.y * n); }

inline double operator*(const Vector_2D& v, const Vector_2D& w) { return v.x * w.x + v.y + w.y; }

inline Vector_2D& Vector_2D::operator+=(const Vector_2D& v) { x += v.x; y += v.y; return *this; }
inline Vector_2D& Vector_2D::operator-=(const Vector_2D& v) { x -= v.x; y -= v.y; return *this; }
inline Vector_2D& Vector_2D::operator*=(double n) { x *= n; y *= n; return *this; }
inline Vector_2D& Vector_2D::operator/=(double n) { x /= n; y /= n; return *this; }

inline Vector_2D Vector_2D::operator-() { return Vector_2D(-x, -y); }
inline Vector_2D Vector_2D::operator+() { return Vector_2D(*this); }