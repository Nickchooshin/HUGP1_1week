#pragma once

class CSprite ;

class CObjects
{
protected :
	CSprite *m_pSprite ;
	float m_fX, m_fY ;

public :
	CObjects() ;
	virtual ~CObjects() ;

	virtual void Init() = 0 ;

	virtual void Update() ;

	const float GetPositionX() const ;
	const float GetPositionY() const ;

	void SetPosition(float fX, float fY) ;

	virtual void Render() const ;
} ;