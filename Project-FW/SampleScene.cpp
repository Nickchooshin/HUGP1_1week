#include "SampleScene.h"

#include "Keyboard.h"
#include "Mouse.h"
#include "Joystick.h"

#include "Sprite.h"
#include "UISprite.h"
#include "CameraManager.h"
#include "MusicManager.h"

#include "BoxManager.h"
#include "Player.h"
#include "CollisionManager.h"
#include "Sprite.h"
//
#include "inelastic_collision.h"

//FMOD::Sound *sound ;

SampleScene::SampleScene() : //m_pPlayer(NULL),
							 m_pBackground(NULL)
{
}
SampleScene::~SampleScene()
{
	/*if(m_pPlayer!=NULL)
		delete m_pPlayer ;*/
	if(m_pBackground!=NULL)
		delete m_pBackground ;
}

Scene* SampleScene::scene()
{
	Scene *scene = new SampleScene ;

	return scene ;
}

void SampleScene::Init()
{
	g_CameraManager->AddCamera(new CCamera()) ;

	/*m_pPlayer = new CPlayer ;
	m_pPlayer->Init() ;
	m_pPlayer->SetPosition(200.0f, 150.0f) ;*/
	g_Player->Init() ;
	g_Player->SetPosition(200.0f, 150.0f) ;

	//sound = g_MusicManager->LoadMusic("click_1.mp3", false, false) ;

	//inelastic_collision(10, 20, 10, -2, 0.5) ;

	//m_pBackground = new CSprite ;
	//m_pBackground->Init("Resource/background.png") ;

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

	//m_pPlayer->Update() ;
	g_Player->Update() ;

	g_BoxManager->Update() ;

	//g_MusicManager->PlayMusic(sound[0]) ;
	
	//float a = GetAngle(m_pBox->GetPositionX(), m_pBox->GetPositionY(), m_pPlayer->GetPositionX(), m_pPlayer->GetPositionY()) ;
	//float b = GetAngle2(a, 90.0f + 45.0f) ;
}

void SampleScene::Render()
{
	g_CameraManager->CameraRun() ;

	//m_pPlayer->Render() ;
	g_Player->Render() ;

	g_BoxManager->Render() ;

	//m_pBackground->Render() ;
}