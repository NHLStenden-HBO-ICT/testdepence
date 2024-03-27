
#pragma once

#include <rectangle.h>
//this class contains a box for the hull of the tank
class Hull
{
	////interger for minpoints
	//int minPointX;
	//int minPointY;
	////integers for the outer bounds
	//int maxPointX;
	//int maxPointY;
	////the outer bounds
	//vec2 minPoints = vec2(0,0);
	//vec2 maxPoints = vec2(0,0);
	////look how big he is
	//vec2 SizeM;

	//vec2 midPoint;

/// <summary>
/// misc data
/// </summary>
	//vec2 tankPosition;

	int spriteH;
	int spriteW;

	//vec2* pointerPositionT = nullptr;


public:
	vec2 tankPosition;
	vec2* pointerPositionT = nullptr;
	//interger for minpoints
	int minPointX;
	int minPointY;
	//integers for the outer bounds
	int maxPointX;
	int maxPointY;
	//the outer bounds
	vec2 minPoints = vec2(0, 0);
	vec2 maxPoints = vec2(0, 0);
	//look how big he is
	vec2 SizeM;

	vec2 midPoint;
	//Hull() = default;
	//gather data
	Hull(const vec2 position, int h, int w, vec2 sz);


	void assignPointer(vec2& pos) {
		this->pointerPositionT = &pos;
	}
	//this method might be shady
	vec2 GetMiddlePoint() {
		midPoint = GetHullMid(minPoints, maxPoints);
		return midPoint;
	}

	//og given coorinates to draw
	//    tank_sprite->draw(screen, (int)position.x - 7 + HEALTHBAR_OFFSET, (int)position.y - 9);
	//https://learning.oreilly.com/library/view/real-time-collision-detection/9781558607323/xhtml/c04.xhtml#:-:text=The%20axis-aligned,individual%20coordinate%20values.
	//the hull is a box
	void updateBox() {
		//the tankposition is not the same of the position of the sprite
		//we are supposed to use the centre point and halfes
		// https://learning.oreilly.com/library/view/real-time-collision-detection/9781558607323/xhtml/c04.xhtml#:-:text=The%20last%20representation,along%20its%20axes%3A
		//the minpoints of the box
		minPointX = tankPosition.x - SizeM.x;
		minPointY = tankPosition.y - SizeM.y;
		//the maxpoints of the box
		//maxpoints seem shady 
		//where did the size of the tank go?
		maxPointX = minPointX + spriteW;
		maxPointY = minPointY + spriteH;

		minPoints = vec2(minPointX, minPointY);
		maxPoints = vec2(maxPointX, maxPointY);
	}
	void updateBox(vec2 tankpos) {
		this->tankPosition = tankpos;
		//the offset can be removed
		minPointX = tankPosition.x - SizeM.x;
		minPointY = tankPosition.y - SizeM.y;

		maxPointX = minPointX + spriteW;
		maxPointY = minPointY + spriteH;
		minPoints = vec2(minPointX, minPointY);
		maxPoints = vec2(maxPointX, maxPointY);
	}

	//same goes for this method
	vec2 GetHullMid(vec2 min, vec2 max) {
		float x = (min.x + max.x) / 2;
		float y = (min.y + max.y) / 2;

		return vec2(x, y);
	}

	bool HullIntersect(RectangleM& rectM)
	{
		if (minPointX > rectM.minPoint.x || rectM.minPoint.x > maxPointX) return false;
		if (minPointY < rectM.maxPoint.y || rectM.minPoint.y < maxPointY) return false;
		//if (min.x > rect.max.x || rect.min.x > max.x) return false;
		//if (min.y < rect.max.y || rect.min.y < max.y) return false;

		return true;
	};
};