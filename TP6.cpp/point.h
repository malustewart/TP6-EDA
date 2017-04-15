#ifndef POINT_H
#define POINT_H

class point {
public:
	point(float _x = 0, float _y = 0);
	virtual ~point();
	
	void setX(float _x);
	void setY(float _y);
	float getX();
	float getY();
	
private:
	float x;
	float y;
};

#endif /* POINT_H */

