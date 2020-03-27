#include "Environment.h"

Environment::Environment() {}

Environment::Environment(Vec2f start, Vec2f end, std::vector<Wall> walls, float speed, float timeStep)
	: start(start), end(end), walls(walls), speed(speed), timeStep(timeStep) {}

void Environment::save(const char* filepath) const {
	std::ofstream file;
	file.open(filepath);
	file << start.x << " " << start.y << "\n";
	file << end.x << " " << end.y << "\n";
	file << speed << "\n";
	file << timeStep << "\n";
	for(int i = 0; i < walls.size(); i++) {
		file << walls[i].getStart().getPos().x << " "
		     << walls[i].getStart().getPos().y << " "
		     << walls[i].getStart().getVelocity().x <<  " "
		     << walls[i].getStart().getVelocity().y << " "
		     << walls[i].getEnd().getPos().x << " "
		     << walls[i].getEnd().getPos().y << " "
		     << walls[i].getEnd().getVelocity().x << " "
		     << walls[i].getEnd().getVelocity().y;
		if(i != walls.size()-1)
			file << "\n";
	}
	file.close();
}

Environment * Environment::load(const char* filepath) {
	Environment *env = new Environment();
	std::ifstream file;
	file.open(filepath);
	file >> env->start.x >> env->start.y;
	file >> env->end.x >> env->end.y;
	file >> env->speed;
	file >> env->timeStep;
	float spx, spy, svx, svy, epx, epy, evx, evy;
	while(file >> spx >> spy >> svx >> svy >> epx >> epy >> evx >> evy) {
		env->walls.push_back(Wall(Point(spx, spy, svx, svy), Point(epx, epy, evx, evy)));
	}
	return env;
}
