#pragma once

#include "Objects.h"
#include "Vector.h"

class CBox : public CObjects
{
protected :
	bool m_bLife ;
	float m_fScale ;
	float m_fRotation, m_fSpinSpeed ;
	Vector m_Vector ;

public :
	CBox() ;
	virtual ~CBox() ;

	void Init() ;

	virtual void Update() ;

	void SetScale(float fScale) ;
	void SetSpinSpeed(float fSpinSpeed) ;
	void SetVector(Vector vec) ;

	const float GetScale() const ;
	const float GetSpinSpeed() const ;
	const float GetSpinSpeedAbs() const ;
	const Vector GetVector() const ;

	const bool BeLife() const ;

	void SpinAccelerate(float fSpinAcc) ;
protected :
	void Spin() ;
	void Move() ;
} ;