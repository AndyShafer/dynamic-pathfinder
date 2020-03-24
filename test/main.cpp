#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../src/Point.h"
#include "../src/Wall.h"
#include "../src/Solver.h"
TEST_CASE("Position of point is queried by time", "[Point]") {
	Point notMoving(1, 2, 0, 0);
	REQUIRE(notMoving.getPos() == Vec2f(1, 2));
	REQUIRE(notMoving.getPos(0) == Vec2f(1, 2));
	REQUIRE(notMoving.getPos(10) == Vec2f(1, 2));
	REQUIRE(notMoving.getPos(0.5) == Vec2f(1, 2));
	Point moving(0, 0, 1.5, 3);
	REQUIRE(moving.getPos() == Vec2f(0, 0));
	REQUIRE(moving.getPos(0) == Vec2f(0, 0));
	REQUIRE(moving.getPos(1) == Vec2f(1.5, 3));
	REQUIRE(moving.getPos(2) == Vec2f(3, 6));
	REQUIRE(moving.getPos(0.5) == Vec2f(0.75, 1.5));
}

TEST_CASE("Points can find paths between each other", "[Point]") {
	// Test 1: Time to travel to stationary point should be speed/distance.
	Point p1(0, 0, 0, 0);
	Point p2(10, 0, 0, 0);
	auto paths1 = p1.pathsTo(p2, 1, 0, 0);
	REQUIRE(paths1.size() == 1);
	REQUIRE(paths1[0] == PathSegment(p1.getPos(), p2.getPos(), 0, 10));

	// Test 2: There are two directions that will intersect with the moving point at different times.
	Point p3(10, 0, -2, 0);
	auto paths2 = p1.pathsTo(p3, 1, 0, 0);
	REQUIRE(paths2.size() == 2);

	// Test 3: Point is moving away to fast to catch up.
	Point p4(10, 0, 2, 0);
	auto paths3 = p1.pathsTo(p4, 1, 0, 0);
	REQUIRE(paths3.size() == 0);
	paths3 = p1.pathsTo(p4, 2.1, 0, 0);
	REQUIRE(paths3.size() == 1);

	// Test 4: Path result has correct speed.
	Point p5 = Point(15, -5, 0, -.2);
	Point p6 = Point(4, 0, 0.5, -.1);
	auto paths4 = p5.pathsTo(p6, 1, 29.8074875, 0);
	REQUIRE(paths4.size() == 1);
	float speed = (paths4[0].getEnd() - paths4[0].getStart()).mag() / (paths4[0].getArriveTime() - paths4[0].getStartTime());
	REQUIRE(speed >= .999);
	REQUIRE(speed <= 1.001);
}

TEST_CASE("Walls can determine if they are blocking a path", "[Wall]") {
	// Test 1: Non-blocking wall
	PathSegment path1(Vec2f(0, 0), Vec2f(10, 0), 0, 10);
	Wall w1(Point(Vec2f(5, 5)), Point(Vec2f(5, 10)));
	REQUIRE(!w1.blocksPath(path1));

	// Test 2: Stationary blocking wall
	Wall w2(Point(Vec2f(5, 5)), Point(Vec2f(5, -5)));
	REQUIRE(w2.blocksPath(path1));

	// Test 3: Wall is in path but moves away.
	Wall w3(Point(Vec2f(5, 5), Vec2f(1, 0)), Point(Vec2f(5, -5), Vec2f(1, 0)));
	REQUIRE(!w3.blocksPath(path1));

	// Test 4: Wall is in path but moves up out of the way.
	Wall w4(Point(Vec2f(5, 5), Vec2f(0, 1.01)), Point(Vec2f(5, -5), Vec2f(0, 1.01)));
	REQUIRE(!w4.blocksPath(path1));
}

TEST_CASE("Paths can be estimated between points", "[Solver]") {
	// Test 1: No walls
	std::vector<Wall> walls;
	Environment *env1 = new Environment(Vec2f(0, 0), Vec2f(10, 0), walls, 1, .1);
	Solver solver1(env1);
	Path solution1_1 = solver1.solve();
	env1->start = Vec2f(3, 0);
	env1->end = Vec2f(0, 4);
	Path solution1_2 = solver1.solve();
	REQUIRE(solution1_1.getSegments().size() == 1);
	REQUIRE(solution1_1.getSegments()[0] == PathSegment(PathSegment(Vec2f(0, 0), Vec2f(10, 0), 0, 10)));
	REQUIRE(solution1_2.getSegments().size() == 1);
	REQUIRE(solution1_2.getSegments()[0] == PathSegment(PathSegment(Vec2f(3, 0), Vec2f(0, 4), 0, 5)));

	// Test 2: Stationary wall blocking direct path
	env1->walls.push_back(Wall(Point(5, 5, 0, 0), Point(5, -4, 0, 0)));
	Solver solver2(env1);
	env1->start = Vec2f(0, 0);
	env1->end = Vec2f(10, 0);
	Path solution2_1 = solver2.solve();
	REQUIRE(solution2_1.getSegments().size() == 2);
	REQUIRE(solution2_1.getSegments()[0].getEnd() == Vec2f(5, -4));

	// Test 3: Wall moving slower than movement speed.
	env1->walls.clear();
	env1->walls.push_back(Wall(Point(3, 5, 0, -1), Point(3, -4, 0, -2)));
	env1->end = Vec2f(6, 0);
	env1->speed = 5;
	Solver solver3(env1);
	Path solution3_1 = solver3.solve();
	REQUIRE(solution3_1.getSegments().size() == 2);
	REQUIRE(solution3_1.getSegments()[0].getEnd() == Vec2f(3, 4));

	// Test 4: Waiting for wall to change position before moving.
	env1->walls.clear();
	env1->walls.push_back(Wall(Point(1, 40, 0, -3), Point(1, -100, 0, 0)));
	env1->end = Vec2f(2, 0);
	env1->speed = 1;
	Solver solver4(env1);
	Path solution4_1 = solver4.solve();
	REQUIRE(solution4_1.getSegments().size() == 3);
	REQUIRE(solution4_1.getSegments()[0].getEnd() == Vec2f(0, 0));
	REQUIRE(solution4_1.getSegments()[1].getEnd().y < 10);

	// Test 5: Multiple walls
	env1->walls.clear();
	env1->walls.push_back(Wall(Point(3, 10, 0, -.5), Point(0, -10, 0, -.5)));
	env1->walls.push_back(Wall(Point(3, 0, 0, 0), Point(4, 0, .5, -.1)));
	env1->walls.push_back(Wall(Point(15, 5, 0, 1), Point(15, -5, 0, -.2)));
	env1->end = Vec2f(20, 0);
	Solver solver5(env1);
	Path solution5_1 = solver5.solve();
	REQUIRE(solution5_1.getSegments().size() == 5);
}
