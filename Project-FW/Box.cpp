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
			   m_fSpinSpeed(0.0f),
			   m_Vector(),
			   m_fMoveAcc(g_Data->m_fMoveAcc), m_fSpinAcc(g_Data->m_fSpinAcc),
			   m_fFixedSpinSpeed(0.0f)
{
	for(int i=0; i<3; i++)
		m_pAfterImage[i] = NULL ;
}
CBox::~CBox()
{
	for(int i=0; i<3; i++)
	{
		if(m_pAfterImage[i]!=NULL)
			delete m_pAfterImage[i] ;
	}
}

void CBox::Init()
{
	m_pSprite = new CSprite ;
	m_pSprite->Init("Resource/Image/Box.png") ;

	for(int i=0; i<3; i++)
	{
		m_pAfterImage[i] = new CSprite ;
		m_pAfterImage[i]->Init("Resource/Image/Box.png") ;
		m_pAfterImage[i]->SetAlpha(255-(63*(i+1))) ;
	}

	m_bLife = true ;
	m_fScale = 1.0f ;
	m_fRotation = 0.0f ;
	m_fSpinSpeed = 0.0f ;
	m_Vector = m_Vector * 0.0f ;
}

void CBox::InitAfterImagePosition()
{
	m_pSprite->SetPosition(m_fX, m_fY) ;

	for(int i=0; i<3; i++)
		m_pAfterImage[i]->SetPosition(m_fX, m_fY) ;
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
	for(int i=0; i<3; i++)
		m_pAfterImage[i]->SetScale(m_fScale, m_fScale) ;
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

void CBox::Render()
{
	AfterImage() ;

	for(int i=2; i>=0; i--)
		m_pAfterImage[i]->Render() ;

	m_pSprite->SetPosition(m_fX, m_fY) ;
	m_pSprite->Render() ;
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
	for(int i=0; i<3; i++)
		m_pAfterImage[i]->SetRGB(r, g, b) ;
}

void CBox::AfterImage()
{
	D3DXVECTOR3 position ;
	float angle ;

	for(int i=2; i>=1; i--)
	{
		position = m_pAfterImage[i-1]->GetPosition() ;
		m_pAfterImage[i]->SetPosition(position.x, position.y) ;
		m_pAfterImage[i]->SetAngle(m_fRotation) ;
	}

	position = m_pSprite->GetPosition() ;
	m_pAfterImage[0]->SetPosition(position.x, position.y) ;
	m_pAfterImage[0]->SetAngle(m_fRotation) ;
}