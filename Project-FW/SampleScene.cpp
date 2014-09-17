#include "SampleScene.h"
#include "SceneManager.h"
#include "TitleScene.h"

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

SampleScene::SampleScene() : m_pBackground(NULL),
							 m_pGameover(NULL),
							 m_fGameoverTime(0.0f)
{
}
SampleScene::~SampleScene()
{
	if(m_pBackground!=NULL)
		delete m_pBackground ;
	if(m_pGameover!=NULL)
		delete m_pGameover ;
}

Scene* SampleScene::scene()
{
	Scene *scene = new SampleScene ;

	return scene ;
}

void SampleScene::Init()
{
	g_CameraManager->AddCamera(new CCamera()) ;

	m_pBackground = new CSprite ;
	m_pBackground->Init("Resource/Image/Background.png") ;

	m_pGameover = new CSprite ;
	m_pGameover->Init("Resource/Image/Gameover.png") ;

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

	m_bGameover = !g_Player->BeLife() ;

	if(!m_bGameover)
	{
		g_Player->Update() ;
	}
	else
	{
		m_pGameover->SetPosition(g_Player->GetPositionX(), g_Player->GetPositionY()) ;

		if(m_fGameoverTime<3.0f)
			m_fGameoverTime += dt ;

		if(m_fGameoverTime>=3.0f)
		{
			m_pGameover->SetAlpha(255) ;

			if(g_Keyboard->IsPressDown(DIK_RETURN))
			{
				GameOver() ;
				return ;
			}
		}
		else
		{
			int nAlpha = 255 * (m_fGameoverTime / 3.0f) ;
			m_pGameover->SetAlpha(nAlpha) ;
		}
	}

	g_BoxManager->Update() ;

	g_ParticleManager->Update() ;

	m_pBackground->SetPosition(g_Player->GetPositionX(), g_Player->GetPositionY()) ;

	g_CameraManager->SetPosition(g_Player->GetPositionX(), g_Player->GetPositionY()) ;
}

void SampleScene::Render()
{
	g_CameraManager->CameraRun() ;

	m_pBackground->Render() ;

	if(!m_bGameover)
		g_Player->Render() ;

	g_BoxManager->Render() ;

	g_ParticleManager->Render() ;

	if(m_bGameover)
		m_pGameover->Render() ;
}

void SampleScene::GameOver()
{
	g_BoxManager->Clear() ;

	g_SceneManager->ChangeScene(TitleScene::scene()) ;
}