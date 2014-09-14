#include "Particle.h"
#include "D3dDevice.h"

CParticle::CParticle() : m_bLife(true),
						 m_bTime(false),
						 m_fTime(0.0f),
						 m_vecSpeed(),
						 m_vecAcc()
{
}
CParticle::~CParticle()
{
}

void CParticle::Update()
{
	m_fX += m_vecSpeed.x ;
	m_fY += m_vecSpeed.y ;

	m_vecSpeed += m_vecAcc ;

	if(m_bTime)
	{
		m_fTime -= g_D3dDevice->GetTime() ;
		if(m_fTime<0.0f)
			m_bLife = false ;
	}
}

const bool CParticle::BeLife() const
{
	return m_bLife ;
}