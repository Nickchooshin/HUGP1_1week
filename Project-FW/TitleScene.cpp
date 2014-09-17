#include "TitleScene.h"
#include "SceneManager.h"
#include "SampleScene.h"

#include "Keyboard.h"
#include "Mouse.h"
#include "Joystick.h"

#include "Sprite.h"
#include "CameraManager.h"
#include "MusicManager.h"

#include "D3dDevice.h"

TitleScene::TitleScene() : m_pBackground(NULL),
						   m_pTutorial1(NULL), m_pTutorial2(NULL),
						   m_pDeveloper(NULL),
						   m_pBox1(NULL), m_pBox2(NULL),
						   m_nCursor(0),
						   m_nImageBox(0),
						   m_fAngle(0.0f),
						   m_pSoundButton(NULL),
						   m_pBGM(NULL)
{
}
TitleScene::~TitleScene()
{
	if(m_pBackground!=NULL)
		delete m_pBackground ;
	if(m_pTutorial1!=NULL)
		delete m_pTutorial1 ;
	if(m_pTutorial2!=NULL)
		delete m_pTutorial2 ;
	if(m_pDeveloper!=NULL)
		delete m_pDeveloper ;
	if(m_pBox1!=NULL)
		delete m_pBox1 ;
	if(m_pBox2!=NULL)
		delete m_pBox2 ;
}

Scene* TitleScene::scene()
{
	Scene *scene = new TitleScene ;

	return scene ;
}

void TitleScene::Init()
{
	g_CameraManager->AddCamera(new CCamera()) ;

	float fWinWidth = g_D3dDevice->GetWinWidth() ;
	float fWinHeight = g_D3dDevice->GetWinHeight() ;

	m_pBackground = new CSprite ;
	m_pBackground->Init("Resource/Image/Title.png") ;
	m_pBackground->SetPosition(fWinWidth/2.0f, fWinHeight/2.0f) ;

	m_pTutorial1 = new CSprite ;
	m_pTutorial1->Init("Resource/Image/Tutorial1_ImageBox.png") ;
	m_pTutorial1->SetPosition(fWinWidth/2.0f, fWinHeight/2.0f) ;

	m_pTutorial2 = new CSprite ;
	m_pTutorial2->Init("Resource/Image/Tutorial2_ImageBox.png") ;
	m_pTutorial2->SetPosition(fWinWidth/2.0f, fWinHeight/2.0f) ;

	m_pDeveloper = new CSprite ;
	m_pDeveloper->Init("Resource/Image/Developer_ImageBox.png") ;
	m_pDeveloper->SetPosition(fWinWidth/2.0f, fWinHeight/2.0f) ;

	m_pBox1 = new CSprite() ;
	m_pBox1->Init("Resource/Image/Box.png") ;
	m_pBox1->SetRGB(157, 223, 255) ;

	m_pBox2 = new CSprite() ;
	m_pBox2->Init("Resource/Image/Box.png") ;
	m_pBox2->SetRGB(255, 161, 161) ;

	m_pSoundButton = g_MusicManager->LoadMusic("Resource/Sound/es040.wav", false, false) ;
	m_pBGM = g_MusicManager->LoadMusic("Resource/Sound/Raina-Milk_in_Veins.mp3", true) ;
	//m_pBGM = g_MusicManager->LoadMusic("Resource/Sound/Flutterwonder_UP_NOVOX.mp3", true) ;
	g_MusicManager->PlayMusic(m_pBGM, 0) ;
}

void TitleScene::Destroy()
{
}

void TitleScene::Update(float dt)
{
	g_Keyboard->Update() ;
	g_Mouse->Update() ;
	g_Joystick->Update() ;
	g_MusicManager->Loop() ;

	if(m_nImageBox==0 && g_Keyboard->IsPressDown(DIK_UP))
	{
		g_MusicManager->StopMusic(1) ;
		g_MusicManager->PlayMusic(m_pSoundButton, 1) ;

		--m_nCursor ;
		if(m_nCursor<0)
			m_nCursor = 2 ;
	}
	if(m_nImageBox==0 && g_Keyboard->IsPressDown(DIK_DOWN))
	{
		g_MusicManager->StopMusic(1) ;
		g_MusicManager->PlayMusic(m_pSoundButton, 1) ;

		++m_nCursor ;
		if(m_nCursor>2)
			m_nCursor = 0 ;
	}
	if(g_Keyboard->IsPressDown(DIK_RETURN))
	{
		g_MusicManager->StopMusic(1) ;
		g_MusicManager->PlayMusic(m_pSoundButton, 1) ;

		if(m_nCursor==0)
			g_SceneManager->ChangeScene(SampleScene::scene()) ;
		else if(m_nCursor==1)
			m_nImageBox = ++m_nImageBox % 3 ;
		else
			m_nImageBox = ++m_nImageBox % 2 ;
	}

	float x, y ;
	float width ;

	switch(m_nCursor)
	{
	case 0 :
		x = 502.0f ;
		y = 397.5f ;
		width = 290.0f / 2.0f ;
		break ;

	case 1 :
		x = 513.0f ;
		y = 515.0f ;
		width = 450.0f / 2.0f ;
		break ;

	case 2 :
		x = 513.0f ;
		y = 636.0f ;
		width = 544.0f / 2.0f ;
		break ;
	}

	y = g_D3dDevice->GetWinHeight() - y ;
	width += 48.0f ;
	m_pBox1->SetPosition(x-width, y) ;
	m_pBox2->SetPosition(x+width, y) ;
	
	m_fAngle += 3.0f * g_D3dDevice->GetMoveTime() ;
	if(m_fAngle>360.0f)
		m_fAngle -= 360.0f ;
	m_pBox1->SetAngle(m_fAngle) ;
	m_pBox2->SetAngle(-m_fAngle) ;
}

void TitleScene::Render()
{
	g_CameraManager->CameraRun() ;

	m_pBackground->Render() ;
	
	m_pBox1->Render() ;
	m_pBox2->Render() ;

	if(m_nImageBox!=0)
	{
		if(m_nCursor==1)
		{
			if(m_nImageBox==1)
				m_pTutorial1->Render() ;
			else if(m_nImageBox==2)
				m_pTutorial2->Render() ;
		}
		else if(m_nCursor==2)
		{
			if(m_nImageBox==1)
				m_pDeveloper->Render() ;
		}
	}
}