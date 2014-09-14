#include "ParticleManager.h"
#include "Particle_Debris.h"
#include "Particle_Energy.h"

CParticleManager::CParticleManager()
{
}
CParticleManager::~CParticleManager()
{
	ParticleClear() ;
}

void CParticleManager::Update()
{
	int num=m_ParticleList.size() ;

	for(int i=0; i<num; i++)
	{
		m_ParticleList[i]->Update() ;

		if(!m_ParticleList[i]->BeLife())
		{
			CParticle *pParticle = m_ParticleList[i] ;
			m_ParticleList.erase(m_ParticleList.begin() + i) ;
			delete pParticle ;

			--i ;
			--num ;
		}
	}
}

void CParticleManager::Render()
{
	const int num=m_ParticleList.size() ;

	for(int i=0; i<num; i++)
		m_ParticleList[i]->Render() ;
}

void CParticleManager::CreateParticle(float fX, float fY, int nNumber)
{
	CParticle *pParticle ;
	int num ;

	if(nNumber==0)
		num = 15 ;
	else if(nNumber==1)
		num = 15 ;

	for(int i=0; i<num; i++)
	{
		if(nNumber==0)
			pParticle = new CParticle_Debris ;
		else if(nNumber==1)
			pParticle = new CParticle_Energy ;
		pParticle->Init() ;
		pParticle->SetPosition(fX, fY) ;

		m_ParticleList.push_back(pParticle) ;
	}
}

void CParticleManager::ParticleClear()
{
	const int num=m_ParticleList.size() ;
	CParticle *pParticle ;

	for(int i=0; i<num; i++)
	{
		pParticle = m_ParticleList[i] ;
		delete pParticle ;
	}

	m_ParticleList.clear() ;
}