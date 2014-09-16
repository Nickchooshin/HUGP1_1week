#include "Particle_Energy.h"
#include "Sprite.h"
#include "Collision.h"
#include "Player.h"

#include "D3dDevice.h"

CParticle_Energy::CParticle_Energy() : m_bGuide(false),
									   m_fForce(1.0f)
{
	m_bTime = true ;
	m_fTime = 1.0f ;
}
CParticle_Energy::~CParticle_Energy()
{
}

void CParticle_Energy::Init()
{
	m_pSprite = new CSprite ;
	m_pSprite->Init("Resource/Energy.png") ;

	float angle = rand()%36 ;
	angle = (angle * 10.0f) * D3DX_PI / 180.0f ;

	m_vecSpeed.x = 1.0f * (rand()%3+1) * cos(angle) ;
	m_vecSpeed.y = 1.0f * (rand()%3+1) * sin(angle) ;
}

void CParticle_Energy::Update()
{
	m_fX += m_vecSpeed.x ;
	m_fY += m_vecSpeed.y ;

	if(!m_bGuide)
	{
		m_vecSpeed += m_vecAcc ;
	}
	else
	{
		CCollision col ;
		float angle ;
		float PlayerX = g_Player->GetPositionX() ;
		float PlayerY = g_Player->GetPositionY() ;
		float PlayerS = g_Player->GetScale() * 10.0f ;

		angle = col.GetAngle(m_fX, m_fY, PlayerX, PlayerY) ;
		angle = angle * D3DX_PI / 180.0f ;

		m_vecSpeed.x = m_fForce * cos(angle) ;
		m_vecSpeed.y = m_fForce * sin(angle) ;

		m_fForce += 0.5f * g_D3dDevice->GetMoveTime() ;
		if(m_fForce>25.0f)
			m_fForce = 25.0f ;

		if(col.CircleCollision(m_fX, m_fY, 1.0f, PlayerX, PlayerY, PlayerS))
		{
			m_bLife = false ;
			g_Player->EnergyAbsorption() ;
		}
	}

	if(!m_bGuide)
	{
		m_fTime -= g_D3dDevice->GetTime() ;
		if(m_fTime<0.0f)
			m_bGuide = true ;
	}
}