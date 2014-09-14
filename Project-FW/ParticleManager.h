#pragma once

#include "Singleton.h"
#include <vector>

class CParticle ;

class CParticleManager : public Singleton<CParticleManager>
{
private :
	std::vector<CParticle*> m_ParticleList ;

public :
	CParticleManager() ;
	~CParticleManager() ;

	void Update() ;

	void Render() ;

	void CreateParticle(float fX, float fY, int nNumber) ;

	void ParticleClear() ;
} ;

#define g_ParticleManager CParticleManager::GetInstance()