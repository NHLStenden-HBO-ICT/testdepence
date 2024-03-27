#include "pch.h"
#include "rectangle.h"

bool RectangleM::RectangleToRectangleCol(const RectangleM& a, const RectangleM& b)noexcept {
	const vec2 aMin = a.minPoint;
	const vec2 aMax = a.maxPoint;
	const vec2 bMin = b.minPoint;
	const vec2 bMax = b.maxPoint;
	//check for collision
	const bool overX = ((bMin.x <= aMax.x) && (aMin.x <= bMax.x));
	const bool overY = ((bMin.y <= aMax.y) && (aMin.y <= bMax.y));
	return overX && overY;

}
