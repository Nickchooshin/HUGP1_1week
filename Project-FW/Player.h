#pragma once

#include "Box.h"
#include "Singleton.h"

class CPlayer : public CBox, public Singleton<CPlayer>
{
private :
	int m_nScore ;

public :
	CPlayer() ;
	~CPlayer() ;

	void Update() ;

	void EnergyAbsorption() ;

	const int GetScore() const ;
private :
	void MoveInput() ;
	void SpinInput() ;
} ;

#define g_Player CPlayer::GetInstance()