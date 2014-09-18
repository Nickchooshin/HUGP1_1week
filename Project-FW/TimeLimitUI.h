#pragma once

class CNumberUI ;
class CSprite ;

class CTimeLimitUI
{
private :
	float m_fX, m_fY ;
	float m_fTime ;
	int m_nNum ;
	CNumberUI *m_pNumber[5] ;
	CSprite *m_pDot ;

public :
	CTimeLimitUI() ;
	~CTimeLimitUI() ;

	void Init() ;

	void SetPosition(float fX, float fY) ;
	const bool Timeout() const ;

	void Update() ;

	void Render() ;
private :
	void SetTime() ;
} ;