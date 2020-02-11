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

void Path::compressSegments() {
	std::vector<PathSegment> compressed;
	for(int i = 0; i < segments.size();) {
		int j;
		Vec2f endPos = segments[i].getEnd();
		float arriveTime = segments[i].getArriveTime();
		Vec2f velocity = segments[i].getVelocity();
		int newIdx = i+1;
		for(j = i+1; j < segments.size(); j++) {
			if((segments[j].getVelocity() - velocity).mag() < 0.000001) {
				newIdx++;
				endPos = segments[j].getEnd();
				arriveTime = segments[j].getArriveTime();
			} else break;
		}
		compressed.push_back(PathSegment(segments[i].getStart(), endPos, segments[i].getStartTime(), arriveTime));
		i = newIdx;
	}
	segments = compressed;
}
