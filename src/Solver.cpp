#include "Solver.h"

#define START_OFFSET 0
#define END_OFFSET 1
#define WALLS_OFFSET 2

Solver::Solver(std::vector<Wall> walls, float speed, float timeStep)
	: walls(walls), speed(speed), timeStep(timeStep) {}

Path Solver::solve(Vec2f start, Vec2f end) const {
	std::vector<Point> points;
	points.push_back(Point(start));
	points.push_back(Point(end));
	for(Wall wall : walls) {
		points.push_back(wall.getStart());
		points.push_back(wall.getEnd());
	}
	std::map<PathSearchState, PathSearchState> prevState;
	auto comp = [this, &points](const PathSearchState& a, const PathSearchState& b) {
		float t1 = a.getStartTime() + a.getWaitTime();
		float t2 = b.getStartTime() + b.getWaitTime();
		return (t1 + (points[END_OFFSET].getPos(t1) - points[a.getPoint()].getPos(t1)).mag() / speed) < 
		       (t2 + (points[END_OFFSET].getPos(t2) - points[b.getPoint()].getPos(t2)).mag() / speed);
	};
	std::priority_queue<PathSearchState, std::vector<PathSearchState>, decltype(comp)> next(comp);
	next.push(PathSearchState(START_OFFSET, 0, 0, timeStep));
	prevState[next.top()] = next.top();
	PathSearchState finalState;
	while(!next.empty()) {
		PathSearchState currentState = next.top();
		next.pop();
		if(currentState.getPoint() == END_OFFSET) {
			finalState = currentState;
			break;
		}
		std::vector<PathSearchState> adjStates;
		PathSearchState waitState = PathSearchState(currentState.getPoint(), currentState.getStartTime(),
		                                            currentState.getWaitTime() + timeStep, timeStep);
		adjStates.push_back(waitState);
		for(int i = 0; i < points.size(); i++) {
			if(i == currentState.getPoint()) {
				if(currentState.getWaitTime() == 0 && points[currentState.getPoint()].getVelocity().mag() <= speed) {
					PathSearchState followState = PathSearchState(currentState.getPoint(),
					                                              currentState.getStartTime() + timeStep,
					                                              0, timeStep);
					adjStates.push_back(followState);
				} else {
					std::vector<PathSegment> hops =
						points[currentState.getPoint()].pathsTo(points[i], speed, currentState.getStartTime(),
						                                        currentState.getWaitTime());
					for(PathSegment ps : hops) {
						adjStates.push_back(PathSearchState(i, ps.getArriveTime(), 0, timeStep));
					}
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
	while(prevState[finalState] != finalState) {
		segments.push_back(makePathFromStates(prevState[finalState], finalState, points));
		finalState = prevState[finalState];
	}
	reverse(segments.begin(), segments.end());
	return Path(segments);
}

Vec2f Solver::getStatePos(const PathSearchState& state, const std::vector<Point>& points) const {
	return points[state.getPoint()].getPos(state.getStartTime());
}

PathSegment Solver::makePathFromStates(const PathSearchState& start, const PathSearchState& end,
                                       const std::vector<Point>& points) const {
	return PathSegment(getStatePos(start, points), getStatePos(end, points), start.getStartTime() + start.getWaitTime(),
	                   end.getStartTime() + end.getWaitTime());
}

bool Solver::isBlocked(const PathSegment& path) const {
	for(Wall wall : walls) {
		if(wall.blocksPath(path)) return true;
	}
	return false;
}
