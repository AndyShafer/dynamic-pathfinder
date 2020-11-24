#include "Solver.h"

#define START_OFFSET 0
#define END_OFFSET 1
#define WALLS_OFFSET 2

Solver::Solver(Environment *env)
	: env(env) {}

Path Solver::solve() const {
	std::vector<Point> points;
	points.push_back(Point(env->start));
	points.push_back(Point(env->end));
	for(Wall wall : env->walls) {
		points.push_back(wall.getStart());
		points.push_back(wall.getEnd());
	}
	std::map<PathSearchState, PathSearchState> prevState;
	auto comp = [this, &points](const PathSearchState& a, const PathSearchState& b) {
		float t1 = a.getStartTime() + a.getWaitTime();
		t1 = (t1 + (points[END_OFFSET].getPos(t1) - points[a.getPoint()].getPos(a.getStartTime())).mag()
			/ env->speed);
		float t2 = b.getStartTime() + b.getWaitTime();
		t2 = (t2 + (points[END_OFFSET].getPos(t2) - points[b.getPoint()].getPos(b.getStartTime())).mag()
			/ env->speed);
		return t1 > t2;
	};
	std::priority_queue<PathSearchState, std::vector<PathSearchState>, decltype(comp)> next(comp);
	next.push(PathSearchState(START_OFFSET, 0, 0, env->timeStep));
	prevState[next.top()] = next.top();
	PathSearchState finalState;
	bool pathExists = false;
	while(!next.empty()) {
		PathSearchState currentState = next.top();
		next.pop();
		if(currentState.getPoint() == END_OFFSET) {
			finalState = currentState;
			pathExists = true;
			break;
		}
		std::vector<PathSearchState> adjStates;
		PathSearchState waitState = PathSearchState(currentState.getPoint(),
				currentState.getStartTime(), currentState.getWaitTime()
				+ env->timeStep, env->timeStep);
		adjStates.push_back(waitState);
		for(int i = 0; i < points.size(); i++) {
			if(i == currentState.getPoint()) {
				if(currentState.getWaitTime() == 0 &&
					points[currentState.getPoint()].getVelocity().mag() <=
					env->speed &&
					points[currentState.getPoint()].getVelocity() != Vec2f(0, 0)) {
					PathSearchState followState = PathSearchState(
						currentState.getPoint(),
						currentState.getStartTime() + env->timeStep,
						0, env->timeStep);
					adjStates.push_back(followState);
				}
			} else {
				std::vector<PathSegment> hops =
					points[currentState.getPoint()].pathsTo(points[i], env->speed,
								currentState.getStartTime(),
								currentState.getWaitTime());
				for(PathSegment ps : hops) {
					adjStates.push_back(PathSearchState(i, ps.getArriveTime(), 0,
								env->timeStep));
				}
			}	
		}
		for(PathSearchState st : adjStates) {
			PathSegment path = makePathFromStates(currentState, st, points);
			if(!isBlocked(path) && prevState.find(st) == prevState.end()) {
				prevState[st] = currentState;
				next.push(st);
			}
		}
	}
	std::vector<PathSegment> segments;
	if(pathExists) {
		while(prevState[finalState] != finalState) {
			segments.push_back(makePathFromStates(prevState[finalState], finalState, points));
			finalState = prevState[finalState];
		}
		reverse(segments.begin(), segments.end());
	} 
	auto p = Path(segments);
	return Path(segments);
}

Vec2f Solver::getStatePos(const PathSearchState& state, const std::vector<Point>& points) const {
	return points[state.getPoint()].getPos(state.getStartTime());
}

PathSegment Solver::makePathFromStates(const PathSearchState& start, const PathSearchState& end,
                                       const std::vector<Point>& points) const {
	return PathSegment(getStatePos(start, points), getStatePos(end, points),
			start.getStartTime() + start.getWaitTime(),
			end.getStartTime() + end.getWaitTime());
}

bool Solver::isBlocked(const PathSegment& path) const {
	for(Wall wall : env->walls) {
		if(wall.blocksPath(path)) return true;
	}
	return false;
}
