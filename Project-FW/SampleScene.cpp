#include "SampleScene.h"

#include "Keyboard.h"
#include "Mouse.h"
#include "Joystick.h"

#include "Sprite.h"
#include "UISprite.h"
#include "CameraManager.h"
#include "MusicManager.h"

#include "Data.h"
#include "BoxManager.h"
#include "Player.h"
#include "ParticleManager.h"
//
#include "inelastic_collision.h"

//FMOD::Sound *sound ;

SampleScene::SampleScene()
{
}
SampleScene::~SampleScene()
{
}

Scene* SampleScene::scene()
{
	Scene *scene = new SampleScene ;

	return scene ;
}

void SampleScene::Init()
{
	g_CameraManager->AddCamera(new CCamera()) ;

	g_Data->Init() ;

	g_Player->Init() ;
	g_Player->SetPosition(200.0f, 150.0f) ;

	g_BoxManager->Init() ;
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

	g_Player->Update() ;

	g_BoxManager->Update() ;

	g_ParticleManager->Update() ;

	//g_MusicManager->PlayMusic(sound[0]) ;

	g_CameraManager->SetPosition(g_Player->GetPositionX(), g_Player->GetPositionY()) ;
}

void SampleScene::Render()
{
	g_CameraManager->CameraRun() ;

	g_Player->Render() ;

	g_BoxManager->Render() ;

	g_ParticleManager->Render() ;
}