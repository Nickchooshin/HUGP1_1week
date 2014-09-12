#include "Box.h"
#include "Sprite.h"

#include "D3dDevice.h"

CBox::CBox() : m_fScale(1.0f),
			   m_fRotation(0.0f),
			   m_fSpinSpeed(6.0f),
			   m_Vector()
{
}
CBox::~CBox()
{
}

void CBox::Init()
{
	m_pSprite = new CSprite ;
	m_pSprite->Init("Resource/48.png") ;
}

void CBox::Update()
{
	Spin() ;
	Move() ;
}

void CBox::SetScale(float fScale)
{
	m_fScale = fScale ;
	m_pSprite->SetScale(m_fScale, m_fScale) ;
}

void CBox::SetVector(Vector vec)
{
	m_Vector = vec ;
}

const float CBox::GetScale() const
{
	return m_fScale ;
}

const Vector CBox::GetVector() const
{
	return m_Vector ;
}

void CBox::Spin()
{
	m_fRotation += m_fSpinSpeed * g_D3dDevice->GetMoveTime() ;
	m_pSprite->SetAngle(m_fRotation) ;
}

void CBox::Move()
{
	float fDeceleration = 0.05f * g_D3dDevice->GetMoveTime() ;
	float temp ;

	temp = m_Vector.y < 0.0f ? -m_Vector.y : m_Vector.y ;
	if(temp - fDeceleration>0.0f)
	{
		if(m_Vector.y>0.0f)
			m_Vector.y -= fDeceleration ;
		else
			m_Vector.y += fDeceleration ;
	}
	else
	{
		m_Vector.y = 0.0f ;
	}
	
	temp = m_Vector.x < 0.0f ? -m_Vector.x : m_Vector.x ;
	if(temp - fDeceleration>0.0f)
	{
		if(m_Vector.x>0.0f)
			m_Vector.x -= fDeceleration ;
		else
			m_Vector.x += fDeceleration ;
	}
	else
	{
		m_Vector.x = 0.0f ;
	}

	m_fX += m_Vector.x ;
	m_fY += m_Vector.y ;
}