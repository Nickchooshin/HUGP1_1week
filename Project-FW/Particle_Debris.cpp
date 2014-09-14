#include "Particle_Debris.h"
#include "Sprite.h"

CParticle_Debris::CParticle_Debris()
{
	m_bTime = true ;
	m_fTime = 1.0f ;
}
CParticle_Debris::~CParticle_Debris()
{
}

void CParticle_Debris::Init()
{
	m_pSprite = new CSprite ;
	m_pSprite->Init("Resource/Debris.png") ;

	m_vecSpeed.x = -1.0f * (rand()%13-6) ;
	m_vecSpeed.y = 1.0f * (rand()%5) ;

	m_vecAcc.x = m_vecSpeed.x * -0.01f ;
	m_vecAcc.y = -0.15f ;
}