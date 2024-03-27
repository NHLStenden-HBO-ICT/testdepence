
#pragma once
#include <ContainerTypes.h>
//3:00 wow
//wish i did more things

static vec2 GetMinMV(const vec2& ori, const vec2& size) {
	const vec2 p1 = ori;
	const vec2 p2 = ori + size;

	return vec2(fminf(p1.x, p2.x), fminf(p1.y, p2.y));
}
static vec2 GetMaxMV(const vec2& ori, const vec2& size) {
	const vec2 p1 = ori;
	const vec2 p2 = ori + size;
	return vec2(fmaxf(p1.x, p2.x), fmaxf(p1.y, p2.y));
}

//this class is a rectangle and will be used into the quadtree
//code based on
//https://learning.oreilly.com/library/view/game-physics-cookbook/9781787123663/ch04s05.html
class RectangleM
{

public:
	//the original point in the map
	vec2 origen;
	//the size in x and y
	vec2 size;

	vec2 minPoint;
	vec2 maxPoint;

	RectangleM() {

		size.x = 1;
		size.y = 1;
	}
	RectangleM(vec2 oriPoint, vec2 nSize) {
		this->origen = oriPoint;
		this->size = nSize;
		//this->minPoint = oriPoint - (nSize / 2);
		this->minPoint = GetMinMV(oriPoint, nSize);

		//this->maxPoint = oriPoint + (nSize / 2);
		this->maxPoint = GetMaxMV(oriPoint, nSize);
	}
	RectangleM(vec2 minpoints, vec2 maxPoints, bool boundsAreKnown) {
		this->minPoint = minpoints;
		this->maxPoint = maxPoints;
	}
	static bool RectangleToRectangleCol(const RectangleM& a, const RectangleM& b) noexcept;
};
//get the lower left bounds
static vec2 GetMinM(const RectangleM& rect) {
	const vec2 p1 = rect.origen;
	const vec2 p2 = rect.origen + rect.size;

	return vec2(fminf(p1.x, p2.x), fminf(p1.y, p2.y));
}
//get the upper right bounds
static vec2 GetMaxM(const RectangleM& rect) {
	const vec2 p1 = rect.origen;
	const vec2 p2 = rect.origen + rect.size;
	return vec2(fmaxf(p1.x, p2.x), fmaxf(p1.y, p2.y));
}

//create a rectangle form the given min and max bounds
//its practicly the same as the Rectangle2D
static RectangleM FromMinMaxBounds(const vec2& min, const vec2& max) {
	return RectangleM(min, max - min);
}

static vec2 GetMiddle(int h, int w) {

	const vec2 begin = vec2(0, 0);
	const float x = (begin.x + w) / 2;
	const float y = (begin.y + h) / 2;

	return vec2(x, y);
}
static vec2 GetMiddle(vec2 min, vec2 max) {
	float x = (min.x + max.x) / 2;
	float y = (min.y + max.y) / 2;

	return vec2(x, y);
}
static bool HullIntersect(RectangleM& recti, RectangleM& rectM)
{
	if (recti.minPoint.x > rectM.minPoint.x || rectM.minPoint.x > recti.maxPoint.x) return false;
	if (recti.minPoint.y < rectM.maxPoint.y || rectM.minPoint.y < recti.maxPoint.y) return false;

	return true;
}
static bool is_box_inside(RectangleM& pappa, RectangleM& boxToCheck) {
	// Check if the child box is completely inside the parent box.
	if ((pappa.minPoint.x <= boxToCheck.minPoint.x) &&
		(pappa.minPoint.y <= boxToCheck.minPoint.y) &&
		(pappa.maxPoint.x >= boxToCheck.maxPoint.x) &&
		(pappa.maxPoint.y >= boxToCheck.maxPoint.y)) {
		return true;
	}
	else {
		return false;
	}
};

