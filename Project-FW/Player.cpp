#include "Player.h"
#include "Sprite.h"
#include "Keyboard.h"
#include "D3dDevice.h"
#include "Data.h"

CPlayer::CPlayer() : m_fMoveAcc(g_Data->m_fMoveAcc), m_fSpinAcc(g_Data->m_fSpinAcc)
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
}