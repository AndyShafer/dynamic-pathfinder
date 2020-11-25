#include <emscripten/bind.h>
#include "../Point.h"

typedef Vec2f (Point::*PointGetPos1)() const;
typedef Vec2f (Point::*PointGetPos2)(float) const;

using namespace emscripten;

EMSCRIPTEN_BINDINGS(point_binding) {
	class_<Point>("Point")
		.constructor<Vec2f>()
		.constructor<Vec2f, Vec2f>()
		.constructor<float, float, float, float>()
		.function("getPos", (PointGetPos1)&Point::getPos)
		.function("getPos", (PointGetPos2)&Point::getPos)
		.function("getVelocity", &Point::getVelocity)
		.function("pathsTo", &Point::pathsTo);
}
