#pragma once

#include "Scene.h"

class CSprite ;
class CScoreUI ;
class CTimeLimitUI ;

class SampleScene : public Scene
{
private :
	bool m_bScore, m_bTime ;
	bool m_bGameover, m_bGameclear ;
	float m_fSpriteTime ;
	CSprite *m_pBackground ;
	CSprite *m_pGameover, *m_pGameclear ;
	CScoreUI *m_pScore ;
	CTimeLimitUI *m_pTimeLimit ;

public :
	static Scene* scene() ;

	SampleScene() ;
	virtual ~SampleScene() ;

	void Init() ;
	void Destroy() ;

	void Update(float dt) ;
	void Render() ;
private :
	void GameOver() ;
} ;