#include "stdafx.h"
#include "GameOver.h"

CGameOverScene::CGameOverScene(CFrameWork * framework, HWND hWnd, CurrentScene tag)
	:CScene(framework, hWnd)
{
	m_tag = tag;
	m_nCount[0] = 0;
	m_nCount[1] = 0;
	//m_nAlpha = 255;
	m_UnitType = FALSE;
	LoadImage();
}

CGameOverScene::~CGameOverScene()
{
	m_gameOverImage.Destroy();
}

void CGameOverScene::LoadImage()
{
	if (m_tag == CurrentScene::GameWin)
	{
		m_gameOverImage.Load(_T("resource/UI/StageClear_.png"));
		
		m_imageUnit.Load(_T("resource/Unit/karin/karin_notice.png"));
	}
	else if (m_tag == CurrentScene::GameLose)
	{
		m_gameOverImage.Load(_T("resource/map/gamelose.png"));
	}
}

void CGameOverScene::OnUpdate(float timeElapsed)
{

}

void CGameOverScene::OnDraw(HDC hdc)
{
	//static int count = 0;
	COLORREF removeColor = RGB(255, 0, 255);		//지울 색상
	//static int alpha = 255;				//투명도
	
	if (m_nAlpha >= 0)
	{
		HDC LayDC;
		HBITMAP Lay;
		BLENDFUNCTION bf;

		bf.BlendOp = AC_SRC_OVER;
		bf.BlendFlags = 0;
		bf.AlphaFormat = 0;
		bf.SourceConstantAlpha = m_nAlpha;

		Lay = CreateCompatibleBitmap(hdc, m_rcApp.right, m_rcApp.bottom);
		LayDC = CreateCompatibleDC(hdc);
		SelectObject(LayDC, Lay);
		TransparentBlt(LayDC, 0, 0, m_rcApp.right, m_rcApp.bottom
			, hdc, m_rcApp.left, m_rcApp.top, m_rcApp.right, m_rcApp.bottom, removeColor);

		/*std::vector<Image>* image = FindImage(name);

		if (image)
			image->begin()->GetCimage()->TransparentBlt(hdc, left, top, width, height,
				s_left, s_top, s_width, s_height, removeColor);*/
		if (m_tag == CurrentScene::GameLose)
		{
			m_gameOverImage.TransparentBlt(hdc
				, m_rcApp.left, m_rcApp.top, m_rcApp.right, m_rcApp.bottom
				, 0, 0, m_gameOverImage.GetWidth(), m_gameOverImage.GetHeight(), removeColor);
		}
		/*else
		{
			DrawWinAnimation(hdc);
		}*/
		AlphaBlend(hdc, m_rcApp.left, m_rcApp.top, m_rcApp.right, m_rcApp.bottom
			, LayDC, 0, 0, m_rcApp.right, m_rcApp.bottom, bf);

		DeleteDC(LayDC);
		DeleteObject(Lay);
		m_nAlpha -= 3;
	}
	else
	{
		if (m_tag == CurrentScene::GameLose)
		{
			m_gameOverImage.StretchBlt(hdc
				, m_rcApp.left, m_rcApp.top, m_rcApp.right, m_rcApp.bottom
				, 0, 0, m_gameOverImage.GetWidth(), m_gameOverImage.GetHeight());
		}
		else
		{
			DrawWinAnimation(hdc);
		}
	}
}

void CGameOverScene::PlaySound()
{
	m_pFrameWork->GetSound()->Stop();
}
//CTitleScene에서의 처리 이후에도 처리가 필요할 것이 있다면 FALSE를 반환합니다.
BOOL CGameOverScene::OnProcessingKeyboardMessage(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	return FALSE;
}
BOOL CGameOverScene::OnProcessingMouseMessage(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	switch (iMsg)
	{
	case WM_LBUTTONDOWN:
		int result;
		result = MessageBox(hWnd, _T("Retry?"), _T("재시작"), MB_YESNO);
		if (result == IDYES)
		{
			m_pFrameWork->ChangeScene(CScene::CurrentScene::Title);
		}
		else if (result == IDNO)
		{
			PostQuitMessage(0);
		}
		break;
	case WM_LBUTTONDBLCLK:
		MessageBox(hWnd, _T("프로그램을 종료합니다."), _T("게임 종료"), MB_OK);
		break;
	} 
	return FALSE;
}
//virtual BOOL OnProcessingWindowMessage(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
void CGameOverScene::SetTag(CurrentScene tag)
{
	m_tag = tag;
	LoadImage();
}

void CGameOverScene::DrawWinAnimation(HDC hdc)
{
	if (!m_UnitType)
	{
		m_imageUnit.TransparentBlt(hdc,
			m_rcApp.right / 6 * 4, m_rcApp.bottom / 2 - 50, 68 * 2, 73 * 2,
			m_nCount[1] * 68, 0, 68, 73, RGB(0, 255, 255)
			);
	}
	
	m_gameOverImage.TransparentBlt(hdc
		, m_rcApp.right / 6 * 1, m_rcApp.bottom / 2 - 73
		, 400, 146
		, 0, 0, 400, 146, RGB(255, 0, 255)
		);
	//::Rectangle(hdc, m_rcApp.right / 6 * 1, m_rcApp.bottom / 2 - 50
	//	, m_rcApp.right / 6 * 1 + 400, m_rcApp.bottom / 2 + 50);
	++m_nCount[0];
	if (m_nCount[0] > 50)
		++m_nCount[1];

	if (m_nCount[1] > 4)
		m_nCount[1] = 4;
}