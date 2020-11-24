#pragma once

#include "Wall.h"
#include <vector>
#include <iostream>
#include <fstream>

class Environment {
public:
	Environment();
	Environment(Vec2f start, Vec2f end, std::vector<Wall> walls, float speed, float timeStep);
	void save(const char* filepath) const;
	static Environment * load(const char* filepath);
	Vec2f start;
	Vec2f end;
	std::vector<Wall> walls;
	float speed;
	float timeStep;
};
