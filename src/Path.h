#pragma once

#include "PathSegment.h"
#include "Vec2f.h"
#include <vector>
#include <algorithm>

class Path {
public:
	Path(const std::vector<PathSegment>& segments);
	Path();
	void addSegment(const PathSegment& segment);
	Vec2f getPos(float t);
	std::vector<PathSegment> getSegments() const;
private:
	std::vector<PathSegment> segments;
	void compressSegments();
};
