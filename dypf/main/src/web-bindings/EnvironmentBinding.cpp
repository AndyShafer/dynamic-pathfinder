#include <emscripten/bind.h>
#include "../Environment.h"

using namespace emscripten;

Environment *getEnvironmentPointer(Environment& e) {
	return &e;
}

EMSCRIPTEN_BINDINGS(environment_binding) {
	class_<Environment>("Environment")
		.constructor<>()
		.constructor<Vec2f, Vec2f, std::vector<Wall>, float, float>()
		.property("start", &Environment::start)
		.property("end", &Environment::end)
		.property("walls", &Environment::walls)
		.property("speed", &Environment::speed)
		.property("timeStep", &Environment::timeStep);

	register_vector<Wall>("vector<Wall>");

	function("getEnvironmentPointer", &getEnvironmentPointer, allow_raw_pointers());
}
