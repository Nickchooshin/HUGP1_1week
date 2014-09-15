/*#include <d3d9.h>
#pragma warning( disable : 4996 ) // disable deprecated warning 
#include <strsafe.h>
#pragma warning( default : 4996 ) */

#include "WinSystem.h"
#include "SceneManager.h"
#include "TitleScene.h"

INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR, INT )
{
	CWinSystem WinSystem(hInst) ;

	g_SceneManager->StartScene(TitleScene::scene()) ;

	WinSystem.WinSet("Bound Box - α version", WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX, 1024, 768) ;	// WS_THICKFRAME - 윈도우창 늘리기/줄이기 크기조정 지원안함.
	WinSystem.WinMsg() ;
	WinSystem.WinEnd() ;

	return 0 ;
}