#include "Wall.h"
#include <vector>
#include <math.h>

Wall::Wall(Point start, Point end)
	: start(start), end(end) {}

Point Wall::getStart() const { return start; }

Point Wall::getEnd() const { return end; }

bool Wall::blocksPath(const PathSegment& pSeg) const {
	Vec2f pa = start.getPos();
	Vec2f pb = end.getPos();
	Vec2f va = start.getVelocity();
	Vec2f vb = end.getVelocity();
	Vec2f vc = (pSeg.getEnd() - pSeg.getStart()) / (pSeg.getArriveTime() - pSeg.getStartTime());
	Vec2f pc = pSeg.getStart() - vc * pSeg.getStartTime();
	// at^2 + bt + c = 0
	float a = (vc.y-va.y)*(vb.x-vc.x) - (vc.x-va.x)*(vb.y-vc.y);
	float b = (vc.y-va.y)*(pb.x-pc.x) - (vc.x-va.x)*(pb.y-pc.y) +
	          (pc.y-pa.y)*(vb.x-vc.x) - (pc.x-pa.x)*(vb.y-vc.y);
	float c = (pc.y-pa.y)*(pb.x-pc.x) - (pc.x-pa.x)*(pb.y-pc.y);
	float disc = b*b - 4*a*c;
	float eps = 0.00001;
	// Avoid dividing by zero if path doesn't change distance from the wall.
	std::vector<float> t;
	if(abs(a) < eps) {
		if(b == 0) return false;
		t.push_back(-c/b);
	} else {
		if(disc < -eps) return false;
		if(disc < eps) disc = 0;
		t.push_back((-b + sqrt(disc)) / (2 * a));
		t.push_back((-b - sqrt(disc)) / (2 * a));
	}
	Point pCrawl(pc, vc);
	for(float time : t) {
		if(time-eps < pSeg.getStartTime() || time+eps > pSeg.getArriveTime()) continue;
		Vec2f edge = end.getPos(time) - start.getPos(time);
		float d = edge * (pCrawl.getPos(time) - start.getPos(time));
		if(d-eps > 0 && d+eps < edge*edge) return true;
	}
	return false;
}
