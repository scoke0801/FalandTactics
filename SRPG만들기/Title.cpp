#include "stdafx.h"
#include "Title.h"

CTitleScene::CTitleScene(CFrameWork * framework, HWND hWnd)
	: CScene(framework, hWnd)
{
	//CImage image;
	//HBITMAP hBmp;

	m_font = CreateFont(30, 10, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0,
		VARIABLE_PITCH | FF_ROMAN, _T("굴림"));

	LoadBackground(_T("resource/map/title_background.BMP"));
	m_pFrameWork->GetSound()->AddStream(("resource/sound/BGM/TITLE_BGM.mp3"), Sound_Name::BGM_TITLE);

	UI_stageSelect = NULL;

	//CreateButton();
	/*SendMessage(m_buttonSelectStage, WM_SETFONT, (WPARAM)m_font, MAKELPARAM(TRUE, 0));
	SendMessage(m_buttonLoadStage, WM_SETFONT, (WPARAM)m_font, MAKELPARAM(TRUE, 0));
	SendMessage(m_buttonEndGame, WM_SETFONT, (WPARAM)m_font, MAKELPARAM(TRUE, 0));*/
	
	UI_Login = CUI_Login::GetInstance(m_pFrameWork->GetHWND(),
		m_pFrameWork->GetHINSTANCE());
	UI_Login->SetParent(this);
	UI_Login->SetPos(POINT{ m_rcApp.right / 2 - 150 , m_rcApp.bottom / 2 - 100 });
	
	/*if (CProfile::GetInstance() == NULL)
		UI_Login->MakeUI();
	else*/
		CreateButton();
	CUI_StageSelect::GetInstance(m_pFrameWork->GetHWND(), m_pFrameWork->GetHINSTANCE());
	CUI_StageSelect::GetInstance()->SetFraemWork(m_pFrameWork);
	CUI_StageSelect::GetInstance()->SetCurrentStage(CScene::CurrentScene::Title);
}
CTitleScene::~CTitleScene()
{
}

void CTitleScene::OnUpdate(float timeElapsed)
{
	//if (UI_stageSelect != NULL && m_buttonSelectStage != NULL)
	//{
	//	if (UI_stageSelect->UpdateUI())
	//	{
	//		m_buttonSelectStage = CreateWindow(_T("button"), _T("스테이지 선택"),
	//			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
	//			m_rcApp.right / 8 * 1, m_rcApp.bottom - 75, m_rcApp.right / 4 * 1, 75,
	//			m_hWnd, (HMENU)IDC_BUTTON_SelectStage, m_pFrameWork->GetHINSTANCE(), NULL);
	//
	//		m_buttonLoadStage = CreateWindow(_T("button"), _T("맵 불러오기"),
	//			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
	//			m_rcApp.right / 8 * 3, m_rcApp.bottom - 75, m_rcApp.right / 4 * 1, 75,
	//			m_hWnd, (HMENU)IDC_BUTTON_LoadStage, m_pFrameWork->GetHINSTANCE(), NULL);
	//
	//		/*CreateWindow(_T("button"), _T("튜토리얼"),
	//			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
	//			m_rcApp.left + 600, m_rcApp.bottom - 100, 150, 50,
	//			hWnd, (HMENU)NULL, m_pFrameWork->GetHINSTANCE(), NULL);*/
	//
	//		m_buttonEndGame = CreateWindow(_T("button"), _T("게임 종료"),
	//			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
	//			m_rcApp.right / 8 * 5, m_rcApp.bottom - 75, m_rcApp.right / 4 * 1, 75,
	//			m_hWnd, (HMENU)IDC_BUTTON_EndGame, m_pFrameWork->GetHINSTANCE(), NULL);
	//
	//		SendMessage(m_buttonSelectStage, WM_SETFONT, (WPARAM)m_font, MAKELPARAM(TRUE, 0));
	//		SendMessage(m_buttonLoadStage, WM_SETFONT, (WPARAM)m_font, MAKELPARAM(TRUE, 0));
	//		SendMessage(m_buttonEndGame, WM_SETFONT, (WPARAM)m_font, MAKELPARAM(TRUE, 0));
	//	}
	//}
}
void CTitleScene::OnDraw(HDC hdc)
{
	m_background.StretchBlt(hdc
		,m_rcApp.left, m_rcApp.top, m_rcApp.right, m_rcApp.bottom
		,0,0, m_background.GetWidth(), m_background.GetHeight()
		);
}

void CTitleScene::LoadBackground(LPTSTR szPath)
{					
	m_background.Load(szPath);
}

void CTitleScene::PlaySound()
{
	m_pFrameWork->GetSound()->PlayBgm(Sound_Name::BGM_TITLE);
}
void CTitleScene::CreateButton()
{
	CImage image;
	HBITMAP hBmp;

	m_buttonSelectStage = CreateWindow(_T("button"), _T("스테이지 선택"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP,
		m_rcApp.right / 8 * 1, m_rcApp.bottom - 75, m_rcApp.right / 4 * 1, 75,
		m_hWnd, (HMENU)IDC_BUTTON_SelectStage, m_pFrameWork->GetHINSTANCE(), NULL);

	image.Load(_T("resource/button/SelectStage.bmp"));
	hBmp = image.Detach();
	SendMessage(m_buttonSelectStage, BM_SETIMAGE, 0, (LPARAM)hBmp);

	m_buttonLoadStage = CreateWindow(_T("button"), _T("맵 불러오기"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP,
		m_rcApp.right / 8 * 3, m_rcApp.bottom - 75, m_rcApp.right / 4 * 1, 75,
		m_hWnd, (HMENU)IDC_BUTTON_LoadStage, m_pFrameWork->GetHINSTANCE(), NULL);

	image.Load(_T("resource/button/LoadStage.bmp"));
	hBmp = image.Detach();
	SendMessage(m_buttonLoadStage, BM_SETIMAGE, 0, (LPARAM)hBmp);

	m_buttonEndGame = CreateWindow(_T("button"), _T("게임 종료"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP,
		m_rcApp.right / 8 * 5, m_rcApp.bottom - 75, m_rcApp.right / 4 * 1, 75,
		m_hWnd, (HMENU)IDC_BUTTON_EndGame, m_pFrameWork->GetHINSTANCE(), NULL);

	image.Load(_T("resource/button/EndGame.bmp"));
	hBmp = image.Detach();
	SendMessage(m_buttonEndGame, BM_SETIMAGE, 0, (LPARAM)hBmp);
}
BOOL CTitleScene::OnProcessingKeyboardMessage(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
	case VK_F1:
		DestroyWindow(m_buttonSelectStage);
		DestroyWindow(m_buttonLoadStage);
		DestroyWindow(m_buttonEndGame);

		m_pFrameWork->ChangeScene(CScene::CurrentScene::Stage1);
		return TRUE;
	case VK_F2:
		DestroyWindow(m_buttonSelectStage);
		DestroyWindow(m_buttonLoadStage);
		DestroyWindow(m_buttonEndGame);

		m_pFrameWork->ChangeScene(CScene::CurrentScene::Stage2);
		return TRUE;
	case VK_F3:
		DestroyWindow(m_buttonSelectStage);
		DestroyWindow(m_buttonLoadStage);
		DestroyWindow(m_buttonEndGame);

		m_pFrameWork->ChangeScene(CScene::CurrentScene::Stage3);
		return TRUE;
	case VK_F4:
		DestroyWindow(m_buttonSelectStage);
		DestroyWindow(m_buttonLoadStage);
		DestroyWindow(m_buttonEndGame);

		m_pFrameWork->ChangeScene(CScene::CurrentScene::Stage4);
		return TRUE;
	case VK_F5:
		DestroyWindow(m_buttonSelectStage);
		DestroyWindow(m_buttonLoadStage);
		DestroyWindow(m_buttonEndGame);

		m_pFrameWork->ChangeScene(CScene::CurrentScene::Stage5);
		return TRUE;
	case VK_F6:
		DestroyWindow(m_buttonSelectStage);
		DestroyWindow(m_buttonLoadStage);
		DestroyWindow(m_buttonEndGame);

		m_pFrameWork->ChangeScene(CScene::CurrentScene::Stage6);
		return TRUE;
	}
	return FALSE;
}
BOOL CTitleScene::OnProcessingMouseMessage(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	switch (iMsg)
	{
	case WM_LBUTTONDOWN:
		return TRUE;

	case WM_RBUTTONDOWN:
		return TRUE;
	}
	return FALSE;
}
BOOL CTitleScene::OnProcessingWindowMessage(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	switch (iMsg)
	{
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON_SelectStage:
			UI_stageSelect = NULL;

			UI_stageSelect = CUI_StageSelect::GetInstance(m_pFrameWork->GetHWND(), m_pFrameWork->GetHINSTANCE());
			UI_stageSelect->SetFraemWork(m_pFrameWork);
			UI_stageSelect->SetButton(&m_buttonSelectStage, &m_buttonLoadStage, &m_buttonEndGame);

			DestroyWindow(m_buttonSelectStage);
			DestroyWindow(m_buttonLoadStage);
			DestroyWindow(m_buttonEndGame);
			UI_stageSelect->MakeUI();
			
			//UI_stageSelect->DestroyUI();
			//m_pFrameWork->ChangeScene(CScene::CurrentScene::Stage1);
			
		//	UI_stageSelect->SetRect();
			return TRUE;
		case IDC_BUTTON_LoadStage:
			/*DestroyWindow(m_buttonSelectStage);
			DestroyWindow(m_buttonLoadStage);
			DestroyWindow(m_buttonEndGame);*/

			if (m_pFrameWork->LoadScene())
			{
				DestroyWindow(m_buttonSelectStage);
				DestroyWindow(m_buttonLoadStage);
				DestroyWindow(m_buttonEndGame);
			}
			return TRUE;
		case IDC_BUTTON_EndGame:
			PostQuitMessage(0);
			return TRUE;

		}
		break;
	case WM_PAINT:
		break;
	}
	return FALSE;
}

