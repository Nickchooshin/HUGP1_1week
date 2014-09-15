#pragma once

#include "Scene.h"

class CSprite ;

class SampleScene : public Scene
{
private :
	CSprite *m_pBackground ;

public :
	static Scene* scene() ;

	SampleScene() ;
	virtual ~SampleScene() ;

	void Init() ;
	void Destroy() ;

	void Update(float dt) ;
	void Render() ;
} ;