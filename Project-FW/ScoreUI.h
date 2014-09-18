#pragma once

class CNumberUI ;

class CScoreUI
{
private :
	float m_fX, m_fY ;
	unsigned int m_nScore, m_nMaxScore ;
	int m_nNum ;
	CNumberUI *m_pNumber[10] ;

public :
	CScoreUI() ;
	~CScoreUI() ;

	void Init() ;

	void SetPosition(float fX, float fY) ;
	const bool AchieveAScore() const ;

	void Update() ;

	void Render() ;
private :
	void SetScore() ;
} ;