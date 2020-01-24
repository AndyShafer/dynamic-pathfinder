#include "PathSegment.h"

PathSegment::PathSegment(Vec2f start, Vec2f end, float startTime, float arriveTime)
	: start(start), end(end), startTime(startTime), arriveTime(arriveTime) {}

Vec2f PathSegment::getStart() const { return start; }
Vec2f PathSegment::getEnd() const { return end; }
float PathSegment::getStartTime() const { return startTime; }
float PathSegment::getArriveTime() const { return arriveTime; }
