#include "point.h"

point::point(float _x, float _y) 
{
	x = _x;
	y = _y;
}


point::~point() {
}
void point::setX(float _x) { x = _x; };
void point::setY(float _y) { y = _y; };
float point::getX(){ return x; };
float point::getY(){ return y; };