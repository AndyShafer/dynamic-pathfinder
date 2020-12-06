#include <emscripten/bind.h>
#include "../Path.h"

using namespace emscripten;

EMSCRIPTEN_BINDINGS(path_binding) {
	class_<Path>("Path")
		.constructor<const std::vector<PathSegment>&>()
		.constructor<>()
		.function("addSegment", &Path::addSegment)
		.function("getPos", &Path::getPos)
		.function("getArriveTime", &Path::getArriveTime)
		.function("getSegments", &Path::getSegments);

	register_vector<PathSegment>("vector<PathSegment>");
}
