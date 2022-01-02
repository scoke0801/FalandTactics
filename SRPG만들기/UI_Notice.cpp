#include "stdafx.h"
#include "UI_Notice.h"

CUI_Notice* CUI_Notice::instance = NULL;
CUI_Notice::CUI_Notice(HWND hWnd, HINSTANCE hInstance, NoticePhase phase)
	:CUI(hWnd, hInstance)
{
	szWindowClass = _T("Notice_Class");
	szWindowTitle = _T("알림말");

	//RegisterUI();

	//m_imageNoticeBox.Load(_T("resource/UI/phase1_.png"));
	m_nPhase = phase;
}
CUI_Notice::~CUI_Notice()
{

}
void CUI_Notice::Update(NoticePhase phase)
{
	if (phase == NoticePhase::SkillPhase )
	{
		MoveWindow(hUi, 0, 0, 448, 62, FALSE);
	}
	else
	{
		MoveWindow(hUi, 0, 0, 350, 62, FALSE);
	}
	m_nPhase = phase;
	InvalidateRect(hUi, &m_rcRect, FALSE);
}
void CUI_Notice::RegisterUI()
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
		wcex.lpfnWndProc = UI_Notice_Proc;
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

void CUI_Notice::MakeUI()
{
	if (hUi)
	{
		ShowWindow(hUi, SW_SHOW);
		EnableWindow(hUi, FALSE);
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
		, 0				// 윈도우 보일 때 x 좌표 
		, 0					// 윈도우 보일 때 y 좌표 
		, 350					    // 윈도우 폭
		, 62					    // 윈도우 높이
		, hWnd					    //부모 윈도우
		, (HMENU)NULL			    //메뉴 핸들
		, hInstance				    //인스턴스 핸들
		, NULL					    //추가 파라메터
		);

	::ShowWindow(hUi, SW_SHOW);
	EnableWindow(hUi, FALSE);
}
void CUI_Notice::DestroyUI()
{
	if (hUi)
	{
		::DestroyWindow(hUi);
		hUi = NULL;
	}
}
void CUI_Notice::HideUI()
{
	if (hUi)
	{
		::ShowWindow(hUi, SW_HIDE);
	}
}
void CUI_Notice::DrawUI(HDC hdc)
{
	if (!m_imageNoticeBox.IsNull())
		m_imageNoticeBox.Destroy();
	switch (m_nPhase)
	{
	case NoticePhase::AttackPhase:
		m_imageNoticeBox.Load(_T("resource/UI/phase_attack.png"));
		break;
	case NoticePhase::MoveNotice:
		m_imageNoticeBox.Load(_T("resource/UI/phase_move.png"));
		break;
	case NoticePhase::UnitWayPhase:
		m_imageNoticeBox.Load(_T("resource/UI/phase_way.png"));
		break;
	case NoticePhase::SkillPhase:
		m_imageNoticeBox.Load(_T("resource/UI/phase_skill.png"));
		break;
	case NoticePhase::WaitSkillPhase:
		m_imageNoticeBox.Load(_T("resource/UI/phase_skillWait.png"));
		break;
	case NoticePhase::ManaLack:
		m_imageNoticeBox.Load(_T("resource/UI/Phase_manaLack.png"));
	}
	m_imageNoticeBox.TransparentBlt(hdc,
		0, 0
		, m_imageNoticeBox.GetWidth(), m_imageNoticeBox.GetHeight()
		, 0, 0
		, m_imageNoticeBox.GetWidth(), m_imageNoticeBox.GetHeight()
		, RGB(255, 0, 0)
		);
}
void DrawUI(HDC hdc, NoticePhase phase)
{

}

CUI_Notice * CUI_Notice::GetInstance(HWND hWnd, HINSTANCE hInstance, NoticePhase phase)
{
	if (instance == NULL)
	{
		instance = new CUI_Notice(hWnd, hInstance, phase);
	}
	return instance;
}
CUI_Notice * CUI_Notice::GetInstance()
{
	return instance;
}

LRESULT CALLBACK UI_Notice_Proc(HWND hWnd, UINT iMsg,
	WPARAM wParam, LPARAM lParam)
{
	HDC hdc, bufferDC; //화면에 출력할 hdc, 출력하기 전까지 저장할 변수 bufferDC
	PAINTSTRUCT ps;
	static RECT rect;
	static CUI_Notice* self;
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