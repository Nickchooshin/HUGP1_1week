#pragma once

#include "Scene.h"

class CSprite ;

class TitleScene : public Scene
{
private :
	CSprite *m_pBackground ;
	CSprite *m_pTutorial1, *m_pTutorial2 ;
	CSprite *m_pDeveloper ;
	CSprite *m_pBox1, *m_pBox2 ;

	int m_nCursor ;
	int m_nImageBox ;
	float m_fAngle ;

public :
	static Scene* scene() ;

	TitleScene() ;
	virtual ~TitleScene() ;

	void Init() ;
	void Destroy() ;

	void Update(float dt) ;
	void Render() ;
} ;