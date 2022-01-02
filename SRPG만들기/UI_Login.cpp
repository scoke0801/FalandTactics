#include "stdafx.h"
#include "UI_Login.h"


CUI_Login* CUI_Login::instance = NULL;
CUI_Login::CUI_Login(HWND hWnd, HINSTANCE hInstance)
	:CUI(hWnd, hInstance)
{
	szWindowClass = _T("Login_Class");
	szWindowTitle = _T("�α���");

	m_imageBack.Load(_T("resource/UI/Login_Back.png"));
	//RegisterUI();

	//m_imageNoticeBox.Load(_T("resource/UI/phase1_.png"));
}
CUI_Login::~CUI_Login()
{
	m_imageBack.Destroy();
}

void CUI_Login::RegisterUI()
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
		wcex.lpfnWndProc = UI_Login_Proc;
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

void CUI_Login::MakeUI()
{
	if (hUi)
	{
		CreateButton();
		ShowWindow(hUi, SW_SHOW);
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
		, m_ptPos.x				// ������ ���� �� x ��ǥ 
		, m_ptPos.y					// ������ ���� �� y ��ǥ 
		, 300					    // ������ ��
		, 200					    // ������ ����
		, hWnd					    //�θ� ������
		, (HMENU)NULL			    //�޴� �ڵ�
		, hInstance				    //�ν��Ͻ� �ڵ�
		, NULL					    //�߰� �Ķ����
		);
	
	//CreateWindow(TEXT("edit"), N 10, 10, 200, 25, hWnd, (HMENU)NULL, g_hInst, NULL);
	CreateButton();
	::ShowWindow(hUi, SW_SHOW);
	
}
void CUI_Login::DestroyUI()
{
	if (hUi)
	{
		::DestroyWindow(hUi);
		hUi = NULL;
	}
}
void CUI_Login::HideUI()
{
	if (hUi)
	{
		::ShowWindow(hUi, SW_HIDE);
	}
}
void CUI_Login::DrawUI(HDC hdc)
{
	m_imageBack.StretchBlt(hdc,
		0, 0, 300, 250,
		0, 0, 350, 250, SRCCOPY);
}

void CUI_Login::CreateButton()
{
	CImage image;
	HBITMAP hBmp;
	//HFONT hFont = CreateFont(30, 10, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0,
	//	VARIABLE_PITCH | FF_ROMAN, _T("����"));
	DestroyWindow(m_buttonInput);
	DestroyWindow(m_editName);
	DestroyWindow(m_buttonDefault);

	image.Load(_T("resource/UI/input.png"));
	hBmp = image.Detach();

	m_buttonInput = CreateWindow(_T("button"), _T("�Է�"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP ,
		70, 150, 150, 30,
		hUi, (HMENU)IDC_BUTTON_Input, hInstance, NULL);
	SendMessage(m_buttonInput, BM_SETIMAGE, 0, (LPARAM)hBmp);

	m_editName = CreateWindow(_T("edit"), NULL
		, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL
		, 30, 50, 240, 30
		, hUi, (HMENU)IDE_EDIT_UserName, hInstance, NULL);
	//SendMessage(m_editName, WM_SETFONT, 0, (LPARAM)hFont);
}
void CUI_Login::SetProfile()
{
	TCHAR str[256];

	GetWindowText(m_editName, str, 256);
	//CProfile::GetInstance(str);
}

CUI_Login * CUI_Login::GetInstance(HWND hWnd, HINSTANCE hInstance)
{
	if (instance == NULL)
	{
		instance = new CUI_Login(hWnd, hInstance);
	}
	return instance;
}
CUI_Login * CUI_Login::GetInstance()
{
	return instance;
}

LRESULT CALLBACK UI_Login_Proc(HWND hWnd, UINT iMsg,
	WPARAM wParam, LPARAM lParam)
{
	HDC hdc, bufferDC; //ȭ�鿡 ����� hdc, ����ϱ� ������ ������ ���� bufferDC
	PAINTSTRUCT ps;
	static RECT rect;
	static CUI_Login* self;
	static HBITMAP		hBmp;
	
	switch (iMsg)
	{
	case WM_CREATE:
		self = self->GetInstance();
		rect = self->GetRect();
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON_Input:
			self->SetProfile();
			self->GetParent()->CreateButton();
			self->DestroyUI();
			//DestroyWindow(hWnd);
			break;

		case IDC_BUTTON_Default:
			break;

		case IDE_EDIT_UserName:
			break;
		}
		break;
		
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		bufferDC = CreateCompatibleDC(hdc);//hdc�� ȣȯ�Ǵ� bufferDC����, ������۸�
		hBmp = CreateBitmap(rect.right, rect.bottom, 1, 32, NULL);
		SelectObject(bufferDC, hBmp);
		::FillRect(bufferDC, &rect, (HBRUSH)::GetStockObject(LTGRAY_BRUSH));
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