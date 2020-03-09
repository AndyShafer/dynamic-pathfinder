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
	float psx = getPos(startTime).x;
	float psy = getPos(startTime).y;
	float vsx = getVelocity().x;
	float vsy = getVelocity().y;
	float pdx = dest.getPos(startTime + waitTime).x;
	float pdy = dest.getPos(startTime + waitTime).y;
	float vdx = dest.getVelocity().x;
	float vdy = dest.getVelocity().y;
	float a = -speed*speed + vdx*vdx + vdy*vdy;
	float b = 2*((pdx-psx)*vdx + (pdy-psy)*vdy);
	float c = (pdx-psx)*(pdx-psx)+(pdy-psy)*(pdy-psy);
	float eps = -.000000001;
	float disc = b*b - 4*a*c;
	if(disc < -eps) return ret;
	if(disc < eps) disc = 0;
	float t = (-b - sqrt(disc)) / (2 * a);
	if(t >= 0)
		ret.push_back(PathSegment(getPos(startTime), dest.getPos(startTime+waitTime+t), startTime+waitTime, startTime+waitTime+t));
	if(disc != 0) {
		t = (-b + sqrt(disc)) / (2 * a);
		if(t >= 0)
			ret.push_back(PathSegment(getPos(startTime), dest.getPos(startTime+waitTime+t), startTime+waitTime, startTime+waitTime+t));
	}
	return ret;
}

