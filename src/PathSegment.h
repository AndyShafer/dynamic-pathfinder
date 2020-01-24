#pragma once

#include "Vec2f.h"

class PathSegment {
public:
	PathSegment(Vec2f start, Vec2f end, float startTime, float arriveTime);
	Vec2f getStart() const ;
	Vec2f getEnd() const ;
	float getStartTime() const ;
	float getArriveTime() const ;
private:
	Vec2f start;
	Vec2f end;
	float startTime;
	float arriveTime;
};
