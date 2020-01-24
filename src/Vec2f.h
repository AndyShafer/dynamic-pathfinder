#pragma once

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
	float x;
	float y;
};
