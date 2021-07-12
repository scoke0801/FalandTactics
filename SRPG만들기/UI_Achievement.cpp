#include "stdafx.h"
#include "UI_Achievement.h"

CUI_Achievement* CUI_Achievement::instance = NULL;
CUI_Achievement::CUI_Achievement(HWND hWnd, HINSTANCE hInstance, CUnit* unit)
	:CUI(hWnd, hInstance)
{
	szWindowClass = _T("Achievement_Class");
	szWindowTitle = _T("����");

	m_pUnit = unit;
	//RegisterUI();

	m_unitImage.Load(_T("resource/Unit/unit_all.bmp"));
	m_backImage.Load(_T("resource/UI/unit_info_background.bmp"));
	m_hpMpImage.Load(_T("resource/UI/HP_MP.bmp"));
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
			CS_HREDRAW	//Ŭ���̾�Ʈ�� ���̸� �����ϸ� �ٽ� �׸����� �մϴ�. 
			| CS_VREDRAW	//Ŭ���̾�Ʈ�� ���̸� �����ϸ� �ٽ� �׸����� �մϴ�.
			| CS_DBLCLKS	//�ش� �������α׷��� ���� Ŭ���� �����ϵ��� �մϴ�.
			;
		wcex.lpfnWndProc = UI_UnitInfo_Proc;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = 0;
		wcex.hInstance = hInstance;	///���� ���α׷��� �ν��Ͻ� �ڵ��� ����մϴ�.
									//MAKEINTRESOURCE : Make Inter Source - ���� ���α׷� ���ο� �ִ� ���ҽ��� �ε����� ��ȯ�ϴ� ��ũ��
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
		szWindowClass           // ���ϵ� ������ Ŭ���� �̸� 
		, szWindowTitle         // ������ Ÿ��Ʋ 
		, WS_CHILD
		| WS_SYSMENU
		| WS_VISIBLE
		| WS_CLIPSIBLINGS		//���ϵ峢�� ��ȣ ��ģ ������ �׸��� �������� ����
		| WS_CLIPCHILDREN		//���ϵ尡 ��ġ�� ������ �׸��� �������� ����
		, m_rcRect.right - 320	// ������ ���� �� x ��ǥ 
		, m_rcRect.bottom - 118	// ������ ���� �� y ��ǥ 
		, 320			        // ������ ��
		, 118			        // ������ ����
		, hWnd			        //�θ� ������
		, (HMENU)NULL		    //�޴� �ڵ�
		, hInstance		        //�ν��Ͻ� �ڵ�
		, NULL		            //�߰� �Ķ����
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
	HDC hdc, bufferDC; //ȭ�鿡 ����� hdc, ����ϱ� ������ ������ ���� bufferDC
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
		bufferDC = CreateCompatibleDC(hdc);//hdc�� ȣȯ�Ǵ� bufferDC����, ������۸�
		hBmp = CreateBitmap(rect.right, rect.bottom, 1, 32, NULL);
		SelectObject(bufferDC, hBmp);

		self->DrawUnit(bufferDC);

		BitBlt(hdc, rect.left, rect.top, rect.right, rect.bottom,
			bufferDC, rect.left, rect.top, SRCCOPY);//bufferDC�� �ִ� ������ hdc�� �Ű� �׸�

		DeleteObject(hBmp);
		DeleteDC(bufferDC);

		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		break;
	}
	return DefMDIChildProc(hWnd, iMsg, wParam, lParam);
}