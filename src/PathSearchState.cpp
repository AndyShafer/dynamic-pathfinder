#include "PathSearchState.h"

PathSearchState::PathSearchState()
	: pointId(0), startTime(0), waitTime(0), precision(1) {}

PathSearchState::PathSearchState(int pointId, float startTime, float waitTime, float precision)
	: pointId(pointId), startTime(startTime), waitTime(waitTime), precision(precision) {}

int PathSearchState::getPoint() const { return pointId; }

float PathSearchState::getStartTime() const { return startTime; }

float PathSearchState::getWaitTime() const { return waitTime; }

bool PathSearchState::operator==(const PathSearchState& other) const {
	if(pointId != other.pointId) return false;
	float diff1 = abs(startTime - other.startTime);
	float diff2 = abs(waitTime - other.waitTime);
	return diff1 < precision && diff2 < precision;
}

bool PathSearchState::operator!=(const PathSearchState& other) const {
	return !(*this == other);
}

bool PathSearchState::operator<(const PathSearchState& other) const {
	if(pointId < other.pointId) return true;
	if(pointId > other.pointId) return false;
	if(startTime < other.startTime && other.startTime - startTime >= precision) return true;
	if(startTime > other.startTime && startTime - other.startTime >= precision) return false;
	if(waitTime < other.waitTime && other.waitTime - waitTime >= precision) return true;
	return false;
}

