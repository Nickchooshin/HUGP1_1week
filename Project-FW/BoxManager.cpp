#include "BoxManager.h"
#include "Box.h"
#include "Player.h"
#include "Collision.h"
#include "ParticleManager.h"

#include "D3dDevice.h"

CBoxManager::CBoxManager()
{
}
CBoxManager::~CBoxManager()
{
	CBox *pBox ;
	const int num=m_BoxList.size() ;

	for(int i=0; i<num; i++)
	{
		pBox = m_BoxList[i] ;
		delete pBox ;
	}
	m_BoxList.clear() ;
}

void CBoxManager::Init()
{
	CBox *pBox=NULL ;

	/*pBox = new CBox() ;
	pBox->Init() ;
	pBox->SetPosition(320.0f, 280.0f) ;
	m_BoxList.push_back(pBox) ;*/

	const int num=10 ;

	for(int i=0; i<num; i++)
	{
		pBox = new CBox() ;
		pBox->Init() ;
		pBox->SetPosition((rand()%10)*100.0f, (rand()%10)*100.0f) ;
		m_BoxList.push_back(pBox) ;
	}
}

void CBoxManager::Update()
{
	int num=m_BoxList.size() ;

	for(int i=0; i<num; i++)
	{
		if(!m_BoxList[i]->BeLife())
		{
			CBox *pBox = m_BoxList[i] ;
			m_BoxList.erase(m_BoxList.begin() + i) ;
			//
			g_ParticleManager->CreateParticle(pBox->GetPositionX(), pBox->GetPositionY(), 1) ;
			//
			delete pBox ;

			--i ;
			--num ;
			continue ;
		}
		m_BoxList[i]->Update() ;
	}

	Collision() ;

	CreateBox() ;
	DeleteBox() ;
}

void CBoxManager::Render()
{
	const int num=m_BoxList.size() ;

	for(int i=0; i<num; i++)
		m_BoxList[i]->Render() ;
}

void CBoxManager::Collision()
{
	const int num=m_BoxList.size() ;

	CCollision collision ;
	
	float PlayerX = g_Player->GetPositionX() ;
	float PlayerY = g_Player->GetPositionY() ;
	float PlayerR = g_Player->GetScale() ;

	for(int i=0; i<num; i++)
	{
		CBox *pBox = m_BoxList[i] ;
		float BoxX = pBox->GetPositionX() ;
		float BoxY = pBox->GetPositionY() ;
		float BoxR = pBox->GetScale() ;

		bool bCol = collision.CircleCollision(PlayerX, PlayerY, PlayerR*24.0f, BoxX, BoxY, BoxR*24.0f) ;
		if(bCol)
		{
			collision.InelasticCollision(g_Player, pBox) ;
			g_ParticleManager->CreateParticle(g_Player->GetPositionX(), g_Player->GetPositionY(), 0) ;
		}
	}
}

void CBoxManager::CreateBox()
{
	static float t=0.0f ;
	t += g_D3dDevice->GetTime() ;

	if(t>=0.5f)
	{
		const int num = (int)(t/1.0f) ;
		t -= num * 1.0f ;

		if(m_BoxList.size()<50)
		{
			for(int i=0; i<num; i++)
			{
				int length = rand()%10 ;
				int angle = rand()%36 ;

				float x = g_Player->GetPositionX() + (100.0f * length + 500.0f) * cos((angle*10.0f) * D3DX_PI / 180.0f) ;
				float y = g_Player->GetPositionY() + (100.0f * length + 500.0f) * sin((angle*10.0f) * D3DX_PI / 180.0f) ;

				CBox *pBox = new CBox ;
				pBox->Init() ;
				pBox->SetPosition(x, y) ;
				m_BoxList.push_back(pBox) ;
			}
		}
	}
}

void CBoxManager::DeleteBox()
{
	int num=m_BoxList.size() ;

	float PlayerX = g_Player->GetPositionX() ;
	float PlayerY = g_Player->GetPositionY() ;

	for(int i=0; i<num; i++)
	{
		CBox *pBox = m_BoxList[i] ;

		float x = PlayerX - pBox->GetPositionX() ;
		float y = PlayerY - pBox->GetPositionY() ;
		float distance = sqrt((x*x) + (y*y)) ;

		if(distance>3000.0f)
		{
			m_BoxList.erase(m_BoxList.begin() + i) ;
			delete pBox ;

			--i ;
			--num ;
		}
	}
}