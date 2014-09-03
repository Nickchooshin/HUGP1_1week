#include "SampleScene.h"

#include "Keyboard.h"
#include "Mouse.h"
#include "Joystick.h"

#include "Sprite.h"
#include "UISprite.h"
#include "CameraManager.h"
#include "MusicManager.h"

#include "Box.h"

//FMOD::Sound *sound ;

SampleScene::SampleScene() : pBox(NULL)
{
}
SampleScene::~SampleScene()
{
	if(pBox!=NULL)
		delete pBox ;
}

Scene* SampleScene::scene()
{
	Scene *scene = new SampleScene ;

	return scene ;
}

void SampleScene::Init()
{
	g_CameraManager->AddCamera(new CCamera()) ;

	pBox = new CBox ;
	pBox->Init() ;
	pBox->SetPosition(100.0f, 100.0f) ;

	//sound = g_MusicManager->LoadMusic("click_1.mp3", false, false) ;
}

void SampleScene::Destroy()
{
}

void SampleScene::Update(float dt)
{
	g_Keyboard->Update() ;
	g_Mouse->Update() ;
	g_Joystick->Update() ;
	g_MusicManager->Loop() ;

	static float s=1.0f ;

	if(g_Keyboard->IsButtonDown(DIK_W))
		s += 0.1f ;
	if(g_Keyboard->IsButtonDown(DIK_S))
		s -= 0.1f ;
	pBox->SetScale(s) ;

	//g_MusicManager->PlayMusic(sound[0]) ;
}

void SampleScene::Render()
{
	g_CameraManager->CameraRun() ;

	pBox->Render() ;
}