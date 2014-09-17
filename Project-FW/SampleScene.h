#pragma once

#include "Scene.h"

class CSprite ;

class SampleScene : public Scene
{
private :
	bool m_bGameover ;
	float m_fGameoverTime ;
	CSprite *m_pBackground ;
	CSprite *m_pGameover ;

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