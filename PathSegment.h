#pragma once

#include "Vec2f.h"

class PathSegment {
public:
	PathSegment(Vec2f start, Vec2f end, float startTime, float arriveTime);
	Vec2f getStart();
	Vec2f getEnd();
	float getStartTime();
	float getArriveTime();
private:
	Vec2f start;
	Vec2f end;
	float startTime;
	float arriveTime;
};
