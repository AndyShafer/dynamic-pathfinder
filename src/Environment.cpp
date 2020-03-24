#include "Environment.h"

Environment::Environment() {}

Environment::Environment(Vec2f start, Vec2f end, std::vector<Wall> walls, float speed, float timeStep)
	: start(start), end(end), walls(walls), speed(speed), timeStep(timeStep) {}
