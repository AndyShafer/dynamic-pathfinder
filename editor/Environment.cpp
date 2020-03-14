#include "Environment.h"

Environment::Environment() {
	start = Vec2f(0, 0);
	end = Vec2f(10, 0);
	speed = 1;
	timeStep = .1;
}

void Environment::addWall(const Wall& wall) {
	pathDirty = true;
	walls.push_back(wall);
}

Wall& Environment::getWall(int idx) {
	pathDirty = true;
	return walls[idx];
}

void Environment::setStart(const Vec2f& s) {
	pathDirty = true;
	start = s;
}

void Environment::setEnd(const Vec2f& e) {
	pathDirty = true;
	end = e;
}

void Environment::setSpeed(float s) {
	pathDirty = true;
	speed = s;
}

void Environment::setTimeStep(float ts) {
	pathDirty = true;
	timeStep = ts;
}

int Environment::numWalls() const {
	return walls.size();
}

Vec2f Environment::pathPosAt(float t) {
	if(pathDirty) {
		pathDirty = false;
		Solver solver(walls, speed, timeStep);
		path = solver.solve(start, end);	
	}
	return path.getPos(t);
}
