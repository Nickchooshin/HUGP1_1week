#pragma once

#include "Particle.h"

class CParticle_Energy : public CParticle
{
private :
	bool m_bGuide ;
	float m_fForce ;

public :
	CParticle_Energy() ;
	~CParticle_Energy() ;

	void Init() ;

	void Update() ;
} ;