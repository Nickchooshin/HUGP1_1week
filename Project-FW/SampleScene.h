#pragma once

#include "Scene.h"

class CBox ;

class SampleScene : public Scene
{
private :
	CBox *pBox ;

public :
	static Scene* scene() ;

	SampleScene() ;
	virtual ~SampleScene() ;

	void Init() ;
	void Destroy() ;

	void Update(float dt) ;
	void Render() ;
} ;