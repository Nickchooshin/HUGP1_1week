#include "Box.h"
#include "Sprite.h"

CBox::CBox()
{
}
CBox::~CBox()
{
}

void CBox::Init()
{
	m_pSprite = new CSprite ;
	m_pSprite->Init("Resource/1.png") ;
}

void CBox::Update()
{
}

void CBox::SetScale(float fScale)
{
	m_pSprite->SetScale(fScale, fScale) ;
}