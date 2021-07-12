#include "stdafx.h"
#include "stage1.h"

#include "Tile.h"
#include "Karin.h"
#include "YoungKarin.h"
#include "Rian.h"
#include "Farm.h"
#include "Reon.h"
#include "Cat.h"
#include "Arl.h"
#include "Aris.h"
#include "Rucia.h"
#include "Marcia.h"
#include "Catherine.h"
#include "Ivan.h"
#include "Wolf.h"
#include "Ruru.h"
#include "Fairy.h"
#include "Shon.h"
#include "BlackKnight.h"
#include "Crab.h"

CStage1::CStage1(CFrameWork * framework, HWND hWnd, CurrentScene tag)
	:CScene(framework, hWnd)
{
	INDEX idx;
	m_map = new CMap(_T("resource/map/요새.txt"));
	m_map->LoadUnit(_T("resource/map/요새_유닛.txt"),&m_vecUnits);
	/*idx = m_map->GetTilePos(10, 10);
	idx.height = m_map->GetHeight(INDEX{ 10,10 ,0});
	m_vecUnits.push_back(new CReon(idx));
	m_map->SetUnitOnTile(INDEX{ 10,10, m_map->GetHeight(idx) }, m_vecUnits[0]);
*/

	for (int i = 0; i < (int)m_vecUnits.size(); ++i)
	{
		m_vecUnits[i]->SetSound(m_pFrameWork->GetSound());
		m_vecUnits[i]->SetStage(this);
	}
	SortUnitArrayDown();

	for (int i = 0; i < 7; ++i)
	{
		m_vecUnits[i]->SetUnitWay(UnitWay::LeftDown);
	}
	for (int i = 7; i < 14; ++i)
	{
		m_vecUnits[i]->SetUnitWay(UnitWay::RightUp);
	}
	m_vecUnits[5]->SetUnitWay(UnitWay::RightDown);
	m_vecUnits[13]->SetUnitWay(UnitWay::LeftUp);
	m_pFrameWork->GetSound()->AddStream(("resource/sound/BGM/STAGE1_BGM.mp3"), Sound_Name::BGM_STAGE1);
	m_pFrameWork->GetSound()->AddSound("resource/sound/Effect/move.wav", Sound_Name::EFFECT_MOVE_GROUND);
	m_pFrameWork->GetSound()->AddSound("resource/sound/Effect/stick_attack.wav", Sound_Name::EFFECT_STICK_ATTACK);
	m_pFrameWork->GetSound()->AddSound("resource/sound/Effect/stick_swing.wav", Sound_Name::EFFECT_STICK_SWING);
	m_pFrameWork->GetSound()->AddSound("resource/sound/Effect/sword_attack.wav", Sound_Name::EFFECT_SWORD_ATTACK);
	m_pFrameWork->GetSound()->AddSound("resource/sound/Effect/attack_hand.wav", Sound_Name::EFFECT_HAND_ATTACK);
	m_pFrameWork->GetSound()->AddSound("resource/sound/Effect/TurnChange.wav", Sound_Name::EFFECT_NEW_TURN);
	m_pFrameWork->GetSound()->AddSound("resource/sound/Effect/Burst.wav", Sound_Name::EFFECT_BURST);
	m_pFrameWork->GetSound()->AddSound("resource/sound/Effect/Aid.wav", Sound_Name::EFFECT_AID);
	m_pFrameWork->GetSound()->AddSound("resource/sound/Effect/curse.wav", Sound_Name::EFFECT_CURSE);
	m_pFrameWork->GetSound()->AddSound("resource/sound/Effect/Hurricane.wav", Sound_Name::EFFECT_HURRICANE);
	m_pFrameWork->GetSound()->AddSound("resource/sound/Effect/Resurrection.wav", Sound_Name::EFFECT_RESURRECTION);
	m_pFrameWork->GetSound()->AddSound("resource/sound/Effect/Edge.wav", Sound_Name::EFFECT_EDGE);
	m_pFrameWork->GetSound()->AddSound("resource/sound/Effect/Thunder.wav", Sound_Name::EFFECT_THUNDER);
	m_pCurUnit = NULL;

	m_nUnitNum = (short)m_vecUnits.size();

	camera.viewPoint.x = 0;
	camera.viewPoint.y = 0;
	m_bLeftClick = FALSE;
	m_tag = tag;
	m_phase = NoticePhase::None;

	UI_UnitInfo = CUI_UnitInfo::GetInstance(
		m_pFrameWork->GetHWND()
		, m_pFrameWork->GetHINSTANCE()
		, NULL
		);
	UI_CommandSelect = CUI_CommandSelect::GetInstance(
		m_pFrameWork->GetHWND()
		, m_pFrameWork->GetHINSTANCE()
		, NULL
		);
	UI_CommandSelect->SetRect(m_rcApp);
	UI_CommandSelect->SetParent(this);

	UI_Notice = CUI_Notice::GetInstance(
		m_pFrameWork->GetHWND()
		, m_pFrameWork->GetHINSTANCE()
		, NoticePhase::MoveNotice);

	CUI_ClearCondition::GetInstance(
		m_pFrameWork->GetHWND()
		, m_pFrameWork->GetHINSTANCE()
		, CScene::CurrentScene::Stage1
		);

	CUI_UnitDetailInfo::GetInstance(
		m_pFrameWork->GetHWND()
		, m_pFrameWork->GetHINSTANCE()
		);
	CUI_UnitDetailInfo::GetInstance()->SetUnit(m_vecUnits[0]);
	camera.viewPoint.x = 100;
	camera.viewPoint.y = 120;

	m_bCommandSelecting = TRUE;
	CUI_ClearCondition::GetInstance()->SetPhase(CScene::CurrentScene::Stage1);
	CUI_ClearCondition::GetInstance()->MakeUI();
}
CStage1::~CStage1()
{
	delete m_map;
}

void CStage1::OnUpdate(float timeElapsed)
{
	if (m_bCommandSelecting)
		return;
	if (m_phase == NoticePhase::UsingSkillPhase)
	{
		m_pCurUnit->SkillSpriteUpdate(timeElapsed);
	}
	for (int i = 0; i < (int)m_vecUnits.size(); ++i)
	{
		m_vecUnits[i]->OnUpdate(timeElapsed);
	}
	for (std::vector<CUnit*>::iterator iter = m_vecUnits.begin(); iter != m_vecUnits.end();)
	{
		if ((*iter)->CheckTrueDie())
		{
			m_map->SetUnitOnTile((*iter)->GetCurrentIndex(), NULL);
			delete(*iter);
			iter = m_vecUnits.erase(iter);
		}
		else
			++iter;
	}

	if (m_phase == NoticePhase::EnemyPhase)
	{
		if (ExecuteEnemyAct())
		{
			SortUnitArrayDown();
			NewTurn();
			m_phase = NoticePhase::None;
		}
	}
	if (CheckGameWin())
		m_phase = NoticePhase::IntervalPhase;
	if (CheckGameLose())
		m_phase = NoticePhase::IntervalPhase;
}
void CStage1::OnDraw(HDC hdc)
{
	static int delay = 0;
	
	if (m_phase == NoticePhase::IntervalPhase)
	{
		DrawIntervalScene(hdc);
	}

	else
	{
		if (m_pCurUnit != NULL)
		{
			if (m_phase == NoticePhase::AttackPhase || m_phase == NoticePhase::OnlyAttackPhase)
			{
				m_map->OnDraw(hdc, m_vecUnits, 2, camera);
			}
			else if (m_phase == NoticePhase::SkillPhase
				|| m_phase == NoticePhase::WaitSkillPhase)
			{
				m_map->OnDraw(hdc, m_vecUnits, 3, camera);
			}
			else if (m_phase == NoticePhase::UsingSkillPhase
				|| m_phase == NoticePhase::EnemyPhase
				|| m_phase == NoticePhase::NoActPhase)
			{
				m_map->OnDraw(hdc, m_vecUnits, 0, camera);
			}
			else
				m_map->OnDraw(hdc, m_vecUnits, 1, camera);
		}
		else
		{
			m_map->OnDraw(hdc, m_vecUnits, 0, camera);
		}
	}
	if (m_phase == NoticePhase::UnitWayPhase)
		m_pCurUnit->DrawWayNotice(hdc, camera);
	if (m_phase == NoticePhase::UsingSkillPhase)
	{
		/*delay++;
		if (delay < 8)
		return;*/

		m_pCurUnit->DrawSkill(hdc, camera);
		if (m_pCurUnit->CheckSkillEnd())
		{
			if (m_pCurUnit->GetUnitTeam() == UnitTeam::West)
				m_phase = NoticePhase::NoActPhase;
			else
				m_phase = NoticePhase::None;
			m_pCurUnit = NULL;
			m_phase = NoticePhase::None;
			UI_Notice->Update(NoticePhase::MoveNotice);
			UI_Notice->HideUI();
			UI_UnitInfo->HideUI();
			delay = 0;
		}
	}
}
void CStage1::DrawIntervalScene(HDC hdc)
{
	//static int count = 0;
	COLORREF removeColor = RGB(255, 0, 255);		//지울 색상
	//static int alpha = 0;				//투명도

	if (m_nAlpha <= 255)
	{
		HDC LayDC;
		HBITMAP Lay;
		BLENDFUNCTION bf;

		bf.BlendOp = AC_SRC_OVER;
		bf.BlendFlags = 0;
		bf.AlphaFormat = 0;
		bf.SourceConstantAlpha = m_nAlpha;

		Lay = CreateCompatibleBitmap(hdc, m_rcApp.right, m_rcApp.bottom);
		LayDC = CreateCompatibleDC(hdc);
		SelectObject(LayDC, Lay);
		TransparentBlt(LayDC, 0, 0, m_rcApp.right, m_rcApp.bottom
			, hdc, m_rcApp.left, m_rcApp.top, m_rcApp.right, m_rcApp.bottom, removeColor);

		m_map->OnDraw(hdc, m_vecUnits, 0, camera);

		AlphaBlend(hdc, m_rcApp.left, m_rcApp.top, m_rcApp.right, m_rcApp.bottom
			, LayDC, 0, 0, m_rcApp.right, m_rcApp.bottom, bf);

		DeleteDC(LayDC);
		DeleteObject(Lay);
		m_nAlpha += 3;
	}
	else
	{
		if (CheckGameWin())
		{
			//CProfile::GetInstance()->AddStageClear();		//승리 횟수 추가
			//CProfile::GetInstance()->AddStageClear(1);
			//CheckAchievement();
			//m_pFrameWork->ChangeScene(CurrentScene::Title);
			m_pFrameWork->ChangeScene(CScene::CurrentScene::GameWin);
		}
		if (CheckGameLose())
		{
			//CProfile::GetInstance()->AddStageDefeat();		//패배 횟수 추가
			//CheckAchievement();
			m_pFrameWork->ChangeScene(CScene::CurrentScene::GameLose);
		}
	}
}


void CStage1::PlaySound()
{
	m_pFrameWork->GetSound()->PlayBgm(Sound_Name::BGM_STAGE1);
}
BOOL CStage1::OnProcessingKeyboardMessage(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
	case 'C':
	case 'c':
//		NewTurn();

		m_phase = NoticePhase::EnemyPhase;
		UI_Notice->Update(NoticePhase::MoveNotice);
		UI_UnitInfo->HideUI();
		UI_Notice->HideUI();
		return TRUE;
	}

	return FALSE;
}
BOOL CStage1::OnProcessingMouseMessage(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	switch (iMsg)
	{
	case WM_LBUTTONDOWN:
	{
		if (m_bCommandSelecting == TRUE)
		{
			CUI_DetailSelect::GetInstance()->DestroyUI();
			CUI_ClearCondition::GetInstance()->HideUI();
			CUI_UnitDetailInfo::GetInstance()->HideUI();
			UI_CommandSelect->DestroyUI();
			m_bCommandSelecting = FALSE;

			m_pCurUnit = NULL;

			UI_CommandSelect->SetUnit(m_pCurUnit);
			UI_Notice->HideUI();
			UI_UnitInfo->HideUI();
			break;
		}
		if (m_phase == NoticePhase::NoActPhase)
		{
			UI_Notice->Update(NoticePhase::MoveNotice);
			UI_Notice->HideUI();
		}

		INDEX idx;
		POINT pos;

		m_ptMouseStart.x = LOWORD(lParam);
		m_ptMouseStart.y = HIWORD(lParam);
		pos = m_ptMouseEnd = m_ptMouseStart;
		m_bLeftClick = TRUE;

		pos = m_map->GetTilePos(pos, &idx, camera);
		idx.height = m_map->GetHeight(idx);

		if (m_phase == NoticePhase::UnitWayPhase)
		{
			m_map->SetUnitOnTile(m_pCurUnit->GetPrevTileIndex(), NULL);
			m_pCurUnit->SetNextUnitWay(
				m_pCurUnit->CheckUnitWay(m_ptMouseStart, camera)
				);
			if (m_pCurUnit->GetCanAttack())
				m_pCurUnit->SetNextCommand(KeyInput::Idle);
			else
				m_pCurUnit->SetNextCommand(KeyInput::Stop);

			//m_pCurUnit = m_map->GetUnitOnTile(idx); //현재 유닛을 클릭한 타일에 있는 유닛으로 설정
			m_pCurUnit->HandleInput(KeyInput::Move);		//유닛을 지정한 타일로 이동시킵니다.
			m_phase = NoticePhase::NoActPhase;
			m_pCurUnit = NULL;

			//UI_Notice->Update(m_phase);
			UI_UnitInfo->HideUI();
			UI_Notice->HideUI();

			//SortUnitArray();
			m_bLeftClick = FALSE;
		}

		if (!idx.CheckInRange(m_map->GetColumn(), m_map->GetRow()))
			break;

		if (m_phase == NoticePhase::None)	//유닛이 행동하기 전
		{
			if (m_pCurUnit == NULL)					//유닛이 선택되어 있지 않은 경우
			{
				if (m_map->CheckIsUsableTile(idx) == FALSE) //클릭한 타일에 유닛이 있는 경우
				{
					if (m_map->GetUnitOnTile(idx)->GetUnitTeam() != UnitTeam::North)
					{
						m_pCurUnit = m_map->GetUnitOnTile(idx);
						UI_UnitInfo->SetUnit(m_map->GetUnitOnTile(idx));
						UI_UnitInfo->MakeUI();					//선택한 유닛의 HP,MP를 출력하는 UI를 생성합니다.
						break;
					}
					m_pCurUnit = m_map->GetUnitOnTile(idx); //현재 유닛을 클릭한 타일에 있는 유닛으로 설정
					m_map->CheckMovableTile(m_pCurUnit);	//유닛이 이동가능한 타일을 확인합니다.

					UI_UnitInfo->SetUnit(m_pCurUnit);
					UI_UnitInfo->MakeUI();					//선택한 유닛의 HP,MP를 출력하는 UI를 생성합니다.

					if (!m_pCurUnit->GetCanMove())
					{
						if (m_map->CheckContiguousEnemy(idx))
						{
							UI_Notice->MakeUI();
							UI_Notice->Update(NoticePhase::AttackPhase);	//공격 도움 UI로 변경합니다.
							m_phase = NoticePhase::OnlyAttackPhase;				//있다면 공격 명령을 수행하도록 합니다.
							m_bLeftClick = FALSE;
							break;
						}
						UI_CommandSelect->SetParent(this);
						CUI_UnitDetailInfo::GetInstance()->SetUnit(m_pCurUnit);
						CUI_DetailSelect::GetInstance()->SetParent(this);
						UI_CommandSelect->SetPos(m_ptMouseStart);
						UI_CommandSelect->MakeUI();
						UI_CommandSelect->SetUnit(m_pCurUnit);

						m_bCommandSelecting = TRUE;
						m_bLeftClick = FALSE;

						m_phase = NoticePhase::None;
						UI_Notice->Update(NoticePhase::MoveNotice);
						UI_Notice->HideUI();
						break;
					}
					
					UI_Notice->MakeUI();


					//UI_UnitInfo->OnUpdate();
					if (m_map->CheckContiguousEnemy(idx))	//유닛이 이동하지 않은 위치에서 적을 공격할 수 있는지 검사합니다.
					{
						UI_Notice->Update(NoticePhase::AttackPhase);	//공격 도움 UI로 변경합니다.
						m_phase = NoticePhase::OnlyAttackPhase;				//있다면 공격 명령을 수행하도록 합니다.
						break;
					}

					if (m_pCurUnit->GetCanMove() && m_pCurUnit->GetCanAttack())
					{
						//알림말 UI를 생성합니다.
						m_phase = NoticePhase::None;
						UI_Notice->Update(NoticePhase::MoveNotice);
					}
					else if(m_pCurUnit->GetCanMove())
					{
						m_phase = NoticePhase::None;
						UI_Notice->Update(NoticePhase::MoveNotice);
						//UI_Notice->HideUI();
					}
					else
					{
						m_phase = NoticePhase::None;
						UI_Notice->Update(NoticePhase::MoveNotice);
						UI_Notice->HideUI();
					}
					m_bLeftClick = FALSE;
				}
			}
			else									//유닛이 선택되어 있는 경우
			{
				if (m_pCurUnit == m_map->GetUnitOnTile(idx))	//현재 유닛과 새롭게 선택한 유닛이 같다면
					break;										//건너뜁니다.

				if (m_map->CheckIsUsableTile(idx) == FALSE)	//클릭한 타일에 유닛이 있는 경우
				{
					if (m_map->GetUnitOnTile(idx)->GetUnitTeam() != UnitTeam::North)
					{
						m_pCurUnit = m_map->GetUnitOnTile(idx);
						UI_UnitInfo->SetUnit(m_map->GetUnitOnTile(idx));
						UI_UnitInfo->MakeUI();					//선택한 유닛의 HP,MP를 출력하는 UI를 생성합니다.
						m_bLeftClick = FALSE;
						break;
					}
					m_pCurUnit->ClearMovableTile();
					m_pCurUnit->ClearAttackableTile();
					m_pCurUnit = m_map->GetUnitOnTile(idx);	//새롭게 선택된 타일에 있는 유닛으로 현재 유닛을 변경합니다.

					m_map->CheckMovableTile(m_pCurUnit);	//유닛이 이동가능한 타일을 확인합니다.

					UI_UnitInfo->SetUnit(m_pCurUnit);
					UI_UnitInfo->OnUpdate();

					if (m_pCurUnit->GetCanMove() && m_pCurUnit->GetCanAttack())
						UI_Notice->MakeUI();					//알림말 UI를 생성합니다.

					m_bLeftClick = FALSE;

				}
				else								//클릭한 타일에 유닛이 없는 경우
				{
					if (m_pCurUnit->CheckIsMovableTile(idx))	//현재 유닛의 이동가능 타일 목록에 선택한 타일이 있는지 확인합니다.
					{											//이동가능 타일 목록에 있는 경우
						m_pCurUnit->SetNextTile(idx);
						m_pCurUnit->SetPrevTile(m_pCurUnit->GetCurrentIndex());
						m_pCurUnit->SetCurrentTile(idx);

						//m_pCurUnit->SetCurrentPos(POINT{ idx.GetXPos(), idx.GetYPos() });
						m_pCurUnit->SetCurrentPos(m_map->GetTilePos(idx.x, idx.y));
						m_map->SetUnitOnTile(idx, m_pCurUnit);
						if (m_map->CheckContiguousEnemy(idx))	//이동한 위치에서 적 유닛이 있는지 검사합니다.
						{
							UI_Notice->Update(NoticePhase::AttackPhase);	//공격 도움 UI로 변경합니다.
							m_phase = NoticePhase::AttackPhase;				//있다면 공격 명령을 수행하도록 합니다.
						}
						else
						{
							UI_Notice->Update(NoticePhase::UnitWayPhase);	//유닛 방향 변경 도움 UI로 변경합니다.
							m_phase = NoticePhase::UnitWayPhase;			//없다면 유닛의 방향을 지정하게 합니다.
						}
						m_bLeftClick = FALSE;
					}
				}

			}
		}
		else if (m_phase == NoticePhase::OnlyAttackPhase)			//공격만 하는 분기
		{
			if (m_pCurUnit->CheckIsAttackableTile(idx))				//공격가능 타일이라면
			{
				m_pCurUnit->SetTargetUnit(m_map->GetUnitOnTile(idx));	//공격할 유닛에 선택한 타일에 있는 유닛을 추가합니다.
				m_pCurUnit->SetNextCommand(KeyInput::Attack);

				if (m_pCurUnit->GetCanAttack())
					m_pCurUnit->HandleInput(KeyInput::Attack);

				m_phase = NoticePhase::NoActPhase;
				m_pCurUnit->ClearAttackableTile();

				m_pCurUnit = NULL;

				UI_UnitInfo->HideUI();
				UI_Notice->HideUI();
			}
			else								//공격 가능 타일이 아닌 경우
			{
				m_pCurUnit->ClearAttackableTile();	//공격 가능 타일을 초기화 합니다.

				m_phase = NoticePhase::None;
				UI_Notice->Update(NoticePhase::MoveNotice);
			}
		}
		else if (m_phase == NoticePhase::AttackPhase) //이동 - 공격 하는 분기
		{
			if (m_pCurUnit->CheckIsAttackableTile(idx))	//현재 유닛의 공격가능 타일 목록에 선택한 타일이 있는지 확인합니다.
			{											//공격가능 타일 목록에 있는 경우
				if (m_pCurUnit->GetCanMove())
					m_map->SetUnitOnTile(m_pCurUnit->GetPrevTileIndex(), NULL);
				m_pCurUnit->SetTargetUnit(m_map->GetUnitOnTile(idx));	//공격할 유닛에 선택한 타일에 있는 유닛을 추가합니다.
				m_pCurUnit->SetNextCommand(KeyInput::Attack);

				if (m_pCurUnit->GetCanMove())
					m_pCurUnit->HandleInput(KeyInput::Move);		//유닛을 지정한 타일로 이동시킵니다.
				else if (m_pCurUnit->GetCanAttack())
					m_pCurUnit->HandleInput(KeyInput::Attack);

				m_phase = NoticePhase::NoActPhase;
				m_pCurUnit->ClearAttackableTile();

				m_pCurUnit = NULL;

				UI_UnitInfo->HideUI();
				UI_Notice->HideUI();

				//SortUnitArray();
			}
			else							//공격가능 목록에 없는 경우
			{								//공격하지 않고 이동만 합니다.
				if (m_pCurUnit->GetCanMove())
					m_map->SetUnitOnTile(m_pCurUnit->GetPrevTileIndex(), NULL);
				if (m_pCurUnit->GetCanMove())
					m_pCurUnit->HandleInput(KeyInput::Move);
				m_phase = NoticePhase::NoActPhase;
				m_pCurUnit->ClearAttackableTile();

				m_pCurUnit = NULL;

				UI_UnitInfo->HideUI();
				UI_Notice->HideUI();
			}
		}

		else if (m_phase == NoticePhase::SkillPhase)	//스킬 사용 분기
		{
			if (m_pCurUnit->CheckIsSkillTile(idx))		//선택한 타일이 스킬 범위 안인지 확인합니다.
			{											//맞는 경우
				m_map->CheckSkillTile(m_pCurUnit, idx, m_pCurUnit->GetCurrentSkill()); //해당 범위에 각 스킬의 고유범위의 스킬 타일을 생성합니다.
				UI_Notice->MakeUI();
				m_phase = NoticePhase::WaitSkillPhase;	//새로 생성한 스킬 범위에 대해 재입력을 기다립니다.
				UI_Notice->Update(NoticePhase::WaitSkillPhase);
				//m_pCurUnit->EnterNextState();
				//m_pCurUnit->SetNextCommand(KeyInput::Stop);
				//m_pCurUnit->SetSkillPos(POINT{ idx.GetXPos(), idx.GetYPos() });
				//m_phase = NoticePhase::UsingSkillPhase;

				//UI_Notice->HideUI();
			}
			//else
			//{    //아닌 경우
			//	m_pCurUnit->ClearSkillTile();	//선택을 초기화합니다.
			//	m_pCurUnit = NULL;

			//	m_phase = NoticePhase::None;
			//	UI_Notice->Update(NoticePhase::MoveNotice);
			//	UI_Notice->HideUI();
			//	UI_UnitInfo->HideUI();
			//}
		}
		else if (m_phase == NoticePhase::WaitSkillPhase)	// 스킬 사용 확인 분기
		{
			if (m_pCurUnit->CheckIsSkillTile(idx))			//클릭한 타일이 스킬 범위 안에 있는지 확인합니다.
			{
				m_pCurUnit->SetSkillTarget();				
				m_pCurUnit->EnterNextState();				//스킬 사용상태로 진입합니다.
				//m_pCurUnit->SetNextCommand(KeyInput::Stop);
				m_phase = NoticePhase::UsingSkillPhase;

				UI_Notice->HideUI();
				UI_UnitInfo->HideUI();
			}
			//else
			//{												//없는 경우
			//	m_pCurUnit->ClearSkillTile();				//선택을 초기화합니다.
			//	m_pCurUnit = NULL;

			//	m_phase = NoticePhase::None;
			//	UI_Notice->Update(NoticePhase::MoveNotice);
			//	UI_Notice->HideUI();
			//}
		}
	}
	return TRUE;
	case WM_LBUTTONUP:
		m_bLeftClick = FALSE;
		return TRUE;

	case WM_RBUTTONDOWN:
		if (m_bCommandSelecting == TRUE)
		{
			CUI_DetailSelect::GetInstance()->DestroyUI();
			CUI_ClearCondition::GetInstance()->HideUI();
			CUI_UnitDetailInfo::GetInstance()->HideUI();
			UI_CommandSelect->DestroyUI();
			m_bCommandSelecting = FALSE;
			m_pCurUnit = NULL;

			UI_CommandSelect->SetUnit(m_pCurUnit);

			UI_Notice->HideUI();
			UI_UnitInfo->HideUI();
			break;
		}
		m_ptMouseStart.x = LOWORD(lParam);
		m_ptMouseStart.y = HIWORD(lParam);
		if (m_pCurUnit != NULL)		// 유닛이 선택되어 있는 경우
		{
			if (m_phase == NoticePhase::None || m_phase == NoticePhase::OnlyAttackPhase)
			{
				m_pCurUnit->ClearMovableTile();
				m_pCurUnit->ClearAttackableTile();
				m_phase = NoticePhase::None;
				UI_Notice->HideUI();
				UI_UnitInfo->HideUI();

				m_pCurUnit = NULL;
			}
			if (m_phase == NoticePhase::AttackPhase || m_phase == NoticePhase::UnitWayPhase)
			{
				if (m_pCurUnit->GetCanMove())
				{
					m_phase = NoticePhase::None;
					UI_Notice->Update(NoticePhase::MoveNotice);

					m_map->SetUnitOnTile(m_pCurUnit->GetCurrentIndex(), NULL);
					m_pCurUnit->ClearAttackableTile();
					m_pCurUnit->ReturnToPrevPos();
					m_pCurUnit->ClearMovableTile();

					m_pCurUnit = NULL;

					m_phase = NoticePhase::None;
					UI_Notice->Update(NoticePhase::MoveNotice);
					UI_Notice->HideUI();
					UI_UnitInfo->HideUI();
				}
				else
				{
					m_pCurUnit->ClearMovableTile();
					m_pCurUnit->ClearAttackableTile();

					m_phase = NoticePhase::None;
					UI_Notice->Update(NoticePhase::MoveNotice);
					UI_Notice->HideUI();
					UI_UnitInfo->HideUI();

					m_pCurUnit = NULL;
				}
			}
			else if (m_phase == NoticePhase::SkillPhase)
			{
				m_phase = NoticePhase::None;
				UI_Notice->Update(NoticePhase::MoveNotice);
				UI_Notice->HideUI();
				UI_UnitInfo->HideUI();
				
				m_pCurUnit->ClearSkillTile();
				m_pCurUnit = NULL;
			}
			else if (m_phase == NoticePhase::WaitSkillPhase)
			{
				m_pCurUnit->ClearSkillTile();				//선택을 초기화합니다.
				m_pCurUnit = NULL;

				m_phase = NoticePhase::None;
				UI_Notice->Update(NoticePhase::MoveNotice);
				UI_Notice->HideUI();
			}

		}
		else							//유닛이 선택되어 있지 않은 경우
		{
			if (m_phase == NoticePhase::UsingSkillPhase
				|| m_phase == NoticePhase::EnemyPhase
				|| m_phase == NoticePhase::NoActPhase)
			{
				break;
			}
			POINT pos = m_ptMouseStart;
			INDEX idx;

			pos = m_map->GetTilePos(pos, &idx, camera);
			idx.height = m_map->GetHeight(idx);

			if (!idx.CheckInRange(m_map->GetColumn(), m_map->GetRow()))
				break;

			if (m_map->CheckIsUsableTile(idx) == FALSE)	//선택한 타일에 유닛이 있다면
			{
				m_pCurUnit = m_map->GetUnitOnTile(idx);	//선택한 타일에 있는 유닛을 현재 선택된 유닛으로 설정합니다.

				UI_UnitInfo->SetUnit(m_pCurUnit);		//정보를 출력할 유닛을 넘겨줍니다.
				UI_UnitInfo->OnUpdate();				//넘겨준 유닛으로 갱신합니다.
				UI_UnitInfo->MakeUI();
			}

			UI_CommandSelect->SetParent(this);			//
			CUI_UnitDetailInfo::GetInstance()->SetUnit(m_pCurUnit);
			//CUI_DetailSelect::GetInstance()->SetUnit(m_pCurUnit);
			CUI_DetailSelect::GetInstance()->SetParent(this);
			UI_CommandSelect->SetPos(m_ptMouseStart);
			UI_CommandSelect->MakeUI();
			UI_CommandSelect->SetUnit(m_pCurUnit);

			m_bCommandSelecting = TRUE;

			m_phase = NoticePhase::None;
			UI_Notice->Update(NoticePhase::MoveNotice);
			UI_Notice->HideUI();
			break;
		}
		return TRUE;

	case WM_MOUSEMOVE:
		if (m_bLeftClick)
		{
			m_ptMouseEnd.x = LOWORD(lParam);
			m_ptMouseEnd.y = HIWORD(lParam);

			camera.viewPoint.x += m_ptMouseEnd.x - m_ptMouseStart.x;
			camera.viewPoint.y += m_ptMouseEnd.y - m_ptMouseStart.y;

			m_ptMouseStart = m_ptMouseEnd;

			for (int i = 0; i < (int)m_vecUnits.size(); ++i)
			{
				m_vecUnits[i]->SetCamera(&camera);
			}
		}

		return TRUE;
	}

	return FALSE;
}
