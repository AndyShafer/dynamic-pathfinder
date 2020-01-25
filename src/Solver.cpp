#include "Solver.h"

Solver::Solver(std::vector<Wall> walls, float speed, float timeStep)
	: walls(walls), speed(speed), timeStep(timeStep) {}
