#pragma once

#include "../src/Wall.h"
#include "../src/Point.h"
#include "../src/Path.h"
#include "../src/Solver.h"
#include <vector>

class Environment {
public:
	Environment();
	void addWall(const Wall& wall);
	Wall& getWall(int idx);
	void setStart(const Vec2f& s);
	void setEnd(const Vec2f& e);
	void setSpeed(float s);
	void setTimeStep(float ts);
	int numWalls() const;
	Vec2f pathPosAt(float t);
private:
	std::vector<Wall> walls;
	Vec2f start;
	Vec2f end;
	float speed;
	float timeStep;
	Path path;
	bool pathDirty = true;
};
