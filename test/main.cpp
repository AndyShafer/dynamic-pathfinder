#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../src/Point.h"

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
	Point p1(0, 0, 0, 0);
	Point p2(10, 0, 0, 0);
	auto paths1 = p1.pathsTo(p2, 1, 0, 0);
	REQUIRE(paths1.size() == 1);
	REQUIRE(paths1[0] == PathSegment(p1.getPos(), p2.getPos(), 0, 10));
}
