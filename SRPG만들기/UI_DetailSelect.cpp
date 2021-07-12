#include "stdafx.h"
#include "UI_DetailSelect.h"

CUI_DetailSelect* CUI_DetailSelect::instance = NULL;
CUI_DetailSelect::CUI_DetailSelect(HWND hWnd, HINSTANCE hInstance)
	:CUI(hWnd, hInstance)
{
	szWindowClass = _T("Detail_Class");
	szWindowTitle = _T("행동 선택");

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
			CS_HREDRAW	//클라이언트의 넓이를 변경하면 다시 그리도록 합니다. 
			| CS_VREDRAW	//클라이언트의 높이를 변경하면 다시 그리도록 합니다.
			| CS_DBLCLKS	//해당 응용프로그램이 더블 클릭을 지원하도록 합니다.
			;
		wcex.lpfnWndProc = UI_DetailSelect_Proc;
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
		szWindowClass           // 차일드 윈도우 클래스 이름 
		, szWindowTitle         // 윈도우 타이틀 
		, WS_CHILD
		| WS_SYSMENU
		| WS_VISIBLE
	//	| WS_CLIPSIBLINGS			//차일드끼리 상호 겹친 영역은 그리기 영역에서 제외
	//	| WS_CLIPCHILDREN			//차일드가 위치한 영역은 그리기 영역에서 제외
		, m_ptPos.x					// 윈도우 보일 때 x 좌표 
		, m_ptPos.y					// 윈도우 보일 때 y 좌표 
		, 200					    // 윈도우 폭
		, 60					    // 윈도우 높이
		, hWnd					    //부모 윈도우
		, (HMENU)NULL			    //메뉴 핸들
		, hInstance				    //인스턴스 핸들
		, NULL					    //추가 파라메터
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
			m_buttonUnitList = CreateWindow(_T("button"), _T("유닛 일람"),
				WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP,
				0, 0, 200, 30,
				hUi, (HMENU)IDC_BUTTON_UnitList, hInstance, NULL);
			image.Load(_T("resource/Button/UnitList.bmp"));
			hBmp = image.Detach();
			SendMessage(m_buttonUnitList, BM_SETIMAGE, 0, (LPARAM)hBmp);
			height++;
		}
		m_buttonClearCondition = CreateWindow(_T("button"), _T("클리어 조건"),
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
		m_buttonStageChange = CreateWindow(_T("button"), _T("스테이지 전환"),
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP,
			0, 0, 200, 30,
			hUi, (HMENU)IDC_BUTTON_StageChange, hInstance, NULL);
		image.Load(_T("resource/Button/StageChange.bmp"));
		hBmp = image.Detach();
		SendMessage(m_buttonStageChange, BM_SETIMAGE, 0, (LPARAM)hBmp);

		m_buttonGameEnd = CreateWindow(_T("button"), _T("게임종료"),
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
			m_buttonSkill.push_back(CreateWindow(_T("button"), _T("익스플로전"),
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
			m_buttonSkill.push_back(CreateWindow(_T("button"), _T("익스플로전"),
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
			m_buttonSkill.push_back(CreateWindow(_T("button"), _T("에이드"),
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
			m_buttonSkill.push_back(CreateWindow(_T("button"), _T("마나에이드"),
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
			m_buttonSkill.push_back(CreateWindow(_T("button"), _T("메르시"),
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
			m_buttonSkill.push_back(CreateWindow(_T("button"), _T("레저렉션"),
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
			m_buttonSkill.push_back(CreateWindow(_T("button"), _T("세크리파이스"),
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
			m_buttonSkill.push_back(CreateWindow(_T("button"), _T("엣지"),
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
			m_buttonSkill.push_back(CreateWindow(_T("button"), _T("어스퀘이크"),
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
			m_buttonSkill.push_back(CreateWindow(_T("button"), _T("커스"),
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
			m_buttonSkill.push_back(CreateWindow(_T("button"), _T("이블아이"),
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
			m_buttonSkill.push_back(CreateWindow(_T("button"), _T("썬더"),
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
			m_buttonSkill.push_back(CreateWindow(_T("button"), _T("썬더프레어"),
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
			m_buttonSkill.push_back(CreateWindow(_T("button"), _T("허리케인"),
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
			m_buttonSkill.push_back(CreateWindow(_T("button"), _T("윈드블레스트"),
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
	HDC hdc, bufferDC; //화면에 출력할 hdc, 출력하기 전까지 저장할 변수 bufferDC
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
		bufferDC = CreateCompatibleDC(hdc);//hdc와 호환되는 bufferDC생성, 더블버퍼링
		hBmp = CreateBitmap(rect.right, rect.bottom, 1, 32, NULL);
		SelectObject(bufferDC, hBmp);
		::FillRect(bufferDC, &rect, (HBRUSH)::GetStockObject(LTGRAY_BRUSH));

		BitBlt(hdc, rect.left, rect.top, rect.right, rect.bottom,
			bufferDC, rect.left, rect.top, SRCCOPY);//bufferDC에 있던 내용을 hdc에 옮겨 그림
													//self->DrawUnit(hdc);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		break;
	}
	return DefMDIChildProc(hWnd, iMsg, wParam, lParam);
}