#include "Point.h"
#include <math.h>

Point::Point(Vec2f pos)
	: startPos(pos), velocity(Vec2f()) {}

Point::Point(Vec2f startPos, Vec2f velocity)
	: startPos(startPos), velocity(velocity) {}

Point::Point(float px, float py, float vx, float vy)
	: startPos(Vec2f(px, py)), velocity(Vec2f(vx, vy)) {}

Vec2f Point::getPos() const {
	return getPos(0);
}

Vec2f Point::getPos(float t) const {
	return Vec2f(startPos.x + t * velocity.x, startPos.y + t * velocity.y);
}

Vec2f Point::getVelocity() const { return velocity; }

std::vector<PathSegment> Point::pathsTo(const Point& dest, float speed, float startTime, float waitTime) const {
	std::vector<PathSegment> ret;
	float psx = getPos().x;
	float psy = getPos().y;
	float vsx = getVelocity().x;
	float vsy = getVelocity().y;
	float pdx = dest.getPos().x;
	float pdy = dest.getPos().y;
	float vdx = dest.getVelocity().x;
	float vdy = dest.getVelocity().y;
	float a = -speed*speed + vdx*vdx + vdy*vdy;
	float b = 2*speed*speed*(startTime + waitTime) + 2 * (pdx*vdx - vdx*psx - vdx*vsx*startTime +
	                                                      pdy*vdy - vdy*psy - vdy*vsy*startTime);
	float c = -speed*speed*(waitTime*waitTime + startTime*startTime + 2*waitTime*startTime)
			+ pow(pdx - psx - vsx*startTime, 2)
			+ pow(pdy - psy - vsy*startTime, 2);
	float eps = -.000000001;
	float disc = b*b - 2*a*c;
	if(disc < -eps) return ret;
	if(disc < eps) disc = 0;
	float t = (-b - sqrt(disc)) / (2 * a);
	ret.push_back(PathSegment(getPos(startTime), dest.getPos(t), startTime+waitTime, t));
	if(disc != 0) {
		float t = (-b + sqrt(disc)) / (2 * a);
		ret.push_back(PathSegment(getPos(startTime), dest.getPos(t), startTime+waitTime, t));
	}
	return ret;
}

