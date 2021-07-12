#include "stdafx.h"
#include "UI_DetailSelect.h"

CUI_DetailSelect* CUI_DetailSelect::instance = NULL;
CUI_DetailSelect::CUI_DetailSelect(HWND hWnd, HINSTANCE hInstance)
	:CUI(hWnd, hInstance)
{
	szWindowClass = _T("Detail_Class");
	szWindowTitle = _T("�ൿ ����");

	//RegisterUI();

	m_buttonUnitList = NULL;
	m_buttonClearCondition = NULL;
	m_buttonGameEnd = NULL;
	m_buttonStageChange = NULL;

	m_pUnit = NULL;
}
CUI_DetailSelect::~CUI_DetailSelect()
{

}
void CUI_DetailSelect::OnUpdate()
{
	InvalidateRect(hUi, &m_rcRect, FALSE);
}
void CUI_DetailSelect::RegisterUI()
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
		wcex.lpfnWndProc = UI_DetailSelect_Proc;
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

void CUI_DetailSelect::MakeUI()
{
	if (hUi)
	{
		CUI_UnitInfo::GetInstance()->ReDraw();
		ShowWindow(hUi, SW_SHOW);
		//EnableWindow(hUi, TRUE);
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
		, 60					    // ������ ����
		, hWnd					    //�θ� ������
		, (HMENU)NULL			    //�޴� �ڵ�
		, hInstance				    //�ν��Ͻ� �ڵ�
		, NULL					    //�߰� �Ķ����
		);
	ArrangeUiSize();
	CreateButton();
	
	::ShowWindow(hUi, SW_SHOW);
}
void CUI_DetailSelect::DestroyUI()
{
	if (hUi)
	{
		::DestroyWindow(hUi);
		hUi = NULL;
	}
}
void CUI_DetailSelect::HideUI()
{
	if (hUi)
	{
		::ShowWindow(hUi, SW_HIDE);
	}
}

void CUI_DetailSelect::ArrangeUiSize()
{
	int height = 60;
	if (m_phase == DetailSelectPhase::Show)
	{	
		if (m_pUnit == NULL)
		{
			MoveWindow(hUi, m_ptPos.x, m_ptPos.y, 200, 30, FALSE);
			if (m_ptPos.y + 30 >= m_rcRect.bottom)
			{
				MoveWindow(hUi, m_ptPos.x, m_ptPos.y - (m_ptPos.y + 30 - m_rcRect.bottom)
					, 200, 30, FALSE);
			}
			height = 30;
		}
		else
		{
			MoveWindow(hUi, m_ptPos.x, m_ptPos.y, 200, 60, FALSE);
			if (m_ptPos.y + 60 >= m_rcRect.bottom)
			{
				MoveWindow(hUi, m_ptPos.x, m_ptPos.y - (m_ptPos.y + 60 - m_rcRect.bottom)
					, 200, 60, FALSE);
			}
			height = 60;
		}
	}
	else if (m_phase == DetailSelectPhase::Skill)
	{
		if (m_pUnit != NULL)
		{
			int num = m_pUnit->GetSkillNum();
			
			if (m_ptPos.y + 30 * num >= m_rcRect.bottom)
			{
				MoveWindow(hUi, m_ptPos.x, m_ptPos.y - (m_ptPos.y + 30 * num - m_rcRect.bottom)
					, 200, 30 * num, FALSE);
			}
			else
				MoveWindow(hUi, m_ptPos.x, m_ptPos.y, 200, 30 * num, FALSE);
			height = 30 * num;
		}
	}
	else if (m_phase == DetailSelectPhase::System)
	{
		MoveWindow(hUi, m_ptPos.x, m_ptPos.y, 200, 60, FALSE);
		if (m_ptPos.y + 60 >= m_rcRect.bottom)
		{
			MoveWindow(hUi, m_ptPos.x, m_ptPos.y - (m_ptPos.y + 60 - m_rcRect.bottom)
				, 200, 60, FALSE);
		}
		height = 60;
	}
	if (m_ptPos.x + 200 >= m_rcRect.right)
	{
		MoveWindow(hUi, m_ptPos.x - (m_ptPos.x + 200 - m_rcRect.right), m_ptPos.y, 200, height, FALSE);
		::EnableWindow(CUI_CommandSelect::GetInstance()->GetThis(), FALSE);
	}
	else
		::EnableWindow(CUI_CommandSelect::GetInstance()->GetThis(), TRUE);
}

void CUI_DetailSelect::CreateButton()
{
	CImage image;
	HBITMAP hBmp;

	DestroyWindow(m_buttonUnitList);
	DestroyWindow(m_buttonClearCondition);
	DestroyWindow(m_buttonStageChange);
	DestroyWindow(m_buttonGameEnd);
	for (int i = 0; i < (int)m_buttonSkill.size(); ++i)
		DestroyWindow(m_buttonSkill[i]);
	m_buttonSkill.clear();

	/*if (m_ptPos.x + 200 > m_rcRect.right)
	{
		m_ptPos.x -= (m_rcRect.right - m_ptPos.x + 200);
		MoveWindow(hUi, m_ptPos.x, m_ptPos.y, 200, 60, FALSE);
	}*/

	if (m_phase == DetailSelectPhase::Show)
	{
		int height = 0;
		if (m_pUnit != NULL)
		{
			m_buttonUnitList = CreateWindow(_T("button"), _T("���� �϶�"),
				WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP,
				0, 0, 200, 30,
				hUi, (HMENU)IDC_BUTTON_UnitList, hInstance, NULL);
			image.Load(_T("resource/Button/UnitList.bmp"));
			hBmp = image.Detach();
			SendMessage(m_buttonUnitList, BM_SETIMAGE, 0, (LPARAM)hBmp);
			height++;
		}
		m_buttonClearCondition = CreateWindow(_T("button"), _T("Ŭ���� ����"),
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP,
			0, 30 * height, 200, 30,
			hUi, (HMENU)IDC_BUTTON_ClearCondition, hInstance, NULL);
		image.Load(_T("resource/Button/ClearCondition.bmp"));
		hBmp = image.Detach();
		SendMessage(m_buttonClearCondition, BM_SETIMAGE, 0, (LPARAM)hBmp);

		if(m_pUnit == NULL)
		{
			//MoveWindow(hUi, m_ptPos.x, m_ptPos.y, 200, 30, FALSE);
		}
		
	}
	else if (m_phase == DetailSelectPhase::System)
	{
		m_buttonStageChange = CreateWindow(_T("button"), _T("�������� ��ȯ"),
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP,
			0, 0, 200, 30,
			hUi, (HMENU)IDC_BUTTON_StageChange, hInstance, NULL);
		image.Load(_T("resource/Button/StageChange.bmp"));
		hBmp = image.Detach();
		SendMessage(m_buttonStageChange, BM_SETIMAGE, 0, (LPARAM)hBmp);

		m_buttonGameEnd = CreateWindow(_T("button"), _T("��������"),
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP,
			0, 30, 200, 30,
			hUi, (HMENU)IDC_BUTTON_GameEnd, hInstance, NULL);
		image.Load(_T("resource/Button/GameEnd_Small.bmp"));
		hBmp = image.Detach();
		SendMessage(m_buttonGameEnd, BM_SETIMAGE, 0, (LPARAM)hBmp);
	}
	else if (m_phase == DetailSelectPhase::Skill)
	{
		if (m_pUnit == NULL)
			return;
		int height = m_pUnit->GetSkillNum();
		int count = 0;

		/*if ((m_ptPos.y + 30 * height) > m_rcRect.bottom)
			m_ptPos.y -= (m_rcRect.bottom - m_ptPos.y + 30 * height);*/
		//MoveWindow(hUi, m_ptPos.x, m_ptPos.y + 30, 200, 30 * height, FALSE);

		if (m_pUnit->FindSkill(SKillName::Explosion))
		{
			m_buttonSkill.push_back(CreateWindow(_T("button"), _T("�ͽ��÷���"),
				WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP,
				0, 30 * count, 200, 30,
				hUi, (HMENU)IDC_BUTTON_Explosion, hInstance, NULL)
				);
			image.Load(_T("resource/button/Explosion.bmp"));
			hBmp = image.Detach();
			SendMessage(m_buttonSkill[count++], BM_SETIMAGE, 0, (LPARAM)hBmp);
		}
		if (m_pUnit->FindSkill(SKillName::FlameBurst))
		{
			m_buttonSkill.push_back(CreateWindow(_T("button"), _T("�ͽ��÷���"),
				WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP,
				0, 30 * count, 200, 30,
				hUi, (HMENU)IDC_BUTTON_FlameBurst, hInstance, NULL)
				);
			image.Load(_T("resource/button/FlameBurst.bmp"));
			hBmp = image.Detach();
			SendMessage(m_buttonSkill[count++], BM_SETIMAGE, 0, (LPARAM)hBmp);
		}
		if (m_pUnit->FindSkill(SKillName::Aid))
		{
			m_buttonSkill.push_back(CreateWindow(_T("button"), _T("���̵�"),
				WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP,
				0, 30 * count, 200, 30,
				hUi, (HMENU)IDC_BUTTON_Aid, hInstance, NULL)
				);
			image.Load(_T("resource/button/aid.bmp"));
			hBmp = image.Detach();
			SendMessage(m_buttonSkill[count++], BM_SETIMAGE, 0, (LPARAM)hBmp);
		}
		if (m_pUnit->FindSkill(SKillName::ManaAid))
		{
			m_buttonSkill.push_back(CreateWindow(_T("button"), _T("�������̵�"),
				WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP,
				0, 30 * count, 200, 30,
				hUi, (HMENU)IDC_BUTTON_ManaAid, hInstance, NULL)
				);
			image.Load(_T("resource/button/ManaAid.bmp"));
			hBmp = image.Detach();
			SendMessage(m_buttonSkill[count++], BM_SETIMAGE, 0, (LPARAM)hBmp);
		}
		if (m_pUnit->FindSkill(SKillName::Mercy))
		{
			m_buttonSkill.push_back(CreateWindow(_T("button"), _T("�޸���"),
				WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP,
				0, 30 * count, 200, 30,
				hUi, (HMENU)IDC_BUTTON_Mercy, hInstance, NULL)
				);
			image.Load(_T("resource/button/Mercy.bmp"));
			hBmp = image.Detach();
			SendMessage(m_buttonSkill[count++], BM_SETIMAGE, 0, (LPARAM)hBmp);
		}
		if (m_pUnit->FindSkill(SKillName::Resurrection))
		{
			m_buttonSkill.push_back(CreateWindow(_T("button"), _T("��������"),
				WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP,
				0, 30 * count, 200, 30,
				hUi, (HMENU)IDC_BUTTON_Resurrection, hInstance, NULL)
				);
			image.Load(_T("resource/button/Resurrection.bmp"));
			hBmp = image.Detach();
			SendMessage(m_buttonSkill[count++], BM_SETIMAGE, 0, (LPARAM)hBmp);
		}
		if (m_pUnit->FindSkill(SKillName::Sacrifice))
		{
			m_buttonSkill.push_back(CreateWindow(_T("button"), _T("��ũ�����̽�"),
				WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP,
				0, 30 * count, 200, 30,
				hUi, (HMENU)IDC_BUTTON_Sacrifice, hInstance, NULL)
				);
			image.Load(_T("resource/button/Sacrifice.bmp"));
			hBmp = image.Detach();
			SendMessage(m_buttonSkill[count++], BM_SETIMAGE, 0, (LPARAM)hBmp);
		}
		if (m_pUnit->FindSkill(SKillName::Edge))
		{
			m_buttonSkill.push_back(CreateWindow(_T("button"), _T("����"),
				WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP,
				0, 30 * count, 200, 30,
				hUi, (HMENU)IDC_BUTTON_Edge, hInstance, NULL)
				);
			image.Load(_T("resource/button/Edge.bmp"));
			hBmp = image.Detach();
			SendMessage(m_buttonSkill[count++], BM_SETIMAGE, 0, (LPARAM)hBmp);
		}
		if (m_pUnit->FindSkill(SKillName::Earthquake))
		{
			m_buttonSkill.push_back(CreateWindow(_T("button"), _T("�����ũ"),
				WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP,
				0, 30 * count, 200, 30,
				hUi, (HMENU)IDC_BUTTON_EarthQuake, hInstance, NULL)
				);
			image.Load(_T("resource/button/EarthQuake.bmp"));
			hBmp = image.Detach();
			SendMessage(m_buttonSkill[count++], BM_SETIMAGE, 0, (LPARAM)hBmp);
		}
		if (m_pUnit->FindSkill(SKillName::Curse))
		{
			m_buttonSkill.push_back(CreateWindow(_T("button"), _T("Ŀ��"),
				WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP,
				0, 30 * count, 200, 30,
				hUi, (HMENU)IDC_BUTTON_Curse, hInstance, NULL)
				);
			image.Load(_T("resource/button/Curse.bmp"));
			hBmp = image.Detach();
			SendMessage(m_buttonSkill[count++], BM_SETIMAGE, 0, (LPARAM)hBmp);
		}
		if (m_pUnit->FindSkill(SKillName::EvillEye))
		{
			m_buttonSkill.push_back(CreateWindow(_T("button"), _T("�̺����"),
				WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP,
				0, 30 * count, 200, 30,
				hUi, (HMENU)IDC_BUTTON_EvillEye, hInstance, NULL)
				);
			image.Load(_T("resource/button/EvillEye.bmp"));
			hBmp = image.Detach();
			SendMessage(m_buttonSkill[count++], BM_SETIMAGE, 0, (LPARAM)hBmp);
		}
		if (m_pUnit->FindSkill(SKillName::Thunder))
		{
			m_buttonSkill.push_back(CreateWindow(_T("button"), _T("���"),
				WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP,
				0, 30 * count, 200, 30,
				hUi, (HMENU)IDC_BUTTON_Thunder, hInstance, NULL)
				);
			image.Load(_T("resource/button/Thunder.bmp"));
			hBmp = image.Detach();
			SendMessage(m_buttonSkill[count++], BM_SETIMAGE, 0, (LPARAM)hBmp);
		}
		if (m_pUnit->FindSkill(SKillName::ThunderFlare))
		{
			m_buttonSkill.push_back(CreateWindow(_T("button"), _T("���������"),
				WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP,
				0, 30 * count, 200, 30,
				hUi, (HMENU)IDC_BUTTON_ThunderFlare, hInstance, NULL)
				);
			image.Load(_T("resource/button/ThunderFlare.bmp"));
			hBmp = image.Detach();
			SendMessage(m_buttonSkill[count++], BM_SETIMAGE, 0, (LPARAM)hBmp);

		}
		if (m_pUnit->FindSkill(SKillName::Hurricane))
		{
			m_buttonSkill.push_back(CreateWindow(_T("button"), _T("�㸮����"),
				WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP,
				0, 30 * count, 200, 30,
				hUi, (HMENU)IDC_BUTTON_Hurricane, hInstance, NULL)
				);
			image.Load(_T("resource/button/Hurricane.bmp"));
			hBmp = image.Detach();
			SendMessage(m_buttonSkill[count++], BM_SETIMAGE, 0, (LPARAM)hBmp);
		}
		if (m_pUnit->FindSkill(SKillName::WindBlast))
		{
			m_buttonSkill.push_back(CreateWindow(_T("button"), _T("�������Ʈ"),
				WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP,
				0, 30 * count, 200, 30,
				hUi, (HMENU)IDC_BUTTON_WindBlast, hInstance, NULL)
				);
			image.Load(_T("resource/button/WindBlast.bmp"));
			hBmp = image.Detach();
			SendMessage(m_buttonSkill[count++], BM_SETIMAGE, 0, (LPARAM)hBmp);
		}
	}
}


CUI_DetailSelect * CUI_DetailSelect::GetInstance(HWND hWnd, HINSTANCE hInstance)
{
	if (instance == NULL)
	{
		instance = new CUI_DetailSelect(hWnd, hInstance);
	}
	return instance;
}
CUI_DetailSelect * CUI_DetailSelect::GetInstance()
{
	return instance;
}

LRESULT CALLBACK UI_DetailSelect_Proc(HWND hWnd, UINT iMsg,
	WPARAM wParam, LPARAM lParam)
{
	HDC hdc, bufferDC; //ȭ�鿡 ����� hdc, ����ϱ� ������ ������ ���� bufferDC
	PAINTSTRUCT ps;
	static RECT rect;
	static CUI_DetailSelect* self;
	static CUI_CommandSelect* parent;
	static HBITMAP		hBmp;

	switch (iMsg)
	{
	case WM_CREATE:
		self = self->GetInstance();
		parent = CUI_CommandSelect::GetInstance();
		rect = self->GetRect();
		break;
	case WM_ERASEBKGND:
		InvalidateRect(hWnd, NULL, FALSE);
		break;
	case WM_MOUSEMOVE:
		int check;
		check = 0;
		break;
	case WM_COMMAND:
		CUnit* unit;
		unit = self->GetUnit();
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON_UnitList:
			self->DestroyUI();
			parent->DestroyUI();
			//self->GetParent()->SetCommandSelecting(FALSE);
			CUI_UnitDetailInfo::GetInstance()->MakeUI();
			break;
		case IDC_BUTTON_StageChange:
			self->DestroyUI();
			parent->DestroyUI();

			CUI_UnitInfo::GetInstance()->HideUI();
			CUI_Notice::GetInstance()->HideUI();
			CUI_StageSelect::GetInstance()->SetCurrentStage(self->GetParent()->GetCurrentScene());
			CUI_StageSelect::GetInstance()->MakeUI();
			break;
		case IDC_BUTTON_GameEnd:
			PostQuitMessage(0);
			break;
		case IDC_BUTTON_ClearCondition:
			self->DestroyUI();
			parent->DestroyUI();
			//self->GetParent()->SetCommandSelecting(FALSE);
			CUI_ClearCondition::GetInstance()->MakeUI();
			break;
		case IDC_BUTTON_Explosion:
			if (unit->GetMp() >= 10)
			{
				unit->HandleInput(SKillName::Explosion);
				unit->SetCurrentSkill(SKillName::Explosion);

				parent->GetParent()->GetMap()->CheckSkillTile(unit
					, unit->GetCurrentIndex()
					, 5
					, SkillAttackType::Contiguous);

				self->DestroyUI();
				parent->DestroyUI();
				self->GetParent()->SetPhase(NoticePhase::SkillPhase);
				CUI_Notice::GetInstance()->MakeUI();
				CUI_Notice::GetInstance()->Update(NoticePhase::SkillPhase);
				self->GetParent()->SetCommandSelecting(FALSE);
			}
			else
			{
				CUI_Notice::GetInstance()->MakeUI();
				CUI_Notice::GetInstance()->Update(NoticePhase::ManaLack);
			}
			break;

		case IDC_BUTTON_FlameBurst:
			if (unit->GetMp() >= 20)
			{
				unit->HandleInput(SKillName::FlameBurst);
				unit->SetCurrentSkill(SKillName::FlameBurst);
				parent->GetParent()->GetMap()->CheckSkillTile(unit
					, unit->GetCurrentIndex()
					, 5
					, SkillAttackType::Line);

				self->DestroyUI();
				parent->DestroyUI();
				self->GetParent()->SetPhase(NoticePhase::SkillPhase);
				CUI_Notice::GetInstance()->MakeUI();
				CUI_Notice::GetInstance()->Update(NoticePhase::SkillPhase);
				self->GetParent()->SetCommandSelecting(FALSE);
			}
			else
			{
				CUI_Notice::GetInstance()->MakeUI();
				CUI_Notice::GetInstance()->Update(NoticePhase::ManaLack);
			}
			break;
		case IDC_BUTTON_Aid:
			if (unit->GetMp() >= 5)
			{
				unit->HandleInput(SKillName::Aid);
				unit->SetCurrentSkill(SKillName::Aid);

				parent->GetParent()->GetMap()->CheckSkillTile(unit
					, unit->GetCurrentIndex()
					, 5
					, SkillAttackType::Contiguous);

				self->DestroyUI();
				parent->DestroyUI();
				self->GetParent()->SetPhase(NoticePhase::SkillPhase);
				CUI_Notice::GetInstance()->MakeUI();
				CUI_Notice::GetInstance()->Update(NoticePhase::SkillPhase);
				self->GetParent()->SetCommandSelecting(FALSE);
			}
			else
			{
				CUI_Notice::GetInstance()->MakeUI();
				CUI_Notice::GetInstance()->Update(NoticePhase::ManaLack);
			}
			break;
		case IDC_BUTTON_ManaAid:
			if (unit->GetMp() >= 10)
			{
				unit->HandleInput(SKillName::ManaAid);
				unit->SetCurrentSkill(SKillName::ManaAid);

				parent->GetParent()->GetMap()->CheckSkillTile(unit
					, unit->GetCurrentIndex()
					, 5
					, SkillAttackType::Contiguous);

				self->DestroyUI();
				parent->DestroyUI();
				self->GetParent()->SetPhase(NoticePhase::SkillPhase);
				CUI_Notice::GetInstance()->MakeUI();
				CUI_Notice::GetInstance()->Update(NoticePhase::SkillPhase);
				self->GetParent()->SetCommandSelecting(FALSE);
			}
			else
			{
				CUI_Notice::GetInstance()->MakeUI();
				CUI_Notice::GetInstance()->Update(NoticePhase::ManaLack);
			}
			break;
		case IDC_BUTTON_Mercy:
			if (unit->GetMp() >= 10)
			{
				unit->HandleInput(SKillName::Mercy);
				unit->SetCurrentSkill(SKillName::Mercy);

				parent->GetParent()->GetMap()->CheckSkillTile(unit
					, unit->GetCurrentIndex()
					, 5
					, SkillAttackType::Contiguous);

				self->DestroyUI();
				parent->DestroyUI();
				self->GetParent()->SetPhase(NoticePhase::SkillPhase);
				CUI_Notice::GetInstance()->MakeUI();
				CUI_Notice::GetInstance()->Update(NoticePhase::SkillPhase);
				self->GetParent()->SetCommandSelecting(FALSE);
			}
			else
			{
				CUI_Notice::GetInstance()->MakeUI();
				CUI_Notice::GetInstance()->Update(NoticePhase::ManaLack);
			}
			break;
		case IDC_BUTTON_Resurrection:
			if (unit->GetMp() >= 15)
			{
				unit->HandleInput(SKillName::Resurrection);
				unit->SetCurrentSkill(SKillName::Resurrection);

				parent->GetParent()->GetMap()->CheckSkillTile(unit
					, unit->GetCurrentIndex()
					, 5
					, SkillAttackType::Contiguous);

				self->DestroyUI();
				parent->DestroyUI();
				self->GetParent()->SetPhase(NoticePhase::SkillPhase);
				CUI_Notice::GetInstance()->MakeUI();
				CUI_Notice::GetInstance()->Update(NoticePhase::SkillPhase);
				self->GetParent()->SetCommandSelecting(FALSE);
			}
			else
			{
				CUI_Notice::GetInstance()->MakeUI();
				CUI_Notice::GetInstance()->Update(NoticePhase::ManaLack);
			}
			break;
		case IDC_BUTTON_Sacrifice:
			if (unit->GetMp() >= 30)
			{
				unit->HandleInput(SKillName::Sacrifice);
				unit->SetCurrentSkill(SKillName::Sacrifice);

				parent->GetParent()->GetMap()->CheckSkillTile(unit
					, unit->GetCurrentIndex()
					, 5
					, SkillAttackType::Contiguous);

				self->DestroyUI();
				parent->DestroyUI();
				self->GetParent()->SetPhase(NoticePhase::SkillPhase);
				CUI_Notice::GetInstance()->MakeUI();
				CUI_Notice::GetInstance()->Update(NoticePhase::SkillPhase);
				self->GetParent()->SetCommandSelecting(FALSE);
			}
			else
			{
				CUI_Notice::GetInstance()->MakeUI();
				CUI_Notice::GetInstance()->Update(NoticePhase::ManaLack);
			}
			break;
		case IDC_BUTTON_Edge:
			if (unit->GetMp() >= 10)
			{
				unit->HandleInput(SKillName::Edge);
				unit->SetCurrentSkill(SKillName::Edge);

				parent->GetParent()->GetMap()->CheckSkillTile(unit
					, unit->GetCurrentIndex()
					, 5
					, SkillAttackType::Contiguous);

				self->DestroyUI();
				parent->DestroyUI();
				self->GetParent()->SetPhase(NoticePhase::SkillPhase);
				CUI_Notice::GetInstance()->MakeUI();
				CUI_Notice::GetInstance()->Update(NoticePhase::SkillPhase);
				self->GetParent()->SetCommandSelecting(FALSE);
			}
			else
			{
				CUI_Notice::GetInstance()->MakeUI();
				CUI_Notice::GetInstance()->Update(NoticePhase::ManaLack);
			}
			break;

		case IDC_BUTTON_EarthQuake:
			if (unit->GetMp() >= 20)
			{
				unit->HandleInput(SKillName::Earthquake);
				unit->SetCurrentSkill(SKillName::Earthquake);

				parent->GetParent()->GetMap()->CheckSkillTile(unit
					, unit->GetCurrentIndex()
					, 5
					, SkillAttackType::Line);

				self->DestroyUI();
				parent->DestroyUI();
				self->GetParent()->SetPhase(NoticePhase::SkillPhase);
				CUI_Notice::GetInstance()->MakeUI();
				CUI_Notice::GetInstance()->Update(NoticePhase::SkillPhase);
				self->GetParent()->SetCommandSelecting(FALSE);
			}
			else
			{
				CUI_Notice::GetInstance()->MakeUI();
				CUI_Notice::GetInstance()->Update(NoticePhase::ManaLack);
			}
			break;
		case IDC_BUTTON_Thunder:
			if (unit->GetMp() >= 10)
			{
				unit->HandleInput(SKillName::Thunder);
				unit->SetCurrentSkill(SKillName::Thunder);

				parent->GetParent()->GetMap()->CheckSkillTile(unit
					, unit->GetCurrentIndex()
					, 5
					, SkillAttackType::Contiguous);

				self->DestroyUI();
				parent->DestroyUI();
				self->GetParent()->SetPhase(NoticePhase::SkillPhase);
				CUI_Notice::GetInstance()->MakeUI();
				CUI_Notice::GetInstance()->Update(NoticePhase::SkillPhase);
				self->GetParent()->SetCommandSelecting(FALSE);
			}
			else
			{
				CUI_Notice::GetInstance()->MakeUI();
				CUI_Notice::GetInstance()->Update(NoticePhase::ManaLack);
			}
			break;
		case IDC_BUTTON_ThunderFlare:
			if (unit->GetMp() >= 20)
			{
				unit->HandleInput(SKillName::ThunderFlare);
				unit->SetCurrentSkill(SKillName::ThunderFlare);

				parent->GetParent()->GetMap()->CheckSkillTile(unit
					, unit->GetCurrentIndex()
					, 5
					, SkillAttackType::Line);

				self->DestroyUI();
				parent->DestroyUI();
				self->GetParent()->SetPhase(NoticePhase::SkillPhase);
				CUI_Notice::GetInstance()->MakeUI();
				CUI_Notice::GetInstance()->Update(NoticePhase::SkillPhase);
				self->GetParent()->SetCommandSelecting(FALSE);
			}
			else
			{
				CUI_Notice::GetInstance()->MakeUI();
				CUI_Notice::GetInstance()->Update(NoticePhase::ManaLack);
			}
			break;
		case IDC_BUTTON_Hurricane:
			if (unit->GetMp() >= 10)
			{
				unit->HandleInput(SKillName::Hurricane);
				unit->SetCurrentSkill(SKillName::Hurricane);

				parent->GetParent()->GetMap()->CheckSkillTile(unit
					, unit->GetCurrentIndex()
					, 5
					, SkillAttackType::Contiguous);

				self->DestroyUI();
				parent->DestroyUI();
				self->GetParent()->SetPhase(NoticePhase::SkillPhase);
				CUI_Notice::GetInstance()->MakeUI();
				CUI_Notice::GetInstance()->Update(NoticePhase::SkillPhase);
				self->GetParent()->SetCommandSelecting(FALSE);
			}
			else
			{
				CUI_Notice::GetInstance()->MakeUI();
				CUI_Notice::GetInstance()->Update(NoticePhase::ManaLack);
			}
			break;
		case IDC_BUTTON_WindBlast:
			if (unit->GetMp() >= 20)
			{
				unit->HandleInput(SKillName::WindBlast);
				unit->SetCurrentSkill(SKillName::WindBlast);

				parent->GetParent()->GetMap()->CheckSkillTile(unit
					, unit->GetCurrentIndex()
					, 5
					, SkillAttackType::Line);

				self->DestroyUI();
				parent->DestroyUI();
				self->GetParent()->SetPhase(NoticePhase::SkillPhase);
				CUI_Notice::GetInstance()->MakeUI();
				CUI_Notice::GetInstance()->Update(NoticePhase::SkillPhase);
				self->GetParent()->SetCommandSelecting(FALSE);
			}
			else
			{
				CUI_Notice::GetInstance()->MakeUI();
				CUI_Notice::GetInstance()->Update(NoticePhase::ManaLack);
			}
			break;
		case IDC_BUTTON_Curse:
			if (unit->GetMp() >= 10)
			{
				unit->HandleInput(SKillName::Curse);
				unit->SetCurrentSkill(SKillName::Curse);

				parent->GetParent()->GetMap()->CheckSkillTile(unit
					, unit->GetCurrentIndex()
					, 5
					, SkillAttackType::Contiguous);

				self->DestroyUI();
				parent->DestroyUI();
				self->GetParent()->SetPhase(NoticePhase::SkillPhase);
				CUI_Notice::GetInstance()->MakeUI();
				CUI_Notice::GetInstance()->Update(NoticePhase::SkillPhase);
				self->GetParent()->SetCommandSelecting(FALSE);
			}
			else
			{
				CUI_Notice::GetInstance()->MakeUI();
				CUI_Notice::GetInstance()->Update(NoticePhase::ManaLack);
			}
			break;
		case IDC_BUTTON_EvillEye:
			if (unit->GetMp() >= 20)
			{
				unit->HandleInput(SKillName::EvillEye);
				unit->SetCurrentSkill(SKillName::EvillEye);

				parent->GetParent()->GetMap()->CheckSkillTile(unit
					, unit->GetCurrentIndex()
					, 5
					, SkillAttackType::Line);

				self->DestroyUI();
				parent->DestroyUI();
				self->GetParent()->SetPhase(NoticePhase::SkillPhase);
				CUI_Notice::GetInstance()->MakeUI();
				CUI_Notice::GetInstance()->Update(NoticePhase::SkillPhase);
				self->GetParent()->SetCommandSelecting(FALSE);
			}
			else
			{
				CUI_Notice::GetInstance()->MakeUI();
				CUI_Notice::GetInstance()->Update(NoticePhase::ManaLack);
			}
			break;
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		bufferDC = CreateCompatibleDC(hdc);//hdc�� ȣȯ�Ǵ� bufferDC����, ������۸�
		hBmp = CreateBitmap(rect.right, rect.bottom, 1, 32, NULL);
		SelectObject(bufferDC, hBmp);
		::FillRect(bufferDC, &rect, (HBRUSH)::GetStockObject(LTGRAY_BRUSH));

		BitBlt(hdc, rect.left, rect.top, rect.right, rect.bottom,
			bufferDC, rect.left, rect.top, SRCCOPY);//bufferDC�� �ִ� ������ hdc�� �Ű� �׸�
													//self->DrawUnit(hdc);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		break;
	}
	return DefMDIChildProc(hWnd, iMsg, wParam, lParam);
}