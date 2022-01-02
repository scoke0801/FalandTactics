#include "stdafx.h"
#include "UI_UnitDeatilInfo.h"

CUI_UnitDetailInfo* CUI_UnitDetailInfo::instance = NULL;
CUI_UnitDetailInfo::CUI_UnitDetailInfo(HWND hWnd, HINSTANCE hInstance)
	:CUI(hWnd, hInstance)
{
	szWindowClass = _T("UnitDetailInfo_Class");
	szWindowTitle = _T("���� ����_");

//RegisterUI();

	m_unitImage.Load(_T("resource/Unit/unit_all.png"));
	m_backImage.Load(_T("resource/UI/unit_info_background.png"));
	m_hpMpImage.Load(_T("resource/UI/HP_MP.png"));

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
			CS_HREDRAW	//Ŭ���̾�Ʈ�� ���̸� �����ϸ� �ٽ� �׸����� �մϴ�. 
			| CS_VREDRAW	//Ŭ���̾�Ʈ�� ���̸� �����ϸ� �ٽ� �׸����� �մϴ�.
			| CS_DBLCLKS	//�ش� �������α׷��� ���� Ŭ���� �����ϵ��� �մϴ�.
			;
		wcex.lpfnWndProc = UI_UnitDetailInfo_Proc;
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

void CUI_UnitDetailInfo::MakeUI()
{
	if (hUi)
	{
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
		| WS_CLIPSIBLINGS		//���ϵ峢�� ��ȣ ��ģ ������ �׸��� �������� ����
		| WS_CLIPCHILDREN		//���ϵ尡 ��ġ�� ������ �׸��� �������� ����
		, m_rcRect.right / 2 - 200	// ������ ���� �� x ��ǥ 
		, m_rcRect.bottom / 2 - 250	// ������ ���� �� y ��ǥ 
		, 400			        // ������ ��
		, 500			        // ������ ����
		, hWnd			        //�θ� ������
		, (HMENU)NULL		    //�޴� �ڵ�
		, hInstance		        //�ν��Ͻ� �ڵ�
		, NULL		            //�߰� �Ķ����
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

	m_buttonStat = CreateWindow(_T("button"), _T("�ɷ�"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP,
		0, 0
		, 200, 30,
		hUi, (HMENU)IDC_BUTTON_UnitStat, hInstance, NULL);
	
	image.Load(_T("resource/UI/stat.png"));
	hBmp = image.Detach();
	SendMessage(m_buttonStat, BM_SETIMAGE, 0, (LPARAM)hBmp);

	m_buttonSkill = CreateWindow(_T("button"), _T("��ų"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP,
		200, 0
		, 200, 30,
		hUi, (HMENU)IDC_BUTTON_UnitSkill, hInstance, NULL);
	image.Load(_T("resource/UI/skill.png"));
	hBmp = image.Detach();
	SendMessage(m_buttonSkill, BM_SETIMAGE, 0, (LPARAM)hBmp);
}

void CUI_UnitDetailInfo::CreateSkillList()
{
	HFONT hFont;
	hFont = CreateFont(30, 10, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0,
		VARIABLE_PITCH | FF_ROMAN, _T("����"));

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
		m_imageBack.Load(_T("resource/UI/background.png"));
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
			VARIABLE_PITCH | FF_ROMAN, _T("����"));
		oldFont = (HFONT)SelectObject(hdc, hFont);

		DrawText(hdc, m_pUnit->GetUnitDescription(), _tcslen(m_pUnit->GetUnitDescription()),
			&rcRect, DT_WORDBREAK);
		//TextOut(hdc, 110, 50, m_pUnit->GetUnitDescription(), _tcslen(m_pUnit->GetUnitDescription()));
		TextOut(hdc, 20, 220, _T("�̸� : "), _tcslen(_T("�̸� : ")));

		szText = m_pUnit->GetName();
		TextOut(hdc, 80, 220, szText, _tcslen(szText));

		szText.Format(_T("ü��(HP) : %d/%d"), m_pUnit->GetHp(), m_pUnit->GetMaxHp());
		TextOut(hdc, 20, 250, szText, szText.GetLength());

		szText.Format(_T("����(MP) : %d/%d"), m_pUnit->GetMp(), m_pUnit->GetMaxMp());
		TextOut(hdc, 20, 280, szText, szText.GetLength());

		szText.Format(_T("���ݷ� : %d"), m_pUnit->GetStrength());
		TextOut(hdc, 20, 310, szText, szText.GetLength());
		
		szText.Format(_T("�ֹ��� : %d"), m_pUnit->GetIntelligence());
		TextOut(hdc, 20, 340, szText, szText.GetLength());
		
		szText.Format(_T("���� : %d"), m_pUnit->GetDefense());
		TextOut(hdc, 20, 370, szText, szText.GetLength());

		szText.Format(_T("���� : %d"), m_pUnit->GetDefense());
		TextOut(hdc, 20, 400, szText, szText.GetLength());

		szText.Format(_T("���׷� : %d"), m_pUnit->GetMagicDefense());
		TextOut(hdc, 20, 430, szText, szText.GetLength());

		szText.Format(_T("��ø�� : %d"), m_pUnit->GetAgility());
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
				VARIABLE_PITCH | FF_ROMAN, _T("����"));
			oldFont = (HFONT)SelectObject(hdc, hFont);

			//szText.Format(_T("%s"), m_szText);
			if (lstrcmp(m_szText, L"���̵�") == 0)
			{
				szText.Format(_T("��ų �̸� : ���̵�"));
				TextOut(hdc, 20, 320, szText, szText.GetLength());
				szText.Format(_T("��ų ���� : ü�� ȸ��"));
				TextOut(hdc, 20, 350, szText, szText.GetLength());
				szText.Format(_T("��ų ���� : ���� ����"));
				TextOut(hdc, 20, 380, szText, szText.GetLength());
				szText.Format(_T("���� �Ҹ� : 5"));
				TextOut(hdc, 20, 410, szText, szText.GetLength());
			}
			else if (lstrcmp(m_szText, L"���� ���̵�") == 0)
			{
				szText.Format(_T("��ų �̸� : ���� ���̵�"));
				TextOut(hdc, 20, 320, szText, szText.GetLength());
				szText.Format(_T("��ų ���� : ���� ȸ��"));
				TextOut(hdc, 20, 350, szText, szText.GetLength());
				szText.Format(_T("��ų ���� : ���� ����"));
				TextOut(hdc, 20, 380, szText, szText.GetLength());
				szText.Format(_T("���� �Ҹ� : 10"));
				TextOut(hdc, 20, 410, szText, szText.GetLength());
			}
			else if (lstrcmp(m_szText, L"�޸���") == 0)
			{
				szText.Format(_T("��ų �̸� : �޸���"));
				TextOut(hdc, 20, 320, szText, szText.GetLength());
				szText.Format(_T("��ų ���� : ü�� ȸ��"));
				TextOut(hdc, 20, 350, szText, szText.GetLength());
				szText.Format(_T("��ų ���� : ���� Ÿ��"));
				TextOut(hdc, 20, 380, szText, szText.GetLength());
				szText.Format(_T("���� �Ҹ� : 10"));
				TextOut(hdc, 20, 410, szText, szText.GetLength());
			}
			else if (lstrcmp(m_szText, L"��������") == 0)
			{
				szText.Format(_T("��ų �̸� : ��������"));
				TextOut(hdc, 20, 320, szText, szText.GetLength());
				szText.Format(_T("��ų ���� : ���� ��Ȱ"));
				TextOut(hdc, 20, 350, szText, szText.GetLength());
				szText.Format(_T("��ų ���� : ���� ����"));
				TextOut(hdc, 20, 380, szText, szText.GetLength());
				szText.Format(_T("���� �Ҹ� : 15"));
				TextOut(hdc, 20, 410, szText, szText.GetLength());
			}
			else if (lstrcmp(m_szText, L"��ũ�����̽�") == 0)
			{
				szText.Format(_T("��ų �̸� : ��ũ�����̽�"));
				TextOut(hdc, 20, 320, szText, szText.GetLength());
				szText.Format(_T("��ų ���� : ���� ��Ȱ"));
				TextOut(hdc, 20, 350, szText, szText.GetLength());
				szText.Format(_T("��ų ���� : ���� Ÿ��"));
				TextOut(hdc, 20, 380, szText, szText.GetLength());
				szText.Format(_T("���� �Ҹ� : 30"));
				TextOut(hdc, 20, 410, szText, szText.GetLength());
			}
			else if (lstrcmp(m_szText, L"�ͽ��÷���") == 0)
			{
				szText.Format(_T("��ų �̸� : �ͽ��÷���"));
				TextOut(hdc, 20, 320, szText, szText.GetLength());
				szText.Format(_T("��ų ���� : ����"));
				TextOut(hdc, 20, 350, szText, szText.GetLength());
				szText.Format(_T("��ų ���� : ���� Ÿ��"));
				TextOut(hdc, 20, 380, szText, szText.GetLength());
				szText.Format(_T("���� �Ҹ� : 10"));
				TextOut(hdc, 20, 410, szText, szText.GetLength());
			}
			else if (lstrcmp(m_szText, L"�÷��ӹ���Ʈ") == 0)
			{
				szText.Format(_T("��ų �̸� : �÷��ӹ���Ʈ"));
				TextOut(hdc, 20, 320, szText, szText.GetLength());
				szText.Format(_T("��ų ���� : ����"));
				TextOut(hdc, 20, 350, szText, szText.GetLength());
				szText.Format(_T("��ų ���� : ������"));
				TextOut(hdc, 20, 380, szText, szText.GetLength());
				szText.Format(_T("���� �Ҹ� : 20"));
				TextOut(hdc, 20, 410, szText, szText.GetLength());
			}
			else if (lstrcmp(m_szText, L"�㸮����") == 0)
			{
				szText.Format(_T("��ų �̸� : �㸮����"));
				TextOut(hdc, 20, 320, szText, szText.GetLength());
				szText.Format(_T("��ų ���� : ����"));
				TextOut(hdc, 20, 350, szText, szText.GetLength());
				szText.Format(_T("��ų ���� : ���� Ÿ��"));
				TextOut(hdc, 20, 380, szText, szText.GetLength());
				szText.Format(_T("���� �Ҹ� : 10"));
				TextOut(hdc, 20, 410, szText, szText.GetLength());
			}
			else if (lstrcmp(m_szText, L"�������Ʈ") == 0)
			{
				szText.Format(_T("��ų �̸� : �������Ʈ"));
				TextOut(hdc, 20, 320, szText, szText.GetLength());
				szText.Format(_T("��ų ���� : ����"));
				TextOut(hdc, 20, 350, szText, szText.GetLength());
				szText.Format(_T("��ų ���� : ������"));
				TextOut(hdc, 20, 380, szText, szText.GetLength());
				szText.Format(_T("���� �Ҹ� : 20"));
				TextOut(hdc, 20, 410, szText, szText.GetLength());
			}
			else if (lstrcmp(m_szText, L"Ŀ��") == 0)
			{
				szText.Format(_T("��ų �̸� : Ŀ��"));
				TextOut(hdc, 20, 320, szText, szText.GetLength());
				szText.Format(_T("��ų ���� : ����"));
				TextOut(hdc, 20, 350, szText, szText.GetLength());
				szText.Format(_T("��ų ���� : ���� Ÿ��"));
				TextOut(hdc, 20, 380, szText, szText.GetLength());
				szText.Format(_T("���� �Ҹ� : 10"));
				TextOut(hdc, 20, 410, szText, szText.GetLength());
			}
			else if (lstrcmp(m_szText, L"�̺����") == 0)
			{
				szText.Format(_T("��ų �̸� : �̺����"));
				TextOut(hdc, 20, 320, szText, szText.GetLength());
				szText.Format(_T("��ų ���� : ����"));
				TextOut(hdc, 20, 350, szText, szText.GetLength());
				szText.Format(_T("��ų ���� : ������"));
				TextOut(hdc, 20, 380, szText, szText.GetLength());
				szText.Format(_T("���� �Ҹ� : 20"));
				TextOut(hdc, 20, 410, szText, szText.GetLength());
			}
			else if (lstrcmp(m_szText, L"����") == 0)
			{
				szText.Format(_T("��ų �̸� : ����"));
				TextOut(hdc, 20, 320, szText, szText.GetLength());
				szText.Format(_T("��ų ���� : ����"));
				TextOut(hdc, 20, 350, szText, szText.GetLength());
				szText.Format(_T("��ų ���� : ���� Ÿ��"));
				TextOut(hdc, 20, 380, szText, szText.GetLength());
				szText.Format(_T("���� �Ҹ� : 10"));
				TextOut(hdc, 20, 410, szText, szText.GetLength());
			}
			else if (lstrcmp(m_szText, L"�����ũ") == 0)
			{
				szText.Format(_T("��ų �̸� : �����ũ"));
				TextOut(hdc, 20, 320, szText, szText.GetLength());
				szText.Format(_T("��ų ���� : ����"));
				TextOut(hdc, 20, 350, szText, szText.GetLength());
				szText.Format(_T("��ų ���� : ������"));
				TextOut(hdc, 20, 380, szText, szText.GetLength());
				szText.Format(_T("���� �Ҹ� : 20"));
				TextOut(hdc, 20, 410, szText, szText.GetLength());
			}
			else if (lstrcmp(m_szText, L"���") == 0)
			{
				szText.Format(_T("��ų �̸� : ���"));
				TextOut(hdc, 20, 320, szText, szText.GetLength());
				szText.Format(_T("��ų ���� : ����"));
				TextOut(hdc, 20, 350, szText, szText.GetLength());
				szText.Format(_T("��ų ���� : ���� Ÿ��"));
				TextOut(hdc, 20, 380, szText, szText.GetLength());
				szText.Format(_T("���� �Ҹ� : 10"));
				TextOut(hdc, 20, 410, szText, szText.GetLength());
			}
			else if (lstrcmp(m_szText, L"���������") == 0)
			{
				szText.Format(_T("��ų �̸� : ���������"));
				TextOut(hdc, 20, 320, szText, szText.GetLength());
				szText.Format(_T("��ų ���� : ����"));
				TextOut(hdc, 20, 350, szText, szText.GetLength());
				szText.Format(_T("��ų ���� : ������"));
				TextOut(hdc, 20, 380, szText, szText.GetLength());
				szText.Format(_T("���� �Ҹ� : 20"));
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
	HDC hdc, bufferDC; //ȭ�鿡 ����� hdc, ����ϱ� ������ ������ ���� bufferDC
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