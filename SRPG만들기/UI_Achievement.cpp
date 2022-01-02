#include "stdafx.h"
#include "UI_Achievement.h"

CUI_Achievement* CUI_Achievement::instance = NULL;
CUI_Achievement::CUI_Achievement(HWND hWnd, HINSTANCE hInstance, CUnit* unit)
	:CUI(hWnd, hInstance)
{
	szWindowClass = _T("Achievement_Class");
	szWindowTitle = _T("업적");

	m_pUnit = unit;
	//RegisterUI();

	m_unitImage.Load(_T("resource/Unit/unit_all.png"));
	m_backImage.Load(_T("resource/UI/unit_info_background.png"));
	m_hpMpImage.Load(_T("resource/UI/HP_MP.png"));
}
CUI_Achievement::~CUI_Achievement()
{

}
void CUI_Achievement::OnUpdate()
{
	ShowUI();
	InvalidateRect(hUi, &m_rcRect, FALSE);
}
void CUI_Achievement::RegisterUI()
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
		wcex.lpfnWndProc = UI_UnitInfo_Proc;
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

void CUI_Achievement::MakeUI()
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
		| WS_CLIPSIBLINGS		//차일드끼리 상호 겹친 영역은 그리기 영역에서 제외
		| WS_CLIPCHILDREN		//차일드가 위치한 영역은 그리기 영역에서 제외
		, m_rcRect.right - 320	// 윈도우 보일 때 x 좌표 
		, m_rcRect.bottom - 118	// 윈도우 보일 때 y 좌표 
		, 320			        // 윈도우 폭
		, 118			        // 윈도우 높이
		, hWnd			        //부모 윈도우
		, (HMENU)NULL		    //메뉴 핸들
		, hInstance		        //인스턴스 핸들
		, NULL		            //추가 파라메터
		);

	//::ShowWindow(hUi, SW_SHOW);
	EnableWindow(hUi, FALSE);
}
void CUI_Achievement::DestroyUI()
{
	if (hUi)
	{
		::DestroyWindow(hUi);
		hUi = NULL;
	}
}
void CUI_Achievement::HideUI()
{
	if (hUi)
	{
		::ShowWindow(hUi, SW_HIDE);
	}
}
BOOL CUI_Achievement::CompareUnit(CUnit* unit)
{
	if (m_pUnit == unit)
		return TRUE;
	return FALSE;
}
void CUI_Achievement::DrawUnit(HDC hdc)
{
	if (m_pUnit == NULL)
		return;

	int imagePos = (int)m_pUnit->GetUnitName();


	m_backImage.TransparentBlt(hdc, 0, 0, 320, 118,
		0, 0, 320, 118, RGB(255, 0, 0));
	m_unitImage.TransparentBlt(
		hdc, 0, 0, 90, 95,
		(imagePos % 9) * 90, (imagePos / 9) * 95, 90, 95, RGB(255, 0, 255));

	m_hpMpImage.StretchBlt(hdc			//Max HP
		, 150, 25, (int)(m_pUnit->GetMaxHp() * 100 / 170 * 1.1)
		, 15, 0, 0, 150, 12, SRCCOPY);
	m_hpMpImage.StretchBlt(hdc			//Current HP
		, 150 + (int)(m_pUnit->GetMaxHp() * 100 / 170 * 1.1)
		- (int)((float)(m_pUnit->GetMaxHp() - m_pUnit->GetHp()) * 100 / 170 * 1.1)
		, 25, (int)((float)(m_pUnit->GetMaxHp() - m_pUnit->GetHp()) * 100 / 170 * 1.1)
		, 15, 0, 12, 150, 12, SRCCOPY);

	m_hpMpImage.StretchBlt(hdc			//Max Mp
		, 150, 75, (int)(m_pUnit->GetMaxMp() * 100 / 170 * 1.1)
		, 13, 150, 0, 150, 12, SRCCOPY);
	m_hpMpImage.StretchBlt(hdc          //Current Mp
		, 150 + (int)(m_pUnit->GetMaxMp() * 100 / 170 * 1.1)
		- (int)((float)(m_pUnit->GetMaxMp() - m_pUnit->GetMp()) / 170 * 100 * 1.1)
		, 75, (int)((float)(m_pUnit->GetMaxMp() - m_pUnit->GetMp()) / 170 * 100 * 1.1)
		, 13, 150, 12, 150, 12, SRCCOPY);
}
void CUI_Achievement::ReDraw()
{
	InvalidateRect(hUi, NULL, FALSE);
}
CUI_Achievement * CUI_Achievement::GetInstance(HWND hWnd, HINSTANCE hInstance, CUnit* unit)
{
	if (instance == NULL)
	{
		instance = new CUI_Achievement(hWnd, hInstance, unit);
	}
	return instance;
}
CUI_Achievement * CUI_Achievement::GetInstance()
{
	return instance;
}

LRESULT CALLBACK UI_Achievement_Proc(HWND hWnd, UINT iMsg,
	WPARAM wParam, LPARAM lParam)
{
	HDC hdc, bufferDC; //화면에 출력할 hdc, 출력하기 전까지 저장할 변수 bufferDC
	PAINTSTRUCT ps;
	static RECT rect;
	static CUI_Achievement* self;
	static HBITMAP		hBmp;

	switch (iMsg)
	{
	case WM_CREATE:
		self = self->GetInstance();
		rect = self->GetRect();
		break;

		/*case WM_ERASEBKGND:
		InvalidateRect(hWnd, NULL, FALSE);
		break;*/
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		bufferDC = CreateCompatibleDC(hdc);//hdc와 호환되는 bufferDC생성, 더블버퍼링
		hBmp = CreateBitmap(rect.right, rect.bottom, 1, 32, NULL);
		SelectObject(bufferDC, hBmp);

		self->DrawUnit(bufferDC);

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