#pragma once

#include <math.h>

class PathSearchState {
public:
	PathSearchState(int pointId, float startTime, float waitTime, float precision);
	int getPoint() const;
	float getStartTime() const;
	float getWaitTime() const;
	bool operator==(const PathSearchState& other) const;
	bool operator<(const PathSearchState& other) const;
private:
	int pointId;
	float startTime;
	float waitTime;
	float precision;
};
