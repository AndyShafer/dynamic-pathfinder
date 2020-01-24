#include "Wall.h"

Wall::Wall(Point start, Point end)
	: start(start), end(end) {}

Point Wall::getStart() const { return start; }

Point Wall::getEnd() const { return end; }
