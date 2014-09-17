#pragma once

#include "Singleton.h"
#include <vector>
#include <fmod.hpp>

class CBox ;

class CBoxManager : public Singleton<CBoxManager>
{
private :
	std::vector<CBox*> m_BoxList ;

	FMOD::Sound *m_pCrash ;

public :
	CBoxManager() ;
	~CBoxManager() ;

	void Init() ;

	void Update() ;

	void Render() ;

	void Clear() ;
private :
	void Collision() ;
	void CreateBox() ;
	void DeleteBox() ;

	void CreateRandomBox() ;
} ;

#define g_BoxManager CBoxManager::GetInstance()