#pragma once

#include "Objects.h"
#include "Vector.h"

class CBox : public CObjects
{
protected :
	float m_fScale ;
	float m_fRotation, m_fSpinSpeed ;
	Vector m_Vector ;

public :
	CBox() ;
	virtual ~CBox() ;

	void Init() ;

	virtual void Update() ;

	void SetScale(float fScale) ;
	void SetVector(Vector vec) ;

	const float GetScale() const ;
	const Vector GetVector() const ;
protected :
	void Spin() ;
	void Move() ;
} ;