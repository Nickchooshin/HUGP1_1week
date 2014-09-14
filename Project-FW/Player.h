#pragma once

#include "Box.h"
#include "Singleton.h"

class CPlayer : public CBox, public Singleton<CPlayer>
{
public :
	CPlayer() ;
	~CPlayer() ;

	void Update() ;

	void EnergyAbsorption() ;
private :
	void MoveInput() ;
	void SpinInput() ;
} ;

#define g_Player CPlayer::GetInstance()