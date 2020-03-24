#pragma once

#include "Environment.h"
#include "Path.h"
#include "PathSearchState.h"
#include <vector>
#include <map>
#include <queue>
#include <algorithm>

class Solver {
public:
	Solver(Environment *env);
	Path solve() const;
private:
	Environment *env;
	Vec2f getStatePos(const PathSearchState& state, const std::vector<Point>& points) const;
	PathSegment makePathFromStates(const PathSearchState& start, const PathSearchState& end, const std::vector<Point>& points) const;
	bool isBlocked(const PathSegment& path) const;
};
