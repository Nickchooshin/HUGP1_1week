#include "BoxManager.h"
#include "Box.h"
#include "Player.h"
#include "Collision.h"

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

	pBox = new CBox() ;
	pBox->Init() ;
	pBox->SetPosition(320.0f, 280.0f) ;
	m_BoxList.push_back(pBox) ;
}

void CBoxManager::Update()
{
	const int num=m_BoxList.size() ;

	for(int i=0; i<num; i++)
		m_BoxList[i]->Update() ;

	Collision() ;
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
		}
	}
}