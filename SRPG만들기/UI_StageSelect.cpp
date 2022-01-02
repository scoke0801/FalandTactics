#include "stdafx.h"
#include "UI_StageSelect.h"

CUI_StageSelect* CUI_StageSelect::instance = NULL;

CUI_StageSelect::CUI_StageSelect(HWND hWnd, HINSTANCE hInstance)
	:CUI(hWnd, hInstance)
{
	szWindowClass = _T("StageSelect_Class");
	szWindowTitle = _T("�������� ����");

	//RegisterUI();

	m_font = CreateFont(30, 10, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0,
		VARIABLE_PITCH | FF_ROMAN, _T("����"));
	m_tag = CScene::CurrentScene::Title;
	m_bTitie = TRUE;
}
CUI_StageSelect::~CUI_StageSelect()
{

}

void CUI_StageSelect::RegisterUI()
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
		wcex.lpfnWndProc = UI_StageSelect_Proc;
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

void CUI_StageSelect::MakeUI()
{
	if (hUi)
		return;

	hUi = CreateWindow(
		szWindowClass           // ���ϵ� ������ Ŭ���� �̸� 
		, szWindowTitle         // ������ Ÿ��Ʋ 
		, WS_CHILD
		| WS_THICKFRAME
		| WS_VISIBLE
		| WS_CLIPSIBLINGS				//���ϵ峢�� ��ȣ ��ģ ������ �׸��� �������� ����
		| WS_CLIPCHILDREN				//���ϵ尡 ��ġ�� ������ �׸��� �������� ����
		, m_rcRect.right / 6 *1			// ������ ���� �� x ��ǥ 
		, m_rcRect.bottom / 6 *1		// ������ ���� �� y ��ǥ 
		, m_rcRect.right/ 6 * 4			// ������ ��
		, m_rcRect.bottom / 4 * 3		 // ������ ����
		, hWnd			        //�θ� ������
		, (HMENU)NULL		    //�޴� �ڵ�
		, hInstance		        //�ν��Ͻ� �ڵ�
		, NULL		            //�߰� �Ķ����
		);

	::ShowWindow(hUi, SW_SHOW);
}
void CUI_StageSelect::MakeButtonUI()
{
	CImage image;
	HBITMAP hBmp;

	*m_buttonSelectStage = CreateWindow(_T("button"), _T("�������� ����"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP,
		m_rcRect.right / 8 * 1, m_rcRect.bottom - 75, m_rcRect.right / 4 * 1, 75,
		hWnd, (HMENU)IDC_BUTTON_SelectStage, m_pFrameWork->GetHINSTANCE(), NULL);
	
	image.Load(_T("resource/button/SelectStage.png"));
	hBmp = image.Detach();
	SendMessage(*m_buttonSelectStage, BM_SETIMAGE, 0, (LPARAM)hBmp);

	*m_buttonLoadStage = CreateWindow(_T("button"), _T("�� �ҷ�����"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP,
		m_rcRect.right / 8 * 3, m_rcRect.bottom - 75, m_rcRect.right / 4 * 1, 75,
		hWnd, (HMENU)IDC_BUTTON_LoadStage, m_pFrameWork->GetHINSTANCE(), NULL);
	
	image.Load(_T("resource/button/LoadStage.png"));
	hBmp = image.Detach();
	SendMessage(*m_buttonLoadStage, BM_SETIMAGE, 0, (LPARAM)hBmp);

	*m_buttonEndGame = CreateWindow(_T("button"), _T("���� ����"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP,
		m_rcRect.right / 8 * 5, m_rcRect.bottom - 75, m_rcRect.right / 4 * 1, 75,
		hWnd, (HMENU)IDC_BUTTON_EndGame, m_pFrameWork->GetHINSTANCE(), NULL);
	image.Load(_T("resource/button/EndGame.png"));
	hBmp = image.Detach();
	SendMessage(*m_buttonEndGame, BM_SETIMAGE, 0, (LPARAM)hBmp);
	/*SendMessage(*m_buttonSelectStage, WM_SETFONT, (WPARAM)m_font, MAKELPARAM(TRUE, 0));
	SendMessage(*m_buttonLoadStage, WM_SETFONT, (WPARAM)m_font, MAKELPARAM(TRUE, 0));
	SendMessage(*m_buttonEndGame, WM_SETFONT, (WPARAM)m_font, MAKELPARAM(TRUE, 0));*/
}

void CUI_StageSelect::SetButton(HWND* hButtonSelectStage, HWND* hButtonLoadStage, HWND* hButtonEndGame)
{
	m_buttonSelectStage = hButtonSelectStage;
	m_buttonLoadStage = hButtonLoadStage;
	m_buttonEndGame = hButtonEndGame;
}

BOOL CUI_StageSelect::UpdateUI()
{
	if (hUi == NULL)
		return TRUE;
	return FALSE;
}

void CUI_StageSelect::DestroyUI()
{
	DestroyWindow(hUi);

	hUi = NULL;
}

CUI_StageSelect * CUI_StageSelect::GetInstance(HWND hWnd, HINSTANCE hInstance)
{
	if (instance == NULL)
	{
		instance = new CUI_StageSelect(hWnd, hInstance);
	}
	return instance;
}

CUI_StageSelect * CUI_StageSelect::GetInstance()
{
	return instance;
}

LRESULT CALLBACK UI_StageSelect_Proc(HWND hWnd, UINT iMsg,
	WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	static HWND hList;
	static HWND  hButtonSelect, hButtonCancel;
	static HFONT hFont;
	static RECT rect;

	static CUI_StageSelect* self = CUI_StageSelect::GetInstance();
	static CFrameWork* frameWork = self->GetFrameWork();

	static int userSelect;

	switch (iMsg)
	{
	case WM_CREATE:
		::GetClientRect(hWnd, &rect);
		userSelect = -1;

		hFont = CreateFont(30, 10, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0,
			VARIABLE_PITCH | FF_ROMAN, _T("����"));

		hButtonSelect = CreateWindow(_T("button"), _T("����"),
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 
			rect.right - 200, rect.bottom - 30, 100, 30,
			hWnd, (HMENU)IDC_BUTTON_Select, self->GetHINSTANCE(), NULL);
		
		hButtonCancel = CreateWindow(_T("button"), _T("���"),
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			rect.right - 100, rect.bottom - 30,  100, 30,
			hWnd, (HMENU)IDC_BUTTON_Cancel, self->GetHINSTANCE(), NULL);
		
		hList = CreateWindow(_T("listbox")
			, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | LBS_NOTIFY
			, 0, 0, rect.right, rect.bottom - 30
			, hWnd, (HMENU)ID_LISTBOX_Stage, self->GetHINSTANCE(), NULL);

		SendMessage(hList, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0)); 
		SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)_T("���    (����)"));
		SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)_T("���    (����óġ)"));
		SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)_T("����    (����óġ)"));
		SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)_T("����    (��ǥ���� ����)"));
		SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)_T("�ٸ�    (����)"));
		SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)_T("������ (������ 1:1)"));

		if(self->GetCurrentStage() != CScene::CurrentScene::Title)
			SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)_T("Ÿ��Ʋ"));
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_LISTBOX_Stage:
			switch (HIWORD(wParam)) {
			case LBN_SELCHANGE:
				userSelect = SendMessage(hList, LB_GETCURSEL, 0, 0);
				break;
			}
			break;

		case IDC_BUTTON_Select:
			if (userSelect == -1)
			{
				MessageBox(hWnd, _T("�߸��� �����Դϴ�"),
					_T("���� ����"), MB_ICONEXCLAMATION);
				break;
			}

			//frameWork->ChangeScene((CScene::CurrentScene::Stage1));
			frameWork->ChangeScene(((CScene::CurrentScene)(userSelect + 2)));
			DestroyWindow(hWnd);
			self->DestroyUI();

			break;
			case IDC_BUTTON_Cancel:
				if (self->GetCurrentStage() == CScene::CurrentScene::Title)
				{
					self->MakeButtonUI();
				}
				DestroyWindow(hWnd);
				self->DestroyUI();
	
			break;
			
		}
		break;
	case WM_PAINT:
		hdc = ::BeginPaint(hWnd, &ps);
		::FillRect(hdc, &rect, (HBRUSH)GetStockObject(LTGRAY_BRUSH));
		SetBkMode(hdc, TRANSPARENT);

		TextOut(hdc
			, rect.left
			, rect.bottom - 25
			, _T("���������� �������ּ���")
			, _tcslen(_T("���������� �������ּ���")));
		::EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		break;
	}
	return DefMDIChildProc(hWnd, iMsg, wParam, lParam);
}