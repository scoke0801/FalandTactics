#include "stdafx.h"
#include "UI_StageSelect.h"

CUI_StageSelect* CUI_StageSelect::instance = NULL;

CUI_StageSelect::CUI_StageSelect(HWND hWnd, HINSTANCE hInstance)
	:CUI(hWnd, hInstance)
{
	szWindowClass = _T("StageSelect_Class");
	szWindowTitle = _T("스테이지 선택");

	//RegisterUI();

	m_font = CreateFont(30, 10, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0,
		VARIABLE_PITCH | FF_ROMAN, _T("굴림"));
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
			CS_HREDRAW	//클라이언트의 넓이를 변경하면 다시 그리도록 합니다. 
			| CS_VREDRAW	//클라이언트의 높이를 변경하면 다시 그리도록 합니다.
			| CS_DBLCLKS	//해당 응용프로그램이 더블 클릭을 지원하도록 합니다.
			;
		wcex.lpfnWndProc = UI_StageSelect_Proc;
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

void CUI_StageSelect::MakeUI()
{
	if (hUi)
		return;

	hUi = CreateWindow(
		szWindowClass           // 차일드 윈도우 클래스 이름 
		, szWindowTitle         // 윈도우 타이틀 
		, WS_CHILD
		| WS_THICKFRAME
		| WS_VISIBLE
		| WS_CLIPSIBLINGS				//차일드끼리 상호 겹친 영역은 그리기 영역에서 제외
		| WS_CLIPCHILDREN				//차일드가 위치한 영역은 그리기 영역에서 제외
		, m_rcRect.right / 6 *1			// 윈도우 보일 때 x 좌표 
		, m_rcRect.bottom / 6 *1		// 윈도우 보일 때 y 좌표 
		, m_rcRect.right/ 6 * 4			// 윈도우 폭
		, m_rcRect.bottom / 4 * 3		 // 윈도우 높이
		, hWnd			        //부모 윈도우
		, (HMENU)NULL		    //메뉴 핸들
		, hInstance		        //인스턴스 핸들
		, NULL		            //추가 파라메터
		);

	::ShowWindow(hUi, SW_SHOW);
}
void CUI_StageSelect::MakeButtonUI()
{
	CImage image;
	HBITMAP hBmp;

	*m_buttonSelectStage = CreateWindow(_T("button"), _T("스테이지 선택"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP,
		m_rcRect.right / 8 * 1, m_rcRect.bottom - 75, m_rcRect.right / 4 * 1, 75,
		hWnd, (HMENU)IDC_BUTTON_SelectStage, m_pFrameWork->GetHINSTANCE(), NULL);
	
	image.Load(_T("resource/button/SelectStage.png"));
	hBmp = image.Detach();
	SendMessage(*m_buttonSelectStage, BM_SETIMAGE, 0, (LPARAM)hBmp);

	*m_buttonLoadStage = CreateWindow(_T("button"), _T("맵 불러오기"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP,
		m_rcRect.right / 8 * 3, m_rcRect.bottom - 75, m_rcRect.right / 4 * 1, 75,
		hWnd, (HMENU)IDC_BUTTON_LoadStage, m_pFrameWork->GetHINSTANCE(), NULL);
	
	image.Load(_T("resource/button/LoadStage.png"));
	hBmp = image.Detach();
	SendMessage(*m_buttonLoadStage, BM_SETIMAGE, 0, (LPARAM)hBmp);

	*m_buttonEndGame = CreateWindow(_T("button"), _T("게임 종료"),
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
			VARIABLE_PITCH | FF_ROMAN, _T("굴림"));

		hButtonSelect = CreateWindow(_T("button"), _T("선택"),
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 
			rect.right - 200, rect.bottom - 30, 100, 30,
			hWnd, (HMENU)IDC_BUTTON_Select, self->GetHINSTANCE(), NULL);
		
		hButtonCancel = CreateWindow(_T("button"), _T("취소"),
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			rect.right - 100, rect.bottom - 30,  100, 30,
			hWnd, (HMENU)IDC_BUTTON_Cancel, self->GetHINSTANCE(), NULL);
		
		hList = CreateWindow(_T("listbox")
			, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | LBS_NOTIFY
			, 0, 0, rect.right, rect.bottom - 30
			, hWnd, (HMENU)ID_LISTBOX_Stage, self->GetHINSTANCE(), NULL);

		SendMessage(hList, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0)); 
		SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)_T("요새    (섬멸)"));
		SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)_T("고원    (보스처치)"));
		SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)_T("성벽    (보스처치)"));
		SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)_T("제단    (목표지점 도달)"));
		SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)_T("다리    (섬멸)"));
		SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)_T("투기장 (무작위 1:1)"));

		if(self->GetCurrentStage() != CScene::CurrentScene::Title)
			SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)_T("타이틀"));
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
				MessageBox(hWnd, _T("잘못된 선택입니다"),
					_T("선택 실패"), MB_ICONEXCLAMATION);
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
			, _T("스테이지를 선택해주세요")
			, _tcslen(_T("스테이지를 선택해주세요")));
		::EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		break;
	}
	return DefMDIChildProc(hWnd, iMsg, wParam, lParam);
}