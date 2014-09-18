#pragma once

class CSprite ;

class CNumberUI
{
private :
	float m_fX, m_fY ;
	int m_nNumber ;
	CSprite *m_pSprite ;

public :
	CNumberUI() ;
	~CNumberUI() ;

	void Init() ;
	
	void SetPosition(float fX, float fY) ;
	void SetNumber(int nNum) ;

	void Render() ;
} ;