#include "Box.h"
#include "Sprite.h"
#include "Data.h"
#include "BoxManager.h"
#include "Player.h"
#include "Collision.h"

#include "D3dDevice.h"

CBox::CBox() : m_bLife(true),
			   m_fScale(1.0f),
			   m_fRotation(0.0f),
			   m_fSpinSpeed(6.0f),
			   m_Vector(),
			   m_fMoveAcc(g_Data->m_fMoveAcc), m_fSpinAcc(g_Data->m_fSpinAcc),
			   m_fFixedSpinSpeed(10.0f)
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

	SpinColor() ;
}

void CBox::SetScale(float fScale)
{
	m_fScale = fScale ;
	m_pSprite->SetScale(m_fScale, m_fScale) ;
}

void CBox::SetSpinSpeed(float fSpinSpeed)
{
	m_fSpinSpeed = fSpinSpeed ;
}

void CBox::SetVector(Vector vec)
{
	m_Vector = vec ;
}

void CBox::SetFixedSpinSpeed(float fFixedSpinSpeed)
{
	m_fFixedSpinSpeed = fFixedSpinSpeed ;
}

const float CBox::GetScale() const
{
	return m_fScale ;
}

const float CBox::GetSpinSpeed() const
{
	return m_fSpinSpeed ;
}

const float CBox::GetSpinSpeedAbs() const
{
	if(m_fSpinSpeed<0.0f)
		return -m_fSpinSpeed ;

	return m_fSpinSpeed ;
}

const Vector CBox::GetVector() const
{
	return m_Vector ;
}

const bool CBox::BeLife() const
{
	return m_bLife ;
}

void CBox::SpinAccelerate(float fSpinAcc)
{
	bool bSign1, bSign2 ;

	if(m_fSpinSpeed==0.0f || fSpinAcc==0.0f)
	{
		m_bLife = false ;
	}
	else
	{
		if(m_fSpinSpeed>0.0f)
			bSign1 = true ;
		else if(m_fSpinSpeed<0.0f)
			bSign1 = false ;

		if(fSpinAcc>0.0f)
			bSign2 = true ;
		else if(fSpinAcc<0.0f)
			bSign2 = false ;

		if(bSign1!=bSign2)
			m_bLife = false ;
		else
			m_fSpinSpeed = fSpinAcc ;
	}
}

void CBox::Spin()
{
	float fSpinSpeed = m_fSpinAcc * g_D3dDevice->GetMoveTime() ;
	float temp = m_fSpinSpeed < 0.0f ? -m_fSpinSpeed : m_fSpinSpeed ;
	float temp2 = m_fFixedSpinSpeed < 0.0f ? -m_fFixedSpinSpeed : m_fFixedSpinSpeed ;

	if(temp - fSpinSpeed>temp2)
	{
		if(m_fSpinSpeed>0.0f)
			m_fSpinSpeed -= fSpinSpeed ;
		else if(m_fSpinSpeed<0.0f)
			m_fSpinSpeed += fSpinSpeed ;
	}
	else
	{
		m_fSpinSpeed = m_fFixedSpinSpeed ;
	}

	if(m_fSpinSpeed>m_fScale * 15.0f)
		m_fSpinSpeed = m_fScale * 15.0f ;
	else if(m_fSpinSpeed<m_fScale * -15.0f)
		m_fSpinSpeed = m_fScale * -15.0f ;
	m_fRotation += m_fSpinSpeed ;

	m_pSprite->SetAngle(m_fRotation) ;
}

void CBox::Move()
{
	float fAcceleration = m_fMoveAcc * g_D3dDevice->GetMoveTime() ;
	float temp ;
	float temp2 ;

	CCollision col ;
	float angle ;
	float PlayerX = g_Player->GetPositionX() ;
	float PlayerY = g_Player->GetPositionY() ;

	angle = col.GetAngle(m_fX, m_fY, PlayerX, PlayerY) ;
	angle = angle * D3DX_PI / 180.0f ;

	m_Vector.x += cos(angle) * m_fMoveAcc ;
	m_Vector.y += sin(angle) * m_fMoveAcc ;

	float fBoxForce = g_Data->m_fBoxForceMax ;
	float fForce = sqrt((m_Vector.x * m_Vector.x) + (m_Vector.y * m_Vector.y)) ;
	if(fForce>fBoxForce)
	{
		fForce = fBoxForce / fForce ;
		m_Vector = m_Vector * fForce ;
	}

	m_fX += m_Vector.x ;
	m_fY += m_Vector.y ;
}

void CBox::SpinColor()
{
	// 회전 방향에 따른 색
	int r, g, b ;
	float percentage ;
	r = g = b = 255 ;

	if(m_fSpinSpeed>=0.0f)
	{
		r -= 92 ;
		g -= 200 ;
		b -= 255 ;
		percentage = m_fSpinSpeed / (m_fScale * 15.0f) ;
	}
	else
	{
		r -= 255 ;
		g -= 96 ;
		b -= 96 ;
		percentage = m_fSpinSpeed / (m_fScale * -15.0f) ;
	}
	r = 255 - (int)(r * percentage) ;
	g = 255 - (int)(g * percentage) ;
	b = 255 - (int)(b * percentage) ;
	m_pSprite->SetRGB(r, g, b) ;
}