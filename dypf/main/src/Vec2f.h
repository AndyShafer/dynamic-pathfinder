#pragma once

#include <math.h>

class Vec2f {
public:
	Vec2f(float x, float y)
		: x(x), y(y) {}
	Vec2f()
		: x(0), y(0) {}
	Vec2f operator+(const Vec2f& right) const {
		return Vec2f(x+right.x, y+right.y);
	}
	Vec2f operator-(const Vec2f& right) const {
		return Vec2f(x-right.x, y-right.y);
	}
	float operator*(const Vec2f& right) const {
		return x*right.x + y*right.y;
	}
	Vec2f operator*(float mul) const {
		return Vec2f(x*mul, y*mul);
	}
	Vec2f operator/(float div) const {
		return Vec2f(x/div, y/div);
	}
	Vec2f operator+=(const Vec2f& right) {
		x += right.x;
		y += right.y;
		return *this;
	}
	Vec2f operator-=(const Vec2f& right) {
		x -= right.x;
		y -= right.y;
		return *this;
	}
	Vec2f operator*=(float mul) {
		x *= mul;
		y *= mul;
		return *this;
	}
	Vec2f operator/=(float div) {
		x /= div;
		y /= div;
		return *this;
	}
	bool operator==(const Vec2f& other) const {
		return x == other.x && y == other.y;
	}
	bool operator!=(const Vec2f& other) const {
		return !(*this == other);
	}
	float mag() const {
		return sqrt(x*x + y*y);
	}
	float x;
	float y;
};
