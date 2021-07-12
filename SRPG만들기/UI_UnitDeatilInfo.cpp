#include "stdafx.h"
#include "UI_UnitDeatilInfo.h"

CUI_UnitDetailInfo* CUI_UnitDetailInfo::instance = NULL;
CUI_UnitDetailInfo::CUI_UnitDetailInfo(HWND hWnd, HINSTANCE hInstance)
	:CUI(hWnd, hInstance)
{
	szWindowClass = _T("UnitDetailInfo_Class");
	szWindowTitle = _T("유닛 정보_");

//RegisterUI();

	m_unitImage.Load(_T("resource/Unit/unit_all.bmp"));
	m_backImage.Load(_T("resource/UI/unit_info_background.bmp"));
	m_hpMpImage.Load(_T("resource/UI/HP_MP.bmp"));

	m_pUnit = NULL;
	m_phase = UnitInfoPhase::None;
	
	m_nUserSelect = -1;
	m_szText = NULL;
}
CUI_UnitDetailInfo::~CUI_UnitDetailInfo()
{

}
void CUI_UnitDetailInfo::OnUpdate()
{
	ShowUI();
	InvalidateRect(hUi, &m_rcRect, FALSE);
}
void CUI_UnitDetailInfo::RegisterUI()
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
		wcex.lpfnWndProc = UI_UnitDetailInfo_Proc;
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

void CUI_UnitDetailInfo::MakeUI()
{
	if (hUi)
	{
		ShowWindow(hUi, SW_SHOW);
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
		, m_rcRect.right / 2 - 200	// 윈도우 보일 때 x 좌표 
		, m_rcRect.bottom / 2 - 250	// 윈도우 보일 때 y 좌표 
		, 400			        // 윈도우 폭
		, 500			        // 윈도우 높이
		, hWnd			        //부모 윈도우
		, (HMENU)NULL		    //메뉴 핸들
		, hInstance		        //인스턴스 핸들
		, NULL		            //추가 파라메터
		);
	CreateButton();
	//::ShowWindow(hUi, SW_SHOW);
}
void CUI_UnitDetailInfo::DestroyUI()
{
	if (hUi)
	{
		::DestroyWindow(hUi);
		hUi = NULL;
	}
}
void CUI_UnitDetailInfo::HideUI()
{
	if (hUi)
	{
		m_phase = UnitInfoPhase::None;
		m_nUserSelect = -1;
		::ShowWindow(hUi, SW_HIDE);
	}
}
void CUI_UnitDetailInfo::CreateButton()
{
	CImage image;
	HBITMAP hBmp;

	DestroyWindow(m_listSkill);

	m_buttonStat = CreateWindow(_T("button"), _T("능력"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP,
		0, 0
		, 200, 30,
		hUi, (HMENU)IDC_BUTTON_UnitStat, hInstance, NULL);
	
	image.Load(_T("resource/UI/stat.bmp"));
	hBmp = image.Detach();
	SendMessage(m_buttonStat, BM_SETIMAGE, 0, (LPARAM)hBmp);

	m_buttonSkill = CreateWindow(_T("button"), _T("스킬"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP,
		200, 0
		, 200, 30,
		hUi, (HMENU)IDC_BUTTON_UnitSkill, hInstance, NULL);
	image.Load(_T("resource/UI/skill.bmp"));
	hBmp = image.Detach();
	SendMessage(m_buttonSkill, BM_SETIMAGE, 0, (LPARAM)hBmp);
}

void CUI_UnitDetailInfo::CreateSkillList()
{
	HFONT hFont;
	hFont = CreateFont(30, 10, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0,
		VARIABLE_PITCH | FF_ROMAN, _T("굴림"));

	DestroyWindow(m_listSkill);

	m_listSkill = CreateWindow(_T("listbox")
		, NULL
		, WS_CHILD | WS_VISIBLE | WS_BORDER | LBS_NOTIFY
		,10, 40, 380, 300
		, hUi, (HMENU)ID_LISTBOX_UnitSkillList,NULL, NULL);
	

	SendMessage(m_listSkill, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
	m_pUnit->FillSkillList(&m_listSkill);
	if (m_nUserSelect != -1)
	{
		SendMessage(m_listSkill, LB_SETCURSEL, m_nUserSelect, (WPARAM)0);
	}
	//SendMessage(m_listSkill, LB_ADDSTRING, 0, (LPARAM)_T(""));
}
void CUI_UnitDetailInfo::DrawUnit(HDC hdc)
{
	HBRUSH oldBrush;
	CString szText;
	HFONT hFont, oldFont;

	int imagePos = (int)m_pUnit->GetUnitName();
	
	if(m_imageBack.IsNull())
		m_imageBack.Load(_T("resource/UI/background.bmp"));
	m_imageBack.StretchBlt(hdc, 0, 30, 400, 470
		, 0, 0, 400, 470, SRCCOPY);
	if (m_phase == UnitInfoPhase::None)
	{
		RECT rcRect = { 110, 50, 350, 290 };
		DestroyWindow(m_listSkill);

		oldBrush = (HBRUSH)SelectObject(hdc, GetStockObject(NULL_BRUSH));
		Rectangle(hdc, 10, 40, 390, 200);
		Rectangle(hdc, 10, 210, 390, 490);
		//Rectangle(hdc, 20, 50, 120, 150);
		SetBkMode(hdc, TRANSPARENT);
		hFont = CreateFont(20, 10, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0,
			VARIABLE_PITCH | FF_ROMAN, _T("굴림"));
		oldFont = (HFONT)SelectObject(hdc, hFont);

		DrawText(hdc, m_pUnit->GetUnitDescription(), _tcslen(m_pUnit->GetUnitDescription()),
			&rcRect, DT_WORDBREAK);
		//TextOut(hdc, 110, 50, m_pUnit->GetUnitDescription(), _tcslen(m_pUnit->GetUnitDescription()));
		TextOut(hdc, 20, 220, _T("이름 : "), _tcslen(_T("이름 : ")));

		szText = m_pUnit->GetName();
		TextOut(hdc, 80, 220, szText, _tcslen(szText));

		szText.Format(_T("체력(HP) : %d/%d"), m_pUnit->GetHp(), m_pUnit->GetMaxHp());
		TextOut(hdc, 20, 250, szText, szText.GetLength());

		szText.Format(_T("마력(MP) : %d/%d"), m_pUnit->GetMp(), m_pUnit->GetMaxMp());
		TextOut(hdc, 20, 280, szText, szText.GetLength());

		szText.Format(_T("공격력 : %d"), m_pUnit->GetStrength());
		TextOut(hdc, 20, 310, szText, szText.GetLength());
		
		szText.Format(_T("주문력 : %d"), m_pUnit->GetIntelligence());
		TextOut(hdc, 20, 340, szText, szText.GetLength());
		
		szText.Format(_T("방어력 : %d"), m_pUnit->GetDefense());
		TextOut(hdc, 20, 370, szText, szText.GetLength());

		szText.Format(_T("방어력 : %d"), m_pUnit->GetDefense());
		TextOut(hdc, 20, 400, szText, szText.GetLength());

		szText.Format(_T("마항력 : %d"), m_pUnit->GetMagicDefense());
		TextOut(hdc, 20, 430, szText, szText.GetLength());

		szText.Format(_T("민첩성 : %d"), m_pUnit->GetAgility());
		TextOut(hdc, 20, 460, szText, szText.GetLength());
		
		
		m_unitImage.TransparentBlt(
			hdc, 0, 50, 90, 95,
			(imagePos % 9) * 90, (imagePos / 9) * 95, 90, 95, RGB(255, 0, 255));

		SelectObject(hdc, oldFont);
		DeleteObject(hFont);
		SelectObject(hdc, oldBrush);
	}
	else if (m_phase == UnitInfoPhase::Skill)
	{
		CreateSkillList();
		if (m_nUserSelect != -1)
		{
			SetBkMode(hdc, TRANSPARENT);
			hFont = CreateFont(20, 10, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0,
				VARIABLE_PITCH | FF_ROMAN, _T("굴림"));
			oldFont = (HFONT)SelectObject(hdc, hFont);

			//szText.Format(_T("%s"), m_szText);
			if (lstrcmp(m_szText, L"에이드") == 0)
			{
				szText.Format(_T("스킬 이름 : 에이드"));
				TextOut(hdc, 20, 320, szText, szText.GetLength());
				szText.Format(_T("스킬 종류 : 체력 회복"));
				TextOut(hdc, 20, 350, szText, szText.GetLength());
				szText.Format(_T("스킬 범위 : 단일 유닛"));
				TextOut(hdc, 20, 380, szText, szText.GetLength());
				szText.Format(_T("마나 소모량 : 5"));
				TextOut(hdc, 20, 410, szText, szText.GetLength());
			}
			else if (lstrcmp(m_szText, L"마나 에이드") == 0)
			{
				szText.Format(_T("스킬 이름 : 마나 에이드"));
				TextOut(hdc, 20, 320, szText, szText.GetLength());
				szText.Format(_T("스킬 종류 : 마력 회복"));
				TextOut(hdc, 20, 350, szText, szText.GetLength());
				szText.Format(_T("스킬 범위 : 단일 유닛"));
				TextOut(hdc, 20, 380, szText, szText.GetLength());
				szText.Format(_T("마나 소모량 : 10"));
				TextOut(hdc, 20, 410, szText, szText.GetLength());
			}
			else if (lstrcmp(m_szText, L"메르시") == 0)
			{
				szText.Format(_T("스킬 이름 : 메르시"));
				TextOut(hdc, 20, 320, szText, szText.GetLength());
				szText.Format(_T("스킬 종류 : 체력 회복"));
				TextOut(hdc, 20, 350, szText, szText.GetLength());
				szText.Format(_T("스킬 범위 : 인접 타일"));
				TextOut(hdc, 20, 380, szText, szText.GetLength());
				szText.Format(_T("마나 소모량 : 10"));
				TextOut(hdc, 20, 410, szText, szText.GetLength());
			}
			else if (lstrcmp(m_szText, L"레저렉션") == 0)
			{
				szText.Format(_T("스킬 이름 : 레저렉션"));
				TextOut(hdc, 20, 320, szText, szText.GetLength());
				szText.Format(_T("스킬 종류 : 유닛 부활"));
				TextOut(hdc, 20, 350, szText, szText.GetLength());
				szText.Format(_T("스킬 범위 : 단일 유닛"));
				TextOut(hdc, 20, 380, szText, szText.GetLength());
				szText.Format(_T("마나 소모량 : 15"));
				TextOut(hdc, 20, 410, szText, szText.GetLength());
			}
			else if (lstrcmp(m_szText, L"세크리파이스") == 0)
			{
				szText.Format(_T("스킬 이름 : 세크리파이스"));
				TextOut(hdc, 20, 320, szText, szText.GetLength());
				szText.Format(_T("스킬 종류 : 유닛 부활"));
				TextOut(hdc, 20, 350, szText, szText.GetLength());
				szText.Format(_T("스킬 범위 : 인접 타일"));
				TextOut(hdc, 20, 380, szText, szText.GetLength());
				szText.Format(_T("마나 소모량 : 30"));
				TextOut(hdc, 20, 410, szText, szText.GetLength());
			}
			else if (lstrcmp(m_szText, L"익스플로전") == 0)
			{
				szText.Format(_T("스킬 이름 : 익스플로전"));
				TextOut(hdc, 20, 320, szText, szText.GetLength());
				szText.Format(_T("스킬 종류 : 공격"));
				TextOut(hdc, 20, 350, szText, szText.GetLength());
				szText.Format(_T("스킬 범위 : 인접 타일"));
				TextOut(hdc, 20, 380, szText, szText.GetLength());
				szText.Format(_T("마나 소모량 : 10"));
				TextOut(hdc, 20, 410, szText, szText.GetLength());
			}
			else if (lstrcmp(m_szText, L"플레임버스트") == 0)
			{
				szText.Format(_T("스킬 이름 : 플레임버스트"));
				TextOut(hdc, 20, 320, szText, szText.GetLength());
				szText.Format(_T("스킬 종류 : 공격"));
				TextOut(hdc, 20, 350, szText, szText.GetLength());
				szText.Format(_T("스킬 범위 : 십자형"));
				TextOut(hdc, 20, 380, szText, szText.GetLength());
				szText.Format(_T("마나 소모량 : 20"));
				TextOut(hdc, 20, 410, szText, szText.GetLength());
			}
			else if (lstrcmp(m_szText, L"허리케인") == 0)
			{
				szText.Format(_T("스킬 이름 : 허리케인"));
				TextOut(hdc, 20, 320, szText, szText.GetLength());
				szText.Format(_T("스킬 종류 : 공격"));
				TextOut(hdc, 20, 350, szText, szText.GetLength());
				szText.Format(_T("스킬 범위 : 인접 타일"));
				TextOut(hdc, 20, 380, szText, szText.GetLength());
				szText.Format(_T("마나 소모량 : 10"));
				TextOut(hdc, 20, 410, szText, szText.GetLength());
			}
			else if (lstrcmp(m_szText, L"윈드블레스트") == 0)
			{
				szText.Format(_T("스킬 이름 : 윈드블레스트"));
				TextOut(hdc, 20, 320, szText, szText.GetLength());
				szText.Format(_T("스킬 종류 : 공격"));
				TextOut(hdc, 20, 350, szText, szText.GetLength());
				szText.Format(_T("스킬 범위 : 십자형"));
				TextOut(hdc, 20, 380, szText, szText.GetLength());
				szText.Format(_T("마나 소모량 : 20"));
				TextOut(hdc, 20, 410, szText, szText.GetLength());
			}
			else if (lstrcmp(m_szText, L"커스") == 0)
			{
				szText.Format(_T("스킬 이름 : 커스"));
				TextOut(hdc, 20, 320, szText, szText.GetLength());
				szText.Format(_T("스킬 종류 : 공격"));
				TextOut(hdc, 20, 350, szText, szText.GetLength());
				szText.Format(_T("스킬 범위 : 인접 타일"));
				TextOut(hdc, 20, 380, szText, szText.GetLength());
				szText.Format(_T("마나 소모량 : 10"));
				TextOut(hdc, 20, 410, szText, szText.GetLength());
			}
			else if (lstrcmp(m_szText, L"이블아이") == 0)
			{
				szText.Format(_T("스킬 이름 : 이블아이"));
				TextOut(hdc, 20, 320, szText, szText.GetLength());
				szText.Format(_T("스킬 종류 : 공격"));
				TextOut(hdc, 20, 350, szText, szText.GetLength());
				szText.Format(_T("스킬 범위 : 십자형"));
				TextOut(hdc, 20, 380, szText, szText.GetLength());
				szText.Format(_T("마나 소모량 : 20"));
				TextOut(hdc, 20, 410, szText, szText.GetLength());
			}
			else if (lstrcmp(m_szText, L"엣지") == 0)
			{
				szText.Format(_T("스킬 이름 : 엣지"));
				TextOut(hdc, 20, 320, szText, szText.GetLength());
				szText.Format(_T("스킬 종류 : 공격"));
				TextOut(hdc, 20, 350, szText, szText.GetLength());
				szText.Format(_T("스킬 범위 : 인접 타일"));
				TextOut(hdc, 20, 380, szText, szText.GetLength());
				szText.Format(_T("마나 소모량 : 10"));
				TextOut(hdc, 20, 410, szText, szText.GetLength());
			}
			else if (lstrcmp(m_szText, L"어스퀘이크") == 0)
			{
				szText.Format(_T("스킬 이름 : 어스퀘이크"));
				TextOut(hdc, 20, 320, szText, szText.GetLength());
				szText.Format(_T("스킬 종류 : 공격"));
				TextOut(hdc, 20, 350, szText, szText.GetLength());
				szText.Format(_T("스킬 범위 : 십자형"));
				TextOut(hdc, 20, 380, szText, szText.GetLength());
				szText.Format(_T("마나 소모량 : 20"));
				TextOut(hdc, 20, 410, szText, szText.GetLength());
			}
			else if (lstrcmp(m_szText, L"썬더") == 0)
			{
				szText.Format(_T("스킬 이름 : 썬더"));
				TextOut(hdc, 20, 320, szText, szText.GetLength());
				szText.Format(_T("스킬 종류 : 공격"));
				TextOut(hdc, 20, 350, szText, szText.GetLength());
				szText.Format(_T("스킬 범위 : 인접 타일"));
				TextOut(hdc, 20, 380, szText, szText.GetLength());
				szText.Format(_T("마나 소모량 : 10"));
				TextOut(hdc, 20, 410, szText, szText.GetLength());
			}
			else if (lstrcmp(m_szText, L"썬더프레어") == 0)
			{
				szText.Format(_T("스킬 이름 : 썬더프레어"));
				TextOut(hdc, 20, 320, szText, szText.GetLength());
				szText.Format(_T("스킬 종류 : 공격"));
				TextOut(hdc, 20, 350, szText, szText.GetLength());
				szText.Format(_T("스킬 범위 : 십자형"));
				TextOut(hdc, 20, 380, szText, szText.GetLength());
				szText.Format(_T("마나 소모량 : 20"));
				TextOut(hdc, 20, 410, szText, szText.GetLength());
			}
			SelectObject(hdc, oldFont);
			DeleteObject(hFont);
		}
	}
}
CUI_UnitDetailInfo * CUI_UnitDetailInfo::GetInstance(HWND hWnd, HINSTANCE hInstance)
{
	if (instance == NULL)
	{
		instance = new CUI_UnitDetailInfo(hWnd, hInstance);
	}
	return instance;
}
CUI_UnitDetailInfo * CUI_UnitDetailInfo::GetInstance()
{
	return instance;
}

LRESULT CALLBACK UI_UnitDetailInfo_Proc(HWND hWnd, UINT iMsg,
	WPARAM wParam, LPARAM lParam)
{
	HDC hdc, bufferDC; //화면에 출력할 hdc, 출력하기 전까지 저장할 변수 bufferDC
	PAINTSTRUCT ps;
	static RECT rect;
	static CUI_UnitDetailInfo* self;
	static HBITMAP		hBmp;
	static TCHAR text[128];
	switch (iMsg)
	{
	case WM_CREATE:
		self = self->GetInstance();
		rect = self->GetRect();
		break;
	case WM_COMMAND:
		int userSelect;
		
		
		userSelect = -1;
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON_UnitStat:
			self->GetInstance()->SetPhase(UnitInfoPhase::None);
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		case IDC_BUTTON_UnitSkill:
			self->GetInstance()->SetPhase(UnitInfoPhase::Skill);
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		case ID_LISTBOX_UnitSkillList:
			switch (HIWORD(wParam)) 
			{
			case LBN_SELCHANGE:
				userSelect = SendMessage(self->GetList(), LB_GETCURSEL, 0, 0);
				self->SetUserSelect(userSelect);
				SendMessage(self->GetList(), LB_GETTEXT, userSelect, (LPARAM)text);
				self->SetText(text);
				InvalidateRect(hWnd, NULL, FALSE);
				break;
			}
			break;
		}
		//
		break;
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