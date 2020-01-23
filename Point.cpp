#include "Point.h"

Point:Point(Vec2f pos)
	: startPos(pos), velocity(Vec2f()) {}

Point:Point(Vec2f startPos, Vec2f velocity)
	: startPos(startPos), velocity(velocity) {}

Point:Point(float px, float py, float vx, float vy)
	: startPos(Vec2f(px, py)), velocity(Vec2f(vx, vy)) {}

Vec2f Point::getPos() const {
	return getPos(0);
}

Vec2f Point::getPos(float t) const {
	return Vec2f(startPos.x + t * velocity.x, startPos.y + t * velocity.y);
}

Vec2f Point::getVelocity() const { return velocity; }
