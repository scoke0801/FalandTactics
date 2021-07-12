#include "stdafx.h"
#include "UI_ClearCondition.h"

CUI_ClearCondition* CUI_ClearCondition::instance = NULL;
CUI_ClearCondition::CUI_ClearCondition(HWND hWnd, HINSTANCE hInstance, CScene::CurrentScene phase)
	:CUI(hWnd, hInstance)
{
	szWindowClass = _T("ClearCondition_Class");
	szWindowTitle = _T("알림말");

	//RegisterUI();

	//m_imageCondition.Load(_T("resource/UI/phase1_.bmp"));
	m_phase = phase;
}
CUI_ClearCondition::~CUI_ClearCondition()
{

}
void CUI_ClearCondition::Update(CScene::CurrentScene phase)
{
	m_phase = phase;
	InvalidateRect(hUi, &m_rcRect, FALSE);
}
void CUI_ClearCondition::RegisterUI()
{
	if (!m_bRegistration)
	{
		WNDCLASSEXW wcex;

		wcex.cbSize = sizeof(WNDCLASSEX);

		wcex.style =
			CS_HREDRAW	//클라이언트의 넓이를 변경하면 다시 그리도록 합니다. 
			| CS_VREDRAW	//클라이언트의 높이를 변경하면 다시 그리도록 합니다.
			| CS_DBLCLKS	//해당 응용프로그램이 더블 클릭을 지원하도록 합니다.
			;
		wcex.lpfnWndProc = UI_ClearCondition_Proc;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = 0;
		wcex.hInstance = hInstance;	///응용 프로그램의 인스턴스 핸들을 등록합니다.
									//MAKEINTRESOURCE : Make Inter Source - 응용 프로그램 내부에 있는 리소스의 인덱스를 반환하는 매크로
		wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SRPG));
		wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wcex.hbrBackground = (HBRUSH)BLACK_BRUSH;
		wcex.lpszMenuName = NULL;
		wcex.lpszClassName = szWindowClass;
		wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
		assert(RegisterClassExW(&wcex));

		m_bRegistration = TRUE;
	}
}

void CUI_ClearCondition::MakeUI()
{
	if (hUi)
	{
		ShowWindow(hUi, SW_SHOW);
		::EnableWindow(hUi, FALSE);
		InvalidateRect(hUi, &m_rcRect, FALSE);
		return;
	}

	hUi = CreateWindow(
		szWindowClass           // 차일드 윈도우 클래스 이름 
		, szWindowTitle         // 윈도우 타이틀 
		, WS_CHILD
		| WS_SYSMENU
		| WS_VISIBLE
		| WS_CLIPSIBLINGS			//차일드끼리 상호 겹친 영역은 그리기 영역에서 제외
		| WS_CLIPCHILDREN			//차일드가 위치한 영역은 그리기 영역에서 제외
		, m_rcRect.right / 2 - 160	// 윈도우 보일 때 x 좌표 
		, m_rcRect.bottom / 2 - 73	// 윈도우 보일 때 y 좌표 
		, 320					    // 윈도우 폭
		, 146					    // 윈도우 높이
		, hWnd					    //부모 윈도우
		, (HMENU)NULL			    //메뉴 핸들
		, hInstance				    //인스턴스 핸들
		, NULL					    //추가 파라메터
		);

	::ShowWindow(hUi, SW_SHOW);
	::EnableWindow(hUi, FALSE);
}
void CUI_ClearCondition::DestroyUI()
{
	if (hUi)
	{
		::DestroyWindow(hUi);
		hUi = NULL;
	}
}
void CUI_ClearCondition::HideUI()
{
	if (hUi)
	{
		::ShowWindow(hUi, SW_HIDE);
	}
}
void CUI_ClearCondition::DrawUI(HDC hdc)
{
	if (!m_imageCondition.IsNull())
		m_imageCondition.Destroy();
	switch (m_phase)
	{
	case CScene::CurrentScene::Stage1:
		m_imageCondition.Load(_T("resource/UI/annihilation.bmp"));
		break;
	case CScene::CurrentScene::Stage2:
		m_imageCondition.Load(_T("resource/UI/BossCatherine.bmp"));
		break;
	case CScene::CurrentScene::Stage3:
		m_imageCondition.Load(_T("resource/UI/BossIvan.bmp"));
		break;
	case CScene::CurrentScene::Stage4:
		m_imageCondition.Load(_T("resource/UI/Move2Potal.bmp"));
		break;
	case CScene::CurrentScene::Stage5:
		m_imageCondition.Load(_T("resource/UI/annihilation.bmp"));
		break;
	case CScene::CurrentScene::Stage6:
		m_imageCondition.Load(_T("resource/UI/annihilation.bmp"));
		break;
	}
	m_imageCondition.TransparentBlt(hdc,
		0, 0
		, m_imageCondition.GetWidth(), m_imageCondition.GetHeight()
		, 0, 0
		, m_imageCondition.GetWidth(), m_imageCondition.GetHeight()
		, RGB(255, 0, 0)
		);
}

CUI_ClearCondition * CUI_ClearCondition::GetInstance(HWND hWnd, HINSTANCE hInstance, CScene::CurrentScene phase)
{
	if (instance == NULL)
	{
		instance = new CUI_ClearCondition(hWnd, hInstance, phase);
	}
	return instance;
}
CUI_ClearCondition * CUI_ClearCondition::GetInstance()
{
	return instance;
}

LRESULT CALLBACK UI_ClearCondition_Proc(HWND hWnd, UINT iMsg,
	WPARAM wParam, LPARAM lParam)
{
	HDC hdc, bufferDC; //화면에 출력할 hdc, 출력하기 전까지 저장할 변수 bufferDC
	PAINTSTRUCT ps;
	static RECT rect;
	static CUI_ClearCondition* self;
	static HBITMAP		hBmp;

	switch (iMsg)
	{
	case WM_CREATE:
		self = self->GetInstance();
		rect = self->GetRect();
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		bufferDC = CreateCompatibleDC(hdc);//hdc와 호환되는 bufferDC생성, 더블버퍼링
		hBmp = CreateBitmap(rect.right, rect.bottom, 1, 32, NULL);
		SelectObject(bufferDC, hBmp);
		//::FillRect(hdc, &rect, (HBRUSH)::GetStockObject(WHITE_BRUSH));
		//Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);

		self->DrawUI(bufferDC);
		BitBlt(hdc, rect.left, rect.top, rect.right, rect.bottom,
			bufferDC, rect.left, rect.top, SRCCOPY);//bufferDC에 있던 내용을 hdc에 옮겨 그림

		DeleteObject(hBmp);
		DeleteDC(bufferDC);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		break;
	}
	return DefMDIChildProc(hWnd, iMsg, wParam, lParam);
}