#pragma once

#include "Singleton.h"

class CCollisionManager : public Singleton<CCollisionManager>
{
public :
	CCollisionManager() ;
	~CCollisionManager() ;

	void Collision() ;
} ;

#define g_CollisionManager CCollisionManager::GetInstance()