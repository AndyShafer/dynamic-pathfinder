#include <emscripten/bind.h>
#include <Vec2f.h>

using namespace emscripten;

EMSCRIPTEN_BINDINGS(vec2f_binding) {
	value_object<Vec2f>("Vec2f")
		.field("x", &Vec2f::x)
		.field("y", &Vec2f::y);
}
