#pragma once

#include "Wall.h"
#include <vector>

class Environment {
public:
	Environment();
	Environment(Vec2f start, Vec2f end, std::vector<Wall> walls, float speed, float timeStep);
	Vec2f start;
	Vec2f end;
	std::vector<Wall> walls;
	float speed;
	float timeStep;
};
