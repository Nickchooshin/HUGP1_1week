#include "inelastic_collision.h"
#include <math.h>

// inelastic_collision ºñÅº¼º Ãæµ¹
// modulus of elasticity Åº¼º °è¼ö
void inelastic_collision(float m1, float m2, float v1, float v2, float modulus)
{
	float _v1, _v2 ;
	float _v1v2 = modulus * (v1-v2) ;	// _v1 - _v2

	// m1v1 + m2v2 = m1v1' + m1v2'
	//
	// ax + by + c = 0
	// dx + ey + f = 0
	float a=m1, b=m2, c=-((m1*v1)+(m2*v2)) ;
	float d=1.0f, e=-1.0f, f=modulus * (v1-v2) ;

	float temp ;
	temp = a/d ;
	d *= temp ;
	e *= temp ;
	f *= temp ;

	b -= e ;
	c -= f ;
	_v2 = -c/b ;
	_v1 = (-(e*_v2) - f)/d ;
}

float GetAngle(float x1, float y1, float x2, float y2)
{
	/*float angle ;

	float deltaX = x2 - x1 ;
	float deltaY = y2 - y1 ;

	float distance = sqrt(deltaX * deltaX + deltaY * deltaY) ;

	angle = acosf(deltaX/distance) ;

	if(deltaY>0)
	{
		angle = 3.14 + (3.14 - angle) ;
	}*/

	/////

	float angle ;

	angle = atan2(x2-x1, y2-y1) ;
	angle = -(angle * 180.0f) / 3.141592f ;
	angle += 90.0f ;

	if(angle<0.0f)
		angle += 360.0f ;

	return angle ;
}


// angle1 bsg ;
float GetAngle2(float angle1, float angle2)
{
	float angle ;

	angle2 += 180.0f ;
	if(angle2>360.0f)
		angle2 -= 360.0f ;

	angle = angle1 - angle2 ;
	angle = angle1 + angle ;
	if(angle>360.0f)
		angle -= 360.0f ;

	return angle ;
}