#include "Box.h"
#include "Sprite.h"
#include "Data.h"
#include "BoxManager.h"

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

	if(temp - fSpinSpeed>m_fFixedSpinSpeed)
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