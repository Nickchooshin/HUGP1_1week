#include "Collision.h"
#include "Data.h"
#include <math.h>
#include "Box.h"

CCollision::CCollision()
{
}
CCollision::~CCollision()
{
}

bool CCollision::CircleCollision(float x1, float y1, float r1, float x2, float y2, float r2)
{
	float distance ;
	float x = (float)(x2 - x1) ;
	float y = (float)(y2 - y1) ;

	distance = sqrt((x*x) + (y*y)) ;

	if(distance<=(r1 + r2))
		return true ;

	return false ;
}

void CCollision::InelasticCollision(CBox *pBox1, CBox *pBox2)
{
	Vector vecBox1 = pBox1->GetVector() ;
	Vector vecBox2 = pBox2->GetVector() ;

	float vecForceBox1 = sqrt((vecBox1.x * vecBox1.x) + (vecBox1.y * vecBox1.y)) ;
	float vecForceBox2 = sqrt((vecBox2.x * vecBox2.x) + (vecBox2.y * vecBox2.y)) ;

	// 비탄성 충돌
	float _vecForceBox1, _vecForceBox2 ;
	float spinSpeedBox1 = pBox1->GetSpinSpeedAbs() ;
	float spinSpeedBox2 = pBox2->GetSpinSpeedAbs() ;
	float modulus = g_Data->m_fModulus ;
	float mass = g_Data->m_fMass ;
	InelasticCollision((spinSpeedBox1 * mass) + 1.0f, (spinSpeedBox2 * mass) + 1.0f, vecForceBox1, vecForceBox2, modulus, _vecForceBox1, _vecForceBox2) ;

	// 회전 감속/가속
	float forceBox1 = spinSpeedBox1 * vecForceBox1 ;
	float forceBox2 = spinSpeedBox2 * vecForceBox2 ;
	float spinAccBox1, spinAccBox2 ;
	float spinModulus ;

	if(forceBox1>=forceBox2)
	{
		if(forceBox1!=0.0f)
			spinModulus = forceBox2 / forceBox1 ;
		else
			spinModulus = 1.0f ;

		spinAccBox1 = pBox1->GetSpinSpeed() + (pBox2->GetSpinSpeed() * spinModulus) ;
		spinAccBox2 = pBox2->GetSpinSpeed() + pBox1->GetSpinSpeed() ;
	}
	else
	{
		if(forceBox2!=0.0f)
			spinModulus = forceBox1 / forceBox2 ;
		else
			spinModulus = 1.0f ;

		spinAccBox1 = pBox1->GetSpinSpeed() + pBox2->GetSpinSpeed() ;
		spinAccBox2 = pBox2->GetSpinSpeed() + (pBox1->GetSpinSpeed() * spinModulus) ;
	}
	
	pBox1->SpinAccelerate(spinAccBox1) ;
	pBox2->SpinAccelerate(spinAccBox2) ;

	// 겹침 방지, 반사각
	float Box1X = pBox1->GetPositionX(), Box1Y = pBox1->GetPositionY() ;
	float Box2X = pBox2->GetPositionX(), Box2Y = pBox2->GetPositionY() ;
	float angleBox1 = GetAngle(Box1X, Box1Y, Box2X, Box2Y) ;
	float angleBox2 = GetAngle(Box2X, Box2Y, Box1X, Box1Y) ;
	float angleRBox1 = AngleOfReflection(angleBox2 + 180.0f, angleBox1) ;
	float angleRBox2 = AngleOfReflection(angleBox1 + 180.0f, angleBox2) ;

	float x = Box2X - Box1X ;
	float y = Box2Y - Box1Y ;
	float distance = sqrt((x*x) + (y*y)) ;
	
	// 겹침현상 밀어내기
	if(distance<=(48.0f))
	{
		distance = (48.0f - distance) / 2.0f ;

		vecBox1.x = cos( -((angleBox1 + 180.0f) * 3.141592f) / 180.0f ) * distance ;
		vecBox1.y = sin( -((angleBox1 + 180.0f) * 3.141592f) / 180.0f ) * distance ;
		pBox1->SetPosition(Box1X + vecBox1.x, Box1Y + vecBox1.y) ;

		vecBox2.x = cos( -((angleBox2 + 180.0f) * 3.141592f) / 180.0f ) * distance ;
		vecBox2.y = sin( -((angleBox2 + 180.0f) * 3.141592f) / 180.0f ) * distance ;
		pBox2->SetPosition(Box2X + vecBox2.x, Box2Y + vecBox2.y) ;
	}
	
	// 반사각으로 튕겨내기
	float radian ;

	radian = angleRBox1 * 3.141592f / 180.0f ;
	vecBox1.x = cos(radian) * _vecForceBox1 ;
	vecBox1.y = sin(radian) * _vecForceBox1 ;
	pBox1->SetVector(vecBox1) ;

	radian = angleRBox2 * 3.141592f / 180.0f ;
	vecBox2.x = cos(radian) * _vecForceBox2 ;
	vecBox2.y = sin(radian) * _vecForceBox2 ;
	pBox2->SetVector(vecBox2) ;
}

void CCollision::InelasticCollision(float m1, float m2, float v1, float v2, float modulus, float &_v1, float &_v2)
{
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

float CCollision::GetAngle(float x1, float y1, float x2, float y2)
{
	float angle ;

	angle = atan2(x2-x1, y2-y1) ;
	angle = -(angle * 180.0f) / 3.141592f ;
	angle += 90.0f ;

	if(angle<0.0f)
		angle += 360.0f ;

	return angle ;
}

float CCollision::AngleOfReflection(float angle1, float angle2)
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