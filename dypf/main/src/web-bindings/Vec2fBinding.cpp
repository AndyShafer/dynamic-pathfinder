#include <emscripten/bind.h>
#include "../Vec2f.h"

using namespace emscripten;

EMSCRIPTEN_BINDINGS(vec2f_binding) {
	class_<Vec2f>("Vec2f")
		.constructor<float, float>()
		.property("x", &Vec2f::x)
		.property("y", &Vec2f::y);
}
