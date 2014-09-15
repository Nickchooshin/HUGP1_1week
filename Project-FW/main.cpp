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

	WinSystem.WinSet("Bound Box - �� version", WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX, 1024, 768) ;	// WS_THICKFRAME - ������â �ø���/���̱� ũ������ ��������.
	WinSystem.WinMsg() ;
	WinSystem.WinEnd() ;

	return 0 ;
}