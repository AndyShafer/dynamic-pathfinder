#pragma once

#include "Point.h"

class Wall {
public:
	Wall(Point start, Point end);
	Point getStart();
	Point getEnd();
	bool blocks(const PathSegment& pSeg) const;
private:
	Point start;
	Point end;
};
