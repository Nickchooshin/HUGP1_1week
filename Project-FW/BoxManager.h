#pragma once

#include "Singleton.h"
#include <vector>

class CBox ;

class CBoxManager : public Singleton<CBoxManager>
{
private :
	std::vector<CBox*> m_BoxList ;

public :
	CBoxManager() ;
	~CBoxManager() ;

	void Init() ;

	void Update() ;

	void Render() ;
private :
	void Collision() ;
	void CreateBox() ;
	void DeleteBox() ;

	void CreateRandomBox() ;
} ;

#define g_BoxManager CBoxManager::GetInstance()