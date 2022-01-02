#include "stdafx.h"
#include "UI_ClearCondition.h"

CUI_ClearCondition* CUI_ClearCondition::instance = NULL;
CUI_ClearCondition::CUI_ClearCondition(HWND hWnd, HINSTANCE hInstance, CScene::CurrentScene phase)
	:CUI(hWnd, hInstance)
{
	szWindowClass = _T("ClearCondition_Class");
	szWindowTitle = _T("�˸���");

	//RegisterUI();

	//m_imageCondition.Load(_T("resource/UI/phase1_.png"));
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
			CS_HREDRAW	//Ŭ���̾�Ʈ�� ���̸� �����ϸ� �ٽ� �׸����� �մϴ�. 
			| CS_VREDRAW	//Ŭ���̾�Ʈ�� ���̸� �����ϸ� �ٽ� �׸����� �մϴ�.
			| CS_DBLCLKS	//�ش� �������α׷��� ���� Ŭ���� �����ϵ��� �մϴ�.
			;
		wcex.lpfnWndProc = UI_ClearCondition_Proc;
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
		szWindowClass           // ���ϵ� ������ Ŭ���� �̸� 
		, szWindowTitle         // ������ Ÿ��Ʋ 
		, WS_CHILD
		| WS_SYSMENU
		| WS_VISIBLE
		| WS_CLIPSIBLINGS			//���ϵ峢�� ��ȣ ��ģ ������ �׸��� �������� ����
		| WS_CLIPCHILDREN			//���ϵ尡 ��ġ�� ������ �׸��� �������� ����
		, m_rcRect.right / 2 - 160	// ������ ���� �� x ��ǥ 
		, m_rcRect.bottom / 2 - 73	// ������ ���� �� y ��ǥ 
		, 320					    // ������ ��
		, 146					    // ������ ����
		, hWnd					    //�θ� ������
		, (HMENU)NULL			    //�޴� �ڵ�
		, hInstance				    //�ν��Ͻ� �ڵ�
		, NULL					    //�߰� �Ķ����
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
		m_imageCondition.Load(_T("resource/UI/annihilation.png"));
		break;
	case CScene::CurrentScene::Stage2:
		m_imageCondition.Load(_T("resource/UI/BossCatherine.png"));
		break;
	case CScene::CurrentScene::Stage3:
		m_imageCondition.Load(_T("resource/UI/BossIvan.png"));
		break;
	case CScene::CurrentScene::Stage4:
		m_imageCondition.Load(_T("resource/UI/Move2Potal.png"));
		break;
	case CScene::CurrentScene::Stage5:
		m_imageCondition.Load(_T("resource/UI/annihilation.png"));
		break;
	case CScene::CurrentScene::Stage6:
		m_imageCondition.Load(_T("resource/UI/annihilation.png"));
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
	HDC hdc, bufferDC; //ȭ�鿡 ����� hdc, ����ϱ� ������ ������ ���� bufferDC
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