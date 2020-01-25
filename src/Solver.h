#pragma once

#include "Wall.h"
#include "Path.h"
#include <vector>

class Solver {
public:
	Solver(std::vector<Wall> walls, float speed, float timeStep);
	Path solve(Vec2f start, Vec2f end);
private:
	std::vector<Wall> walls;
	float speed;
	float timeStep;
};
