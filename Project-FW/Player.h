#pragma once

#include "Box.h"
#include "Singleton.h"

class CPlayer : public CBox, public Singleton<CPlayer>
{
private :
	unsigned int m_nScore ;
	bool m_bGameover ;

public :
	CPlayer() ;
	~CPlayer() ;

	void Init() ;

	void EnergyAbsorption() ;
	void Gameover() ;

	const int GetScore() const ;
	const bool BeGameover() const ;
private :
	void Spin() ;
	void Move() ;
} ;

#define g_Player CPlayer::GetInstance()