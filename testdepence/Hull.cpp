#include "pch.h"
#include "Hull.h"
Hull::Hull(const vec2 position, int h, int w, vec2 sz) :
	tankPosition(position)
{
	//this->tankPosition = position;
	this->spriteW = w;
	this->spriteH = h;
	this->SizeM = sz;
	//updateBox();
	//GetMiddlePoint();
}