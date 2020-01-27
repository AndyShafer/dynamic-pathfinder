#pragma once

#include "Wall.h"
#include "Path.h"
#include "PathSearchState.h"
#include <vector>
#include <map>
#include <queue>
#include <algorithm>

class Solver {
public:
	Solver(std::vector<Wall> walls, float speed, float timeStep);
	Path solve(Vec2f start, Vec2f end) const;
private:
	std::vector<Wall> walls;
	float speed;
	float timeStep;
	Vec2f getStatePos(const PathSearchState& state, const std::vector<Point>& points) const;
	PathSegment makePathFromStates(const PathSearchState& start, const PathSearchState& end, const std::vector<Point>& points) const;
	bool isBlocked(const PathSegment& path) const;
};
