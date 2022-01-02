#include "stdafx.h"
#include "UI_Notice.h"

CUI_Notice* CUI_Notice::instance = NULL;
CUI_Notice::CUI_Notice(HWND hWnd, HINSTANCE hInstance, NoticePhase phase)
	:CUI(hWnd, hInstance)
{
	szWindowClass = _T("Notice_Class");
	szWindowTitle = _T("�˸���");

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
			CS_HREDRAW	//Ŭ���̾�Ʈ�� ���̸� �����ϸ� �ٽ� �׸����� �մϴ�. 
			| CS_VREDRAW	//Ŭ���̾�Ʈ�� ���̸� �����ϸ� �ٽ� �׸����� �մϴ�.
			| CS_DBLCLKS	//�ش� �������α׷��� ���� Ŭ���� �����ϵ��� �մϴ�.
			;
		wcex.lpfnWndProc = UI_Notice_Proc;
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
		szWindowClass           // ���ϵ� ������ Ŭ���� �̸� 
		, szWindowTitle         // ������ Ÿ��Ʋ 
		, WS_CHILD
		| WS_SYSMENU
		| WS_VISIBLE
		| WS_CLIPSIBLINGS			//���ϵ峢�� ��ȣ ��ģ ������ �׸��� �������� ����
		| WS_CLIPCHILDREN			//���ϵ尡 ��ġ�� ������ �׸��� �������� ����
		, 0				// ������ ���� �� x ��ǥ 
		, 0					// ������ ���� �� y ��ǥ 
		, 350					    // ������ ��
		, 62					    // ������ ����
		, hWnd					    //�θ� ������
		, (HMENU)NULL			    //�޴� �ڵ�
		, hInstance				    //�ν��Ͻ� �ڵ�
		, NULL					    //�߰� �Ķ����
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
	HDC hdc, bufferDC; //ȭ�鿡 ����� hdc, ����ϱ� ������ ������ ���� bufferDC
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

		bufferDC = CreateCompatibleDC(hdc);//hdc�� ȣȯ�Ǵ� bufferDC����, ������۸�
		hBmp = CreateBitmap(rect.right, rect.bottom, 1, 32, NULL);
		SelectObject(bufferDC, hBmp);	
		//::FillRect(hdc, &rect, (HBRUSH)::GetStockObject(WHITE_BRUSH));
		//Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
		
		self->DrawUI(bufferDC);
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