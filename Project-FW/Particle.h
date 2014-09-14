#pragma once

#include "Objects.h"
#include "Vector.h"

class CParticle : public CObjects
{
protected :
	bool m_bLife ;
	bool m_bTime ;
	float m_fTime ;
	Vector m_vecSpeed ;
	Vector m_vecAcc ;

public :
	CParticle() ;
	virtual ~CParticle() ;

	virtual void Update() ;

	const bool BeLife() const ;
} ;