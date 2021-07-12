#include "stdafx.h"
#include "UI.h"


CUI::CUI() 
{

}
CUI::CUI(HWND _hWnd, HINSTANCE _hInstance)
{
	this->hWnd = _hWnd;
	this->hInstance = _hInstance;
	hUi = NULL;

	szWindowClass = _T("UI_Class");
	szWindowTitle = _T("UI_Title");
	m_bRegistration = FALSE;

	::GetClientRect(hWnd, &m_rcRect);

	m_pParent = NULL;
}
CUI::~CUI()
{
	if (hUi)
	{
		DestroyWindow(hUi);
	}
}

void CUI::RegisterUI()
{

}

void CUI::MakeUI() 
{

}

void CUI::OnUpdate()
{

}

void CUI::ShowUI()
{
	ShowWindow(hUi, SW_SHOW);
}

void CUI::DestroyUI()
{

}