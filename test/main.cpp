#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../src/Point.h"
#include "../src/Wall.h"

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
