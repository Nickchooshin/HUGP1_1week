#pragma once

#include "Scene.h"

//class CPlayer ;
class CSprite ;

class SampleScene : public Scene
{
private :
	//CPlayer *m_pPlayer ;
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