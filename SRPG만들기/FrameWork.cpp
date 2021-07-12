#include "stdafx.h"
#include "FrameWork.h"

#include "Title.h"
#include "GameOver.h"
#include "stage1.h"
#include "Stage2.h"
#include "Stage3.h"
#include "Stage4.h"
#include "Stage5.h"
#include "Stage6.h"
#include "StageUser.h"

CFrameWork::CFrameWork()
{
	m_hWnd = NULL;
	m_hInstance = NULL;

	m_pSound = new CSoundManager();

	m_hDC = NULL;
	m_bufferBmp = NULL;
	m_hBrush = NULL;
	m_hPen = NULL;

	m_pCurScene = NULL;
	::SetRect(&m_rcClient, 0, 0, 0, 0);
	
	memset(m_szCurrentDirectory, 0, 256);
	GetCurrentDirectory(256, m_szCurrentDirectory);
	//lstrcpy(m_captionTitle, MAKEINTRESOURCE(IDS_APP_TITLE));
	LoadString(m_hInstance, IDS_APP_TITLE, m_captionTitle, TITLE_LENGTH);
#if defined(SHOW_CAPTIONFPS)
	lstrcat(m_captionTitle, TEXT(" ("));
#endif
	m_titleLength = lstrlen(m_captionTitle);
	SetWindowText(m_hWnd, m_captionTitle);

	srand((unsigned int)time(NULL));

}

CFrameWork::~CFrameWork()
{
	OnDestroy();
}

BOOL CFrameWork::LoadScene()
{
	OPENFILENAME OFN;
	TCHAR lpstrFile[100] = _T("");
	static TCHAR szMap[100], szUnit[100];
	TCHAR filter[] = _T("텍스트 문서(*.txt)\0*.txt\0모든파일\0.* \0");
	bool bRead[2];

	memset(&OFN, 0, sizeof(OPENFILENAME));
	OFN.lStructSize = sizeof(OPENFILENAME);
	OFN.hwndOwner = m_hWnd;
	OFN.lpstrFilter = filter;
	OFN.lpstrFile = lpstrFile;
	OFN.nMaxFile = 100;
	OFN.lpstrInitialDir = _T(".");

	MessageBox(m_hWnd, _T("맵 파일을 열어주세요"), _T("알림"), MB_OK);
	if (GetOpenFileName(&OFN) != 0)
	{
		_stprintf(szMap, _T("%s"), OFN.lpstrFile);
		MessageBox(m_hWnd, _T("유닛 파일도 열어주세요"), _T("열기 선택"), MB_OK);
		bRead[0] = TRUE;
	}
	if (GetOpenFileName(&OFN) != 0)
	{
		_stprintf(szUnit, _T("%s"), OFN.lpstrFile);
		bRead[1] = TRUE;
	}
	if (bRead[0] && bRead[1])
	{
		SetCurrentDirectory(m_szCurrentDirectory);
		ChangeScene(szMap, szUnit);
		return TRUE;
	}
	return FALSE;
}
BOOL CFrameWork::OnCreate(HWND hWnd, HINSTANCE hInstance)
{
	m_hWnd			= hWnd;
	m_hInstance		= hInstance;
	::GetClientRect(m_hWnd, &m_rcClient);
	
	// 타이머 초기화
	m_lastUpdateTime = std::chrono::system_clock::now();
	m_currentTime = std::chrono::system_clock::now();
	m_fps = 0;

	CreateBuffer();
	RegistScene();

	m_pCurScene->PlaySound();

	if(!m_hWnd)
		return FALSE;
	return TRUE;
}
void CFrameWork::OnDraw(HDC hdc)
{
	m_pCurScene->OnDraw(m_hDC);
	
	::BitBlt(hdc, m_rcClient.left , m_rcClient.top , m_rcClient.right, m_rcClient.bottom,
		m_hDC, 0, 0, SRCCOPY);
}
void CFrameWork::PreUpdate()
{
	// Get tick
	m_timeElapsed = std::chrono::system_clock::now() - m_currentTime;//현재시간과 이전시간을 비교해서
	m_dLag = 0.0;
	if (m_timeElapsed.count() > MAX_FPS)				//지정된 시간이 흘렀다면
	{
		m_currentTime = std::chrono::system_clock::now();//현재시간 갱신

		if (m_timeElapsed.count() > 0.0)		
			m_fps = 1.0 / m_timeElapsed.count();	
	
		//게임 시간이 늦어진 경우 이를 따라잡을 때 까지 업데이트 시킵니다.
		//->
		m_dLag += m_timeElapsed.count();
		for (int i = 0;  m_dLag > MAX_FPS && i < MAX_LOOP_TIME; ++i)
		{
			OnUpdate(m_timeElapsed.count());
			m_dLag -= MAX_FPS;
		}
		/*while (m_dLag > MAX_FPS)
		{
			OnUpdate(m_timeElapsed.count());
			m_dLag -= MAX_FPS;
		}*/
	}
	// 최대 FPS 미만의 시간이 경과하면 진행 생략(Frame Per Second)
	else 
		return;

	//업데이트 관련
	//OnUpdate(m_timeElapsed.count());
	
	//렌더링 관련(OnDraw)
	CreateBuffer();
	InvalidateRect(m_hWnd, &m_rcClient, FALSE);

	//타이틀 바(캡션) 관련
#if defined(SHOW_CAPTIONFPS)

	m_updateElapsed = std::chrono::system_clock::now() - m_lastUpdateTime;
	if (m_updateElapsed.count() > MAX_UPDATE_FPS)
		m_lastUpdateTime = std::chrono::system_clock::now();
	else return;

	_itow_s(m_fps + 0.1f, m_captionTitle + m_titleLength, TITLE_LENGTH - m_titleLength, 10);
	wcscat_s(m_captionTitle + m_titleLength, TITLE_LENGTH - m_titleLength, TEXT(" FPS)"));
	SetWindowText(m_hWnd, m_captionTitle);
#endif
}

void CFrameWork::RegistScene()
{
	m_mapScene[CScene::CurrentScene::Title] = new CTitleScene(this, m_hWnd);
	//m_mapScene[CScene::CurrentScene::GameLose] = new CGameOverScene(this, m_hWnd, CScene::CurrentScene::GameLose);
	//m_mapScene[CScene::CurrentScene::GameWin] = new CGameOverScene(this, m_hWnd, CScene::CurrentScene::GameWin);
	//m_mapScene[CScene::CurrentScene::Stage1] = new CStage1(this, m_hWnd, CScene::CurrentScene::Stage1);
	//m_mapScene[CScene::CurrentScene::Stage2] = new CStage2(this, m_hWnd, CScene::CurrentScene::Stage2);
	m_pCurScene = m_mapScene[CScene::CurrentScene::Title];
}
void CFrameWork::ChangeScene(CScene::CurrentScene tag)
{
	m_mapScene.clear();
	for (m_iter = m_mapScene.begin(); m_iter != m_mapScene.end();)
	{
		//delete(m_iter);
		m_iter = m_mapScene.erase(m_iter);
	}
	m_mapScene.clear();
	switch (tag)
	{
	case CScene::CurrentScene::Stage1:
		m_mapScene[tag] = new CStage1(this, m_hWnd, CScene::CurrentScene::Stage1);
		break;
	case CScene::CurrentScene::Stage2:
		m_mapScene[tag] = new CStage2(this, m_hWnd, CScene::CurrentScene::Stage2);
		break;
	case CScene::CurrentScene::Stage3:
		m_mapScene[tag] = new CStage3(this, m_hWnd, CScene::CurrentScene::Stage3);
		break;
	case CScene::CurrentScene::Stage4:
		m_mapScene[tag] = new CStage4(this, m_hWnd, CScene::CurrentScene::Stage4);
		break;
	case CScene::CurrentScene::Stage5:
		m_mapScene[tag] = new CStage5(this, m_hWnd, CScene::CurrentScene::Stage5);
		break;
	case CScene::CurrentScene::Stage6:
		m_mapScene[tag] = new CStage6(this, m_hWnd, CScene::CurrentScene::Stage6);
		break;
	case CScene::CurrentScene::GameWin:
		m_mapScene[tag] = new CGameOverScene(this, m_hWnd, CScene::CurrentScene::GameWin);
		break;
	case CScene::CurrentScene::GameLose:
		m_mapScene[tag] = new CGameOverScene(this, m_hWnd, CScene::CurrentScene::GameLose);
		break;
	case CScene::CurrentScene::Title:
		m_mapScene[tag] = new CTitleScene(this, m_hWnd);
		break;
	}
	
	m_pCurScene = m_mapScene[tag];
	m_pCurScene->PlaySound();
	/*m_iter = m_mapScene.find(tag);
	if (m_iter != m_mapScene.end())
	{
		m_pCurScene = m_iter->second;
		m_pCurScene->PlaySound();
	}
	else
		assert(m_iter == m_mapScene.end());*/
}
void CFrameWork::ChangeScene(TCHAR szMap[100], TCHAR szUnit[100])
{
	m_mapScene.clear();

	m_mapScene[CScene::CurrentScene::UserStage] = new CStageUser(this, m_hWnd, CScene::CurrentScene::UserStage, szMap, szUnit);
	m_pCurScene = m_mapScene[CScene::CurrentScene::UserStage];
	m_pCurScene->PlaySound();
}
void CFrameWork::OnUpdate(float timeElapsed)
{
	m_pCurScene->OnUpdate(timeElapsed);
	m_pSound->OnUpdate();
}
BOOL CFrameWork::OnDestroy()
{
	if (m_bufferBmp)
		::DeleteObject(m_bufferBmp);

	::SelectObject(m_hDC, NULL);
	if (m_hDC)
		::DeleteDC(m_hDC);
	
	//동적할당한 Scene객체들을 해제해줍니다.
	m_mapScene.clear();

	//::MessageBox(NULL, _T("CFrameWork::OnDestory()호출 확인"), _T("프로그램 종료"), MB_OK);
	return FALSE;
}
void CFrameWork::CreateBuffer()
{
	if (m_hDC)			//기존에 디바이스 컨텍스트가 생성되어 있다면 초기화합니다.
	{
		::SelectObject(m_hDC, NULL);	
		::DeleteDC(m_hDC);				
	}

	if (m_bufferBmp)	//기존에 버퍼가 생성되어 있다면 초기화합니다.
	{
		::DeleteObject(m_bufferBmp);	
	}

	HDC hdc = ::GetDC(m_hWnd);
	m_hDC = ::CreateCompatibleDC(hdc);
	m_bufferBmp = ::CreateCompatibleBitmap(hdc, m_rcClient.right, m_rcClient.bottom);
	::SelectObject(m_hDC, m_bufferBmp);
	::FillRect(m_hDC, &m_rcClient, (HBRUSH)GetStockObject(WHITE_BRUSH));
	ReleaseDC(m_hWnd, hdc);
}
void CFrameWork::OnProcessingKeyboardMessage(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	if (m_pCurScene->OnProcessingKeyboardMessage(hWnd, iMsg, wParam, lParam))
		return;
	//switch (iMsg)
	//{
	//case WM_KEYDOWN:
	//	//::MessageBox(m_hWnd, _T("-키 입력 확인-"), _T("키입력"), MB_OK);
	//	break;
	//}
	switch (wParam)
	{
	/*case VK_F1:
		ChangeScene(CScene::CurrentScene::GameWin);
		return;
	case VK_F2:
		ChangeScene(CScene::CurrentScene::GameLose);
		return;*/
	/*case VK_F3:
		ChangeScene(CScene::CurrentScene::Stage1);
		return;
	case VK_F5:
		ChangeScene(CScene::CurrentScene::Stage2);
		return;
	case '0':
		LoadScene();
		return;*/
	}
}
void CFrameWork::OnProcessingMouseMessage(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	if (m_pCurScene->OnProcessingMouseMessage(hWnd, iMsg, wParam, lParam))
		return;
	/*switch (iMsg)
	{
	case WM_MOUSEWHEEL:
		::MessageBox(m_hWnd, _T("-마우스 오른쪽 더블클릭 확인-"), _T("마우스 오른쪽 더블클릭"), MB_OK);
		break;
	case WM_LBUTTONDOWN:
		::MessageBox(m_hWnd, _T("-마우스 왼쪽 클릭 확인-"), _T("마우스 왼쪽 클릭"), MB_OK);
		break;
	case WM_RBUTTONDOWN:
		::MessageBox(m_hWnd, _T("-마우스 오른쪽 클릭 확인-"), _T("마우스 오른쪽 클릭"), MB_OK);
		break;
	
	}*/
	
	
}
LRESULT CFrameWork::OnProcessingWindowMessae(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	switch (iMsg)
	{
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_MOUSEMOVE:
	{
		OnProcessingMouseMessage(hWnd, iMsg, wParam, lParam);
		break;
	}
	case WM_KEYDOWN:
	case WM_KEYUP:
	{
		OnProcessingKeyboardMessage(hWnd, iMsg, wParam, lParam);
		break;
	}
	case WM_COMMAND:
		m_pCurScene->OnProcessingWindowMessage(hWnd, iMsg, wParam, lParam);
		break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = ::BeginPaint(hWnd, &ps);

		OnDraw(hdc);

		::EndPaint(hWnd, &ps);
		break;
	}
	}
	return DefWindowProc(hWnd, iMsg, wParam, lParam);
}