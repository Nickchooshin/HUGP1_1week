#include "BoxManager.h"
#include "Box.h"
#include "Player.h"
#include "Collision.h"
#include "ParticleManager.h"
#include "Data.h"

#include "MusicManager.h"

#include "D3dDevice.h"

CBoxManager::CBoxManager() : m_pCrash(NULL)
{
}
CBoxManager::~CBoxManager()
{
	Clear() ;
}

void CBoxManager::Init()
{
	const int num=10 ;

	for(int i=0; i<num; i++)
		CreateRandomBox() ;
	
	m_pCrash = g_MusicManager->LoadMusic("Resource/Sound/Crash.wav", false, false) ;
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
			g_ParticleManager->CreateParticle(pBox->GetPositionX(), pBox->GetPositionY(), 1) ;
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

void CBoxManager::Clear()
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

void CBoxManager::Collision()
{
	const int num=m_BoxList.size() ;
	bool bCol ;

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

		if(g_Player->BeLife())
		{
			bCol = collision.CircleCollision(PlayerX, PlayerY, PlayerR*24.0f, BoxX, BoxY, BoxR*24.0f) ;
			if(bCol)
			{
				collision.InelasticCollision(g_Player, pBox) ;
				g_ParticleManager->CreateParticle(g_Player->GetPositionX(), g_Player->GetPositionY(), 0) ;
				g_MusicManager->PlayMusic(m_pCrash, 1) ;
			}
		}

		if(g_Data->m_bBoxCollision)
		{
			for(int j=0; j<num; j++)
			{
				if(i==j)
					continue ;

				CBox *pBox2 = m_BoxList[j] ;
				float Box2X = pBox2->GetPositionX() ;
				float Box2Y = pBox2->GetPositionY() ;
				float Box2R = pBox2->GetScale() ;
				bCol = collision.CircleCollision(BoxX, BoxY, BoxR*24.0f, Box2X, Box2Y, Box2R*24.0f) ;
				if(bCol)
				{
					collision.InelasticCollision(pBox, pBox2) ;
					g_ParticleManager->CreateParticle(pBox->GetPositionX(), pBox->GetPositionY(), 0) ;
					g_MusicManager->PlayMusic(m_pCrash, 1) ;
				}
			}
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
				CreateRandomBox() ;
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

void CBoxManager::CreateRandomBox()
{
	int length = rand()%10 ;
	int angle = rand()%36 ;

	float x = g_Player->GetPositionX() + (100.0f * length + 664.0f) * cos((angle*10.0f) * D3DX_PI / 180.0f) ;
	float y = g_Player->GetPositionY() + (100.0f * length + 664.0f) * sin((angle*10.0f) * D3DX_PI / 180.0f) ;

	CBox *pBox = new CBox ;
	pBox->Init() ;
	pBox->SetPosition(x, y) ;

	// 크기 설정
	float Scale = 1.0f - (0.2f * (rand()%4-1)) ;
	Scale *= g_Player->GetScale() ;
	pBox->SetScale(Scale) ;

	// 회전속도 설정
	float Spin = 1.0f - (0.125f * (rand()%5)) ;
	float p = 1.0f - (2.0f * (rand()%2)) ;
	Spin *= Scale * 15.0f * p ;
	pBox->SetFixedSpinSpeed(Spin) ;

	// 리스트에 등록
	m_BoxList.push_back(pBox) ;
}