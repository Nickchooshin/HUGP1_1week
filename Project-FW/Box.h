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

	float m_fMoveAcc, m_fSpinAcc ;

	//
	CSprite *m_pAfterImage[3] ;
private :
	float m_fFixedSpinSpeed ;

public :
	CBox() ;
	virtual ~CBox() ;

	virtual void Init() ;
	void InitAfterImagePosition() ;

	virtual void Update() ;

	void SetScale(float fScale) ;
	void SetSpinSpeed(float fSpinSpeed) ;
	void SetVector(Vector vec) ;
	//
	void SetFixedSpinSpeed(float fFixedSpinSpeed) ;

	const float GetScale() const ;
	const float GetSpinSpeed() const ;
	const float GetSpinSpeedAbs() const ;
	const Vector GetVector() const ;

	const bool BeLife() const ;

	void SpinAccelerate(float fSpinAcc) ;

	void Render() ;
protected :
	virtual void Spin() ;
	virtual void Move() ;

	void SpinColor() ;
	void AfterImage() ;
} ;