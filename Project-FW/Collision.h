#pragma once

class CBox ;

class CCollision
{
public :
	CCollision() ;
	~CCollision() ;

	bool CircleCollision(float x1, float y1, float r1, float x2, float y2, float r2) ;
	void InelasticCollision(CBox *pBox1, CBox *pBox2) ;
	void InelasticCollision(float m1, float m2, float v1, float v2, float modulus, float &_v1, float &_v2) ;
	float GetAngle(float x1, float y1, float x2, float y2) ;
	float AngleOfReflection(float angle1, float angle2) ;
} ;