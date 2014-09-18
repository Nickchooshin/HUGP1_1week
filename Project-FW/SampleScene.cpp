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
#include "ScoreUI.h"
#include "TimeLimitUI.h"

SampleScene::SampleScene() : m_bScore(false), m_bTime(false),
							 m_bGameover(false), m_bGameclear(false),
							 m_fSpriteTime(0.0f),
							 m_pBackground(NULL),
							 m_pGameover(NULL), m_pGameclear(),
							 m_pScore(NULL),
							 m_pTimeLimit(NULL)
{
}
SampleScene::~SampleScene()
{
	if(m_pBackground!=NULL)
		delete m_pBackground ;
	if(m_pGameover!=NULL)
		delete m_pGameover ;
	if(m_pGameclear!=NULL)
		delete m_pGameclear ;
	if(m_pScore!=NULL)
		delete m_pScore ;
	if(m_pTimeLimit!=NULL)
		delete m_pTimeLimit ;
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

	m_bScore = g_Data->m_bScore ;
	m_bTime = g_Data->m_bTime ;

	m_pBackground = new CSprite ;
	m_pBackground->Init("Resource/Image/Background.png") ;

	m_pGameover = new CSprite ;
	m_pGameover->Init("Resource/Image/Gameover.png") ;

	m_pGameclear = new CSprite ;
	m_pGameclear->Init("Resource/Image/Gameclear.png") ;

	if(m_bScore)
	{
		m_pScore = new CScoreUI ;
		m_pScore->Init() ;
	}

	if(m_bTime)
	{
		m_pTimeLimit = new CTimeLimitUI ;
		m_pTimeLimit->Init() ;
	}

	g_Player->Init() ;
	g_Player->SetPosition(0.0f, 0.0f) ;

	g_BoxManager->Init() ;

	g_CameraManager->SetPosition(g_Player->GetPositionX(), g_Player->GetPositionY()) ;
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

	// GameOver üũ
	m_bGameover = !g_Player->BeLife() ;
	if(m_bTime)
		m_bGameover = m_bGameover | m_pTimeLimit->Timeout() ;

	// GameClear üũ
	if(m_bScore)
		m_bGameclear = m_pScore->AchieveAScore() ;

	// Update
	if(!m_bGameover && !m_bGameclear)
		g_Player->Update() ;
	else
		g_Player->Gameover() ;

	g_BoxManager->Update() ;

	g_ParticleManager->Update() ;

	if(m_bScore && (!m_bGameover && !m_bGameclear))
		m_pScore->Update() ;
	if(m_bTime && (!m_bGameover && !m_bGameclear))
		m_pTimeLimit->Update() ;

	//

	float PlayerX = g_Player->GetPositionX() ;
	float PlayerY = g_Player->GetPositionY() ;
	float CameraX = g_CameraManager->GetPosition().x ;
	float CameraY = g_CameraManager->GetPosition().y ;
	float width = 320.0f / 2.0f ;
	float height = 240.0f / 2.0f ;

	if(PlayerX>CameraX + width)
		CameraX += PlayerX - (CameraX + width) ;
	else if(PlayerX<CameraX - width)
		CameraX += PlayerX - (CameraX - width) ;
	
	if(PlayerY>CameraY + height)
		CameraY += PlayerY - (CameraY + height) ;
	else if(PlayerY<CameraY - height)
		CameraY += PlayerY - (CameraY - height) ;

	g_CameraManager->SetPosition(CameraX, CameraY) ;
	m_pBackground->SetPosition(CameraX, CameraY) ;

	if(m_bGameover || m_bGameclear)
	{
		m_pGameover->SetPosition(CameraX, CameraY) ;
		m_pGameclear->SetPosition(CameraX, CameraY) ;

		if(m_fSpriteTime<3.0f)
			m_fSpriteTime += dt ;

		if(m_fSpriteTime>=3.0f)
		{
			m_pGameover->SetAlpha(255) ;
			m_pGameclear->SetAlpha(255) ;

			if(g_Keyboard->IsPressDown(DIK_RETURN))
			{
				GameOver() ;
				return ;
			}
		}
		else
		{
			int nAlpha = 255 * (m_fSpriteTime / 3.0f) ;
			m_pGameover->SetAlpha(nAlpha) ;
			m_pGameclear->SetAlpha(nAlpha) ;
		}
	}

	if(m_bScore)
		m_pScore->SetPosition(CameraX + 462.0f, CameraY + 325.0f) ;
	if(m_bTime)
		m_pTimeLimit->SetPosition(CameraX, CameraY + 325.0f) ;
}

void SampleScene::Render()
{
	g_CameraManager->CameraRun() ;

	m_pBackground->Render() ;

	if(!m_bGameover && !m_bGameclear)
		g_Player->Render() ;

	g_BoxManager->Render() ;

	g_ParticleManager->Render() ;

	if(m_bScore)
		m_pScore->Render() ;
	if(m_bTime)
		m_pTimeLimit->Render() ;

	if(m_bGameover)
		m_pGameover->Render() ;
	if(m_bGameclear)
		m_pGameclear->Render() ;
}

void SampleScene::GameOver()
{
	g_BoxManager->Clear() ;
	g_ParticleManager->ParticleClear() ;

	g_SceneManager->ChangeScene(TitleScene::scene()) ;
}