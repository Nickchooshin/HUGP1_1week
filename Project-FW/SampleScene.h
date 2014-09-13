#pragma once

#include "Scene.h"

class SampleScene : public Scene
{
private :

public :
	static Scene* scene() ;

	SampleScene() ;
	virtual ~SampleScene() ;

	void Init() ;
	void Destroy() ;

	void Update(float dt) ;
	void Render() ;
} ;