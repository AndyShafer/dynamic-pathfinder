#include <emscripten/bind.h>
#include "../PathSegment.h"

using namespace emscripten;

EMSCRIPTEN_BINDINGS(pathsegment_binding) {
	//Vec2f (*getPosFP1)() const = &Point::getPos;
	class_<PathSegment>("PathSegment")
		.constructor<Vec2f, Vec2f, float, float>()
		.function("getStart", &PathSegment::getStart)
		.function("getEnd", &PathSegment::getEnd)
		.function("getStartTime", &PathSegment::getStartTime)
		.function("getArriveTime", &PathSegment::getArriveTime)
		.function("getPos", &PathSegment::getPos)
		.function("getVelocity", &PathSegment::getVelocity);
}
