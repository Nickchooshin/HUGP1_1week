#include "Objects.h"
#include "Sprite.h"

CObjects::CObjects() : m_pSprite(NULL),
					   m_fX(0.0f), m_fY(0.0f)
{
}
CObjects::~CObjects()
{
	if(m_pSprite!=NULL)
		delete m_pSprite ;
}

void CObjects::Update()
{
}

const float CObjects::GetPositionX() const
{
	return m_fX ;
}

const float CObjects::GetPositionY() const
{
	return m_fY ;
}

void CObjects::SetPosition(float fX, float fY)
{
	m_fX = fX ;
	m_fY = fY ;
}

void CObjects::Render() const
{
	m_pSprite->SetPosition(m_fX, m_fY) ;
	m_pSprite->Render() ;
}