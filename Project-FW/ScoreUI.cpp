#include "ScoreUI.h"
#include "NumberUI.h"
#include "Player.h"
#include "Data.h"

CScoreUI::CScoreUI() : m_fX(0.0f), m_fY(0.0f),
					   m_nScore(0), m_nMaxScore(0),
					   m_nNum(0)
{
	for(int i=0; i<10; i++)
		m_pNumber[i] = 0 ;
}
CScoreUI::~CScoreUI()
{
	for(int i=0; i<10; i++)
	{
		if(m_pNumber[i]!=0)
			delete m_pNumber[i] ;
	}
}

void CScoreUI::Init()
{
	for(int i=0; i<10; i++)
	{
		m_pNumber[i] = new CNumberUI ;
		m_pNumber[i]->Init() ;
	}

	m_nMaxScore = g_Data->m_nMaxScore ;

	SetScore() ;
}

void CScoreUI::SetPosition(float fX, float fY)
{
	m_fX = fX ;
	m_fY = fY ;
}

const bool CScoreUI::AchieveAScore() const
{
	if(m_nScore>=m_nMaxScore)
		return true ;

	return false ;
}

void CScoreUI::Update()
{
	unsigned int nScore = g_Player->GetScore() ;
	if(m_nScore!=nScore)
	{
		m_nScore = nScore ;
		SetScore() ;
	}
}

void CScoreUI::Render()
{
	for(int i=0; i<m_nNum; i++)
	{
		m_pNumber[i]->SetPosition(m_fX - (40.0f * i), m_fY) ;
		m_pNumber[i]->Render() ;
	}
}

void CScoreUI::SetScore()
{
	if(m_nScore==0)
	{
		m_pNumber[0]->SetNumber(0) ;
		m_nNum = 1 ;
		return ;
	}

	unsigned int temp=m_nScore ;
	int num ;
	int i=0 ;

	while(temp!=0)
	{
		num = temp % 10 ;
		temp = temp / 10 ;

		m_pNumber[i++]->SetNumber(num) ;
	}

	m_nNum = i ;
}