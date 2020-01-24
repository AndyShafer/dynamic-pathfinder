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
	Vec2f pc = pSeg.getStart() - vc * pSeg.getArriveTime();
	// at^2 + bt + c = 0
	float a = (vb.x - va.x) * (vc.y - va.y) - (vc.x - va.x) * (vb.y - va.y);
	float b = (vb.x - va.x) * (pc.y -pa.y) + (pb.x - pa.x) * (vc.y - va.y) -
			(vc.x - va.x) * (pb.y - pa.y) - (pc.x - pa.x) * (vb.y - va.y);
	float c = (pb.x - pa.x) * (pc.y - pa.y) - (pc.x - pa.x) * (pb.y - pa.y);
	float disc = b*b - 4*a*c;
	float eps = 0.000000001;
	if(disc < -eps) return false;
	if(disc < eps) disc = 0;
	std::vector<float> t;
	t.push_back((-b + sqrt(disc)) / (2 * a));
	t.push_back((-b - sqrt(disc)) / (2 * a));
	Point pCrawl(pc, vc);
	for(float time : t) {
		if(time < pSeg.getStartTime() || time > pSeg.getArriveTime()) continue;
		Vec2f edge = end.getPos(time) - start.getPos(time);
		float d = edge * (pCrawl.getPos(time) - start.getPos(time));
		if(d > 0 && d < edge*edge) return true;
	}
	return false;
}
