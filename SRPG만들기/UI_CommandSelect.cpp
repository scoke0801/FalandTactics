#include "stdafx.h"
#include "UI_CommandSelect.h"

CUI_CommandSelect* CUI_CommandSelect::instance = NULL;
CUI_CommandSelect::CUI_CommandSelect(HWND hWnd, HINSTANCE hInstance, CUnit* unit)
	:CUI(hWnd, hInstance)
{
	szWindowClass = _T("CommandSelect_Class");
	szWindowTitle = _T("�ൿ ����");

	m_pUnit = unit;
	//RegisterUI();

	m_buttonShow = NULL;
	m_buttonTurnEnd = NULL;
	m_buttonSystem = NULL;

	m_rcUI = { 0,0,0,0 };
	UI_DetailSelect = CUI_DetailSelect::GetInstance(hWnd, hInstance);
}
CUI_CommandSelect::~CUI_CommandSelect()
{

}
void CUI_CommandSelect::OnUpdate()
{
	InvalidateRect(hUi, &m_rcRect, FALSE);
}
void CUI_CommandSelect::RegisterUI()
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
		wcex.lpfnWndProc = UI_CommandSelect_Proc;
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

void CUI_CommandSelect::MakeUI()
{
	if (hUi)
	{
		ShowWindow(hUi, SW_SHOW);
		ArrangeUiSize();
		CreateButton();
		return;
	}
	hUi = CreateWindow(
		szWindowClass           // ���ϵ� ������ Ŭ���� �̸� 
		, szWindowTitle         // ������ Ÿ��Ʋ 
		, WS_CHILD
		| WS_SYSMENU
		| WS_VISIBLE
	//	| WS_CLIPSIBLINGS			//���ϵ峢�� ��ȣ ��ģ ������ �׸��� �������� ����
	//	| WS_CLIPCHILDREN			//���ϵ尡 ��ġ�� ������ �׸��� �������� ����
		, m_ptPos.x					// ������ ���� �� x ��ǥ 
		, m_ptPos.y					// ������ ���� �� y ��ǥ 
		, 200					    // ������ ��
		, 90					    // ������ ����
		, hWnd					    //�θ� ������
		, (HMENU)NULL			    //�޴� �ڵ�
		, hInstance				    //�ν��Ͻ� �ڵ�
		, NULL					    //�߰� �Ķ����
		);
	GetClientRect(hWnd, &m_rcUI);
	ArrangeUiSize();
	CreateButton();
	::ShowWindow(hUi, SW_SHOW);

}
void CUI_CommandSelect::DestroyUI()
{
	if (hUi)
	{
		m_pUnit = NULL;
		::DestroyWindow(hUi);
		hUi = NULL;
	}
}
void CUI_CommandSelect::HideUI()
{
	if (hUi)
	{
		m_pUnit = NULL;
		UI_DetailSelect->HideUI();
		::ShowWindow(hUi, SW_HIDE);
	}
}

void CUI_CommandSelect::SetUnit(CUnit* unit)
{
	m_pUnit = unit;
	if (m_pUnit != NULL)
	{
		if (unit->GetSkillNum() > 0 && unit->GetCanAttack())
		{
			/*if (m_ptPos.x + 200 > m_rcRect.right)
				m_ptPos.x -= (m_rcRect.right - m_ptPos.x);
			if (m_ptPos.y + 120 > m_rcRect.bottom)
				m_ptPos.y -= (m_rcRect.bottom - m_ptPos.y);*/
			//MoveWindow(hUi, m_ptPos.x, m_ptPos.y, 200, 120, TRUE);
			ArrangeUiSize();
			CreateButton(1);
		}
		else
		{
		/*	if (m_ptPos.x + 200 > m_rcRect.right)
				m_ptPos.x -= (m_rcRect.right - m_ptPos.x);
			if (m_ptPos.y + 90 > m_rcRect.bottom)
				m_ptPos.y -= (m_rcRect.bottom - m_ptPos.y);*/
			//MoveWindow(hUi, m_ptPos.x, m_ptPos.y, 200, 90, TRUE);
		}
	}
	else
	{
	/*	if (m_ptPos.x + 200 > m_rcRect.right)
			m_ptPos.x -= (m_rcRect.right - m_ptPos.x );
		if (m_ptPos.y + 90 > m_rcRect.bottom)
			m_ptPos.y -= (m_rcRect.bottom - m_ptPos.y );*/
		m_pUnit = NULL;
		//MoveWindow(hUi, m_ptPos.x, m_ptPos.y, 200, 90, TRUE);
	}
	//CreateButton();
}

void CUI_CommandSelect::ArrangeUiSize()
{
	if (m_ptPos.x + 200 >= m_rcRect.right)
	{
		MoveWindow(hUi, m_ptPos.x - (m_ptPos.x + 200 - m_rcRect.right), m_ptPos.y, 200, 60, FALSE);
		m_ptPos.x -= (m_ptPos.x + 200 - m_rcRect.right);
	}
	if (m_pUnit != NULL)
	{
		if (m_pUnit->GetSkillNum() != 0 && m_pUnit->GetUnitTeam() != UnitTeam::West)
		{
			if (m_ptPos.y + 120 >= m_rcRect.bottom)
			{
				MoveWindow(hUi, m_ptPos.x, m_ptPos.y - (m_ptPos.y + 120 - m_rcRect.bottom)
					, 200, 120, FALSE);
				m_ptPos.y -= (m_ptPos.y + 120 - m_rcRect.bottom);
				return;
			}
			else
			{
				MoveWindow(hUi, m_ptPos.x, m_ptPos.y 
					, 200, 120, FALSE);
				return;
			}
		}
	}
	else
	{
		if (m_ptPos.y + 90 >= m_rcRect.bottom)
		{
			MoveWindow(hUi, m_ptPos.x, m_ptPos.y - (m_ptPos.y + 90 - m_rcRect.bottom)
				, 200, 90, FALSE);
			m_ptPos.y -= (m_ptPos.y + 90 - m_rcRect.bottom);
			return;
		}

	}
	MoveWindow(hUi, m_ptPos.x, m_ptPos.y
		, 200, 90, FALSE);
}

void CUI_CommandSelect::CreateButton(int division)
{
	RECT rcUI;
	HBITMAP hBmp;
	CImage image;
	int height = 0;

	DestroyWindow(m_buttonShow);
	DestroyWindow(m_buttonTurnEnd);
	DestroyWindow(m_buttonSystem);
	DestroyWindow(m_buttonUseSkill);

	GetClientRect(hUi, &rcUI);
	if (rcUI.top != 0)
	{
		rcUI = { 0,0,200,90 };
	}
	if (m_pUnit != NULL)
	{
		if (m_pUnit->GetSkillNum() > 0 && m_pUnit->GetCanAttack() && m_pUnit->GetUnitTeam() != UnitTeam::West)
		{
			CString szText;
			szText.Format(_T("%s�� ��ų���"), m_pUnit->GetName());
			m_buttonUseSkill = CreateWindow(_T("button"), szText,
				WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP,
				0, 0, 200, 30,
				hUi, (HMENU)IDC_BUTTON_UseSkill, hInstance, NULL);

			image.Load(_T("resource/Button/UseSkill_.png"));
			hBmp = image.Detach();
			SendMessage(m_buttonUseSkill, BM_SETIMAGE, 0, (LPARAM)hBmp);
			++height;
		}
	}
	m_buttonShow = CreateWindow(_T("button"), _T("   ǥ��                >"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP
		, 0, height * 30
		, 200, 30,
		hUi, (HMENU)IDC_BUTTON_Show, hInstance, NULL);

	image.Load(_T("resource/Button/Show_.png"));
	hBmp = image.Detach();
	SendMessage(m_buttonShow, BM_SETIMAGE, 0, (LPARAM)hBmp);
	++height;
	//SendMessage(m_buttonShow, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
	
	m_buttonTurnEnd = CreateWindow(_T("button"), _T("   �� ����               "),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP,
		0, height*30
		, 200, 30,
		hUi, (HMENU)IDC_BUTTON_TurnEnd, hInstance, NULL);
	
	image.Load(_T("resource/Button/TurnEnd_.png"));
	hBmp = image.Detach();
	SendMessage(m_buttonTurnEnd, BM_SETIMAGE, 0, (LPARAM)hBmp);
	++height;

	m_buttonSystem = CreateWindow(_T("button"), _T("   �ý���             >"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP,
		0, height * 30
		, 200, 30,
		hUi, (HMENU)IDC_BUTTON_System, hInstance, NULL);
	
	image.Load(_T("resource/Button/System_.png"));
	hBmp = image.Detach();
	SendMessage(m_buttonSystem, BM_SETIMAGE, 0, (LPARAM)hBmp);
}

CUI_CommandSelect * CUI_CommandSelect::GetInstance(HWND hWnd, HINSTANCE hInstance, CUnit* unit)
{
	if (instance == NULL)
	{
		instance = new CUI_CommandSelect(hWnd, hInstance, unit);
	}
	return instance;
}
CUI_CommandSelect * CUI_CommandSelect::GetInstance()
{
	return instance;
}

LRESULT CALLBACK UI_CommandSelect_Proc(HWND hWnd, UINT iMsg,
	WPARAM wParam, LPARAM lParam)
{
	HDC hdc, bufferDC; //ȭ�鿡 ����� hdc, ����ϱ� ������ ������ ���� bufferDC
	PAINTSTRUCT ps;
	static RECT rect, rcUI;
	static CUI_CommandSelect* self;
	static HBITMAP		hBmp;

	switch (iMsg)
	{
	case WM_CREATE:
		self = self->GetInstance();
		rect = self->GetRect();
		::GetClientRect(hWnd, &rcUI);
		break;
	case WM_ERASEBKGND:
		InvalidateRect(hWnd, NULL, FALSE);
		break;
	case WM_LBUTTONDOWN:

		break;
	case WM_RBUTTONDOWN:
		CUI_DetailSelect::GetInstance()->DestroyUI();
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON_Show:
			CUI_DetailSelect::GetInstance()->SetPhase(DetailSelectPhase::Show);
			CUI_DetailSelect::GetInstance()->SetUnit(self->GetUnit());
			CUI_DetailSelect::GetInstance()->SetPos(POINT{ self->GetPos().x + 200, self->GetPos().y + rcUI.bottom - 90 });
			CUI_DetailSelect::GetInstance()->MakeUI();
			//CUI_UnitInfo::GetInstance()->ReDraw();
			break;
		case IDC_BUTTON_System:
			CUI_DetailSelect::GetInstance()->SetPhase(DetailSelectPhase::System);
			CUI_DetailSelect::GetInstance()->SetUnit(NULL);
			CUI_DetailSelect::GetInstance()->SetPos(POINT{ self->GetPos().x + 200, self->GetPos().y + rcUI.bottom - 30 });
			CUI_DetailSelect::GetInstance()->MakeUI();
			//CUI_UnitInfo::GetInstance()->ReDraw();
			break;
		case IDC_BUTTON_TurnEnd:
			//self->GetParent()->NewTurn();

			self->GetParent()->SetPhase(NoticePhase::EnemyPhase);
			CUI_Notice::GetInstance()->Update(NoticePhase::MoveNotice);
			CUI_UnitInfo::GetInstance()->HideUI();
			CUI_Notice::GetInstance()->HideUI();

			self->DestroyUI();
			CUI_DetailSelect::GetInstance()->DestroyUI();

			DestroyWindow(hWnd);
			self->GetParent()->SetCommandSelecting(FALSE);
			break;
		case IDC_BUTTON_UseSkill:
			CUI_DetailSelect::GetInstance()->SetPhase(DetailSelectPhase::Skill);
			CUI_DetailSelect::GetInstance()->SetPos(POINT{ self->GetPos().x + 200, self->GetPos().y + rcUI.bottom - 90});
			CUI_DetailSelect::GetInstance()->SetUnit(self->GetUnit());
			CUI_DetailSelect::GetInstance()->MakeUI();
			
			//CUI_UnitInfo::GetInstance()->ReDraw();
			break;
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);	
		bufferDC = CreateCompatibleDC(hdc);//hdc�� ȣȯ�Ǵ� bufferDC����, ������۸�
		hBmp = CreateBitmap(rect.right, rect.bottom, 1, 32, NULL);
		::SelectObject(bufferDC, hBmp);
		::FillRect(bufferDC, &rect, (HBRUSH)::GetStockObject(LTGRAY_BRUSH));
		//Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
		::SetBkMode(hdc, TRANSPARENT);

		//self->OnDraw(bufferDC);
		
		BitBlt(hdc, rect.left, rect.top, rect.right, rect.bottom,
			bufferDC, rect.left, rect.top, SRCCOPY);//bufferDC�� �ִ� ������ hdc�� �Ű� �׸�
		//self->DrawUnit(hdc);
		::EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		break;
	}
	return ::DefMDIChildProc(hWnd, iMsg, wParam, lParam);
}