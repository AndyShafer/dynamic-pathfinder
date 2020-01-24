#include "Path.h"

Path::Path(const std::vector<PathSegment>& segments)
	: segments(segments) {
	compressSegments();
}

Path::Path()
	: segments(std::vector<PathSegment>()) {}

std::vector<PathSegment> Path::getSegments() const {
	return segments;
}
