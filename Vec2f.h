#pragma once

class Vec2f {
public:
	Vec2f(float x, float y)
		: x(x), y(y) {}
	Vec2f()
		: x(0), y(0) {}
	float x;
	float y;
};
