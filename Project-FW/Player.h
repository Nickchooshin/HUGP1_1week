#pragma once

#include "Box.h"
#include "Singleton.h"

class CPlayer : public CBox, public Singleton<CPlayer>
{
private :
	float m_fMoveAcc, m_fSpinAcc ;

public :
	CPlayer() ;
	~CPlayer() ;

	void Update() ;
private :
	void MoveInput() ;
	void SpinInput() ;
} ;

#define g_Player CPlayer::GetInstance()