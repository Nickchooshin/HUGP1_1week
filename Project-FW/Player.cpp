#include "Player.h"
#include "Sprite.h"
#include "Keyboard.h"

#include "D3dDevice.h"

CPlayer::CPlayer()
{
	m_fSpinSpeed = 0.0f ;
}
CPlayer::~CPlayer()
{
}

void CPlayer::Update()
{
	MoveInput() ;
	SpinInput() ;
}

void CPlayer::EnergyAbsorption()
{
	m_fScale += 0.001f ;
	m_pSprite->SetScale(m_fScale, m_fScale) ;
}

void CPlayer::MoveInput()
{
	float fAcceleration = m_fMoveAcc * g_D3dDevice->GetMoveTime() ;
	float fDeceleration = (m_fMoveAcc/2.0f) * g_D3dDevice->GetMoveTime() ;

	if(g_Keyboard->IsButtonDown(DIK_UP))
		m_Vector.y += fAcceleration ;
	else if(g_Keyboard->IsButtonDown(DIK_DOWN))
		m_Vector.y -= fAcceleration ;
	else
	{
		float temp = m_Vector.y < 0.0f ? -m_Vector.y : m_Vector.y ;

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
	}

	if(g_Keyboard->IsButtonDown(DIK_LEFT))
		m_Vector.x -= fAcceleration ;
	else if(g_Keyboard->IsButtonDown(DIK_RIGHT))
		m_Vector.x += fAcceleration ;
	else
	{
		float temp = m_Vector.x < 0.0f ? -m_Vector.x : m_Vector.x ;

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
	}

	m_fX += m_Vector.x ;
	m_fY += m_Vector.y ;
}

void CPlayer::SpinInput()
{
	float fSpinSpeed = m_fSpinAcc * g_D3dDevice->GetMoveTime() ;

	if(g_Keyboard->IsButtonDown(DIK_A))
		m_fSpinSpeed += fSpinSpeed ;
	else if(g_Keyboard->IsButtonDown(DIK_S))
		m_fSpinSpeed -= fSpinSpeed ;
	else
	{
		float temp = m_fSpinSpeed < 0.0f ? -m_fSpinSpeed : m_fSpinSpeed ;
		fSpinSpeed = 0.05f * g_D3dDevice->GetMoveTime() ;

		if(temp - fSpinSpeed>0.0f)
		{
			if(m_fSpinSpeed>0.0f)
				m_fSpinSpeed -= fSpinSpeed ;
			else if(m_fSpinSpeed<0.0f)
				m_fSpinSpeed += fSpinSpeed ;
		}
		else
		{
			m_fSpinSpeed = 0.0f ;
		}
	}

	if(m_fSpinSpeed>m_fScale * 15.0f)
		m_fSpinSpeed = m_fScale * 15.0f ;
	else if(m_fSpinSpeed<m_fScale * -15.0f)
		m_fSpinSpeed = m_fScale * -15.0f ;
	m_fRotation += m_fSpinSpeed ;

	m_pSprite->SetAngle(m_fRotation) ;
	
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