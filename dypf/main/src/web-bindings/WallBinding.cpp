#include <emscripten/bind.h>
#include "../Wall.h"

using namespace emscripten;

EMSCRIPTEN_BINDINGS(wall_binding) {
	class_<Wall>("Wall")
		.constructor<Point, Point>()
		.function("getStart", &Wall::getStart)
		.function("getEnd", &Wall::getEnd)
		.function("blocksPath", &Wall::blocksPath);
}
