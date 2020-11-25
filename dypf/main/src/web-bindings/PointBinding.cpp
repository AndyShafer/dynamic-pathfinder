#include <emscripten/bind.h>
//#include <functional>
#include "../Point.h"

typedef Vec2f (Point::*PointGetPos1)() const;

using namespace emscripten;

EMSCRIPTEN_BINDINGS(point_binding) {
	//Vec2f (*getPosFP1)() const = &Point::getPos;
	class_<Point>("Point")
		//.constructor<Vec2f>()
		//.constructor<Vec2f, Vec2f>()
		.constructor<float, float, float, float>()
		.function("getPos", (PointGetPos1)&Point::getPos)
		.function("getVelocity", &Point::getVelocity);
}
