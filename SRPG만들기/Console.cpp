#include "stdafx.h"
#include "Console.h"

CConsoleManager::CConsoleManager(CFrameWork * pFramework)
{
#ifdef _DEBUG

	#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")

#endif
}

CConsoleManager::~CConsoleManager()
{

}

void CConsoleManager::OnUpdate()
{

}