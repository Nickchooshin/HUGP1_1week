#include "TimeLimitUI.h"
#include "NumberUI.h"
#include "Sprite.h"
#include "Data.h"
#include "D3dDevice.h"

CTimeLimitUI::CTimeLimitUI() : m_fX(0.0f), m_fY(0.0f),
							   m_fTime(0),
							   m_nNum(NULL),
							   m_pDot(NULL)
{
}
CTimeLimitUI::~CTimeLimitUI()
{
	for(int i=0; i<5; i++)
	{
		if(m_pNumber[i]!=NULL)
			delete m_pNumber[i] ;
	}

	if(m_pDot!=NULL)
		delete m_pDot ;
}

void CTimeLimitUI::Init()
{
	for(int i=0; i<5; i++)
	{
		m_pNumber[i] = new CNumberUI ;
		m_pNumber[i]->Init() ;
	}

	m_pDot = new CSprite ;
	m_pDot->Init("Resource/Image/Dot.png") ;

	m_fTime = g_Data->m_fTimeLimit ;
	SetTime() ;
}

void CTimeLimitUI::SetPosition(float fX, float fY)
{
	m_fX = fX ;
	m_fY = fY ;
}

const bool CTimeLimitUI::Timeout() const
{
	if(m_fTime<=0.0f)
		return true ;

	return false ;
}

void CTimeLimitUI::Update()
{
	m_fTime -= g_D3dDevice->GetTime() ;
	SetTime() ;
}

void CTimeLimitUI::Render()
{
	m_pDot->SetPosition(m_fX, m_fY) ;
	m_pDot->Render() ;

	for(int i=0; i<m_nNum; i++)
	{
		if(i!=0)
			m_pNumber[i]->SetPosition(m_fX - (40.0f * (i-1)) - 25.0f, m_fY) ;
		else
			m_pNumber[i]->SetPosition(m_fX + (40.0f * i) + 25.0f, m_fY) ;
		m_pNumber[i]->Render() ;
	}
}

void CTimeLimitUI::SetTime()
{
	int nTime = (int)(m_fTime * 10.0f) ;
	int num ;
	int i=0 ;

	if(nTime<0)
	{
		m_pNumber[0]->SetNumber(0) ;
		m_pNumber[1]->SetNumber(0) ;
		m_nNum = 2 ;
	}

	while(nTime!=0 || i<2)
	{
		num = nTime % 10 ;
		nTime = nTime / 10 ;

		m_pNumber[i++]->SetNumber(num) ;
	}

	m_nNum = i ;
}