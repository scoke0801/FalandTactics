#include "stdafx.h"
#include "stage6.h"

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

CStage6::CStage6(CFrameWork * framework, HWND hWnd, CurrentScene tag)
	:CScene(framework, hWnd)
{
	INDEX idx;
	int nRandom;
	m_map = new CMap(_T("resource/map/������.txt"));
	//m_map->LoadUnit(_T("resource/map/���_����.txt"), &m_vecUnits);

	nRandom = rand() % 18;

	for (int i = 0; i < 2; ++i)
	{
		nRandom = rand() % 18;
		if (i == 0)
		{
			idx = m_map->GetTilePos(16, 4);
			idx.height = m_map->GetHeight(INDEX{ 16,4,0 });
		}
		else
		{
			idx = m_map->GetTilePos(4, 4);
			idx.height = m_map->GetHeight(INDEX{ 4,4,0 });
		}
		switch ((UnitName)nRandom)
		{
		case UnitName::Aris:
			m_vecUnits.push_back(new CAris(idx));
			break;
		case UnitName::Arl:
			m_vecUnits.push_back(new CArl(idx));
			break;
		case UnitName::BlackKnight:
			m_vecUnits.push_back(new CBlackKnight(idx));
			break;
		case UnitName::Cat:
			m_vecUnits.push_back(new CCat(idx));
			break;
		case UnitName::Catherine:
			m_vecUnits.push_back(new CCatherine(idx));
			break;
		case UnitName::Crab:
			m_vecUnits.push_back(new CCrab(idx));
			break;
		case UnitName::Fairy:
			m_vecUnits.push_back(new CFairy(idx));
			break;
		case UnitName::Farm:
			m_vecUnits.push_back(new CFarm(idx));
			break;
		case UnitName::Ivan:
			m_vecUnits.push_back(new CIvan(idx));
			break;
		case UnitName::Karin:
			m_vecUnits.push_back(new CKarin(idx));
			break;
		case UnitName::Marcia:
			m_vecUnits.push_back(new CMarcia(idx));
			break;
		case UnitName::Reon:
			m_vecUnits.push_back(new CReon(idx));
			break;
		case UnitName::Rian:
			m_vecUnits.push_back(new CRian(idx));
			break;
		case UnitName::Rucia:
			m_vecUnits.push_back(new CRucia(idx));
			break;
		case UnitName::Ruru:
			m_vecUnits.push_back(new CRuru(idx));
			break;
		case UnitName::Shon:
			m_vecUnits.push_back(new CShon(idx));
			break;
		case UnitName::Wolf:
			m_vecUnits.push_back(new CWolf(idx));
			break;
		case UnitName::YoungKarin:
			m_vecUnits.push_back(new CYoungKarin(idx));
		
			break;
		}
	}
	idx = m_map->GetTilePos(16, 4);
	idx.height = m_map->GetHeight(INDEX{ 16,4,0 });
	m_map->SetUnitOnTile(INDEX{ 16,4, m_map->GetHeight(idx) }, m_vecUnits[0]);
	m_vecUnits[0]->SetTeam(UnitTeam::North);
	m_vecUnits[0]->SetUnitWay(UnitWay::LeftDown);

	idx = m_map->GetTilePos(4, 4);
	idx.height = m_map->GetHeight(INDEX{ 4,4,0 });
	m_map->SetUnitOnTile(INDEX{ 4,4, m_map->GetHeight(idx) }, m_vecUnits[1]);
	m_vecUnits[1]->SetTeam(UnitTeam::West);
	m_vecUnits[1]->SetUnitWay(UnitWay::RightDown);
	
	for (int i = 0; i < 2; ++i)
	{
		m_vecUnits[i]->ClearSkillList();
		for (int j = 0; j < 3; ++j)
			m_vecUnits[i]->AddSkill((SKillName)(rand() % 15));
	}
	for (int i = 0; i < (int)m_vecUnits.size(); ++i)
	{
		m_vecUnits[i]->SetSound(m_pFrameWork->GetSound());
		m_vecUnits[i]->SetStage(this);
	}
	SortUnitArrayUp();

	m_pFrameWork->GetSound()->AddStream(("resource/sound/BGM/STAGE6_BGM.mp3"), Sound_Name::BGM_STAGE6);
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
	
	camera.viewPoint.x = 220;
	camera.viewPoint.y = 200;

	m_bCommandSelecting = TRUE;
	CUI_ClearCondition::GetInstance()->SetPhase(CScene::CurrentScene::Stage6);
	CUI_ClearCondition::GetInstance()->MakeUI();
}
CStage6::~CStage6()
{
	delete m_map;
}

void CStage6::OnUpdate(float timeElapsed)
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
void CStage6::OnDraw(HDC hdc)
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
void CStage6::DrawIntervalScene(HDC hdc)
{
	//static int count = 0;
	COLORREF removeColor = RGB(255, 0, 255);		//���� ����
	//static int alpha = 0;				//����

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
		m_nAlpha += 1;
	}
	else
	{
		if (CheckGameWin())
		{
			//CProfile::GetInstance()->AddStageClear();		//�¸� Ƚ�� �߰�
			//CProfile::GetInstance()->AddStageClear(6);
			//CheckAchievement();
			
			//m_pFrameWork->ChangeScene(CurrentScene::Title);
			m_pFrameWork->ChangeScene(CScene::CurrentScene::GameWin);
		}
		if (CheckGameLose())
		{
			//CProfile::GetInstance()->AddStageDefeat();		//�й� Ƚ�� �߰�
			//CheckAchievement();
			m_pFrameWork->ChangeScene(CScene::CurrentScene::GameLose);
		}
	}
}


void CStage6::PlaySound()
{
	m_pFrameWork->GetSound()->PlayBgm(Sound_Name::BGM_STAGE6);
}
BOOL CStage6::OnProcessingKeyboardMessage(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
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
BOOL CStage6::OnProcessingMouseMessage(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
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

			//m_pCurUnit = m_map->GetUnitOnTile(idx); //���� ������ Ŭ���� Ÿ�Ͽ� �ִ� �������� ����
			m_pCurUnit->HandleInput(KeyInput::Move);		//������ ������ Ÿ�Ϸ� �̵���ŵ�ϴ�.
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

		if (m_phase == NoticePhase::None)	//������ �ൿ�ϱ� ��
		{
			if (m_pCurUnit == NULL)					//������ ���õǾ� ���� ���� ���
			{
				if (m_map->CheckIsUsableTile(idx) == FALSE) //Ŭ���� Ÿ�Ͽ� ������ �ִ� ���
				{
					if (m_map->GetUnitOnTile(idx)->GetUnitTeam() != UnitTeam::North)
					{
						m_pCurUnit = m_map->GetUnitOnTile(idx);
						UI_UnitInfo->SetUnit(m_map->GetUnitOnTile(idx));
						UI_UnitInfo->MakeUI();					//������ ������ HP,MP�� ����ϴ� UI�� �����մϴ�.
						break;
					}
					m_pCurUnit = m_map->GetUnitOnTile(idx); //���� ������ Ŭ���� Ÿ�Ͽ� �ִ� �������� ����
					m_map->CheckMovableTile(m_pCurUnit);	//������ �̵������� Ÿ���� Ȯ���մϴ�.

					UI_UnitInfo->SetUnit(m_pCurUnit);
					UI_UnitInfo->MakeUI();					//������ ������ HP,MP�� ����ϴ� UI�� �����մϴ�.

					if (!m_pCurUnit->GetCanMove())
					{
						if (m_map->CheckContiguousEnemy(idx))
						{
							UI_Notice->MakeUI();
							UI_Notice->Update(NoticePhase::AttackPhase);	//���� ���� UI�� �����մϴ�.
							m_phase = NoticePhase::OnlyAttackPhase;				//�ִٸ� ���� ����� �����ϵ��� �մϴ�.
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
					if (m_map->CheckContiguousEnemy(idx))	//������ �̵����� ���� ��ġ���� ���� ������ �� �ִ��� �˻��մϴ�.
					{
						UI_Notice->Update(NoticePhase::AttackPhase);	//���� ���� UI�� �����մϴ�.
						m_phase = NoticePhase::OnlyAttackPhase;				//�ִٸ� ���� ����� �����ϵ��� �մϴ�.
						break;
					}

					if (m_pCurUnit->GetCanMove() && m_pCurUnit->GetCanAttack())
					{
						//�˸��� UI�� �����մϴ�.
						m_phase = NoticePhase::None;
						UI_Notice->Update(NoticePhase::MoveNotice);
					}
					else if (m_pCurUnit->GetCanMove())
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
			else									//������ ���õǾ� �ִ� ���
			{
				if (m_pCurUnit == m_map->GetUnitOnTile(idx))	//���� ���ְ� ���Ӱ� ������ ������ ���ٸ�
					break;										//�ǳʶݴϴ�.

				if (m_map->CheckIsUsableTile(idx) == FALSE)	//Ŭ���� Ÿ�Ͽ� ������ �ִ� ���
				{
					if (m_map->GetUnitOnTile(idx)->GetUnitTeam() != UnitTeam::North)
					{
						m_pCurUnit = m_map->GetUnitOnTile(idx);
						UI_UnitInfo->SetUnit(m_map->GetUnitOnTile(idx));
						UI_UnitInfo->MakeUI();					//������ ������ HP,MP�� ����ϴ� UI�� �����մϴ�.
						m_bLeftClick = FALSE;
						break;
					}
					m_pCurUnit->ClearMovableTile();
					m_pCurUnit->ClearAttackableTile();
					m_pCurUnit = m_map->GetUnitOnTile(idx);	//���Ӱ� ���õ� Ÿ�Ͽ� �ִ� �������� ���� ������ �����մϴ�.

					m_map->CheckMovableTile(m_pCurUnit);	//������ �̵������� Ÿ���� Ȯ���մϴ�.

					UI_UnitInfo->SetUnit(m_pCurUnit);
					UI_UnitInfo->OnUpdate();

					if (m_pCurUnit->GetCanMove() && m_pCurUnit->GetCanAttack())
						UI_Notice->MakeUI();					//�˸��� UI�� �����մϴ�.

					m_bLeftClick = FALSE;

				}
				else								//Ŭ���� Ÿ�Ͽ� ������ ���� ���
				{
					if (m_pCurUnit->CheckIsMovableTile(idx))	//���� ������ �̵����� Ÿ�� ��Ͽ� ������ Ÿ���� �ִ��� Ȯ���մϴ�.
					{											//�̵����� Ÿ�� ��Ͽ� �ִ� ���
						m_pCurUnit->SetNextTile(idx);
						m_pCurUnit->SetPrevTile(m_pCurUnit->GetCurrentIndex());
						m_pCurUnit->SetCurrentTile(idx);

						//m_pCurUnit->SetCurrentPos(POINT{ idx.GetXPos(), idx.GetYPos() });
						m_pCurUnit->SetCurrentPos(m_map->GetTilePos(idx.x, idx.y));
						m_map->SetUnitOnTile(idx, m_pCurUnit);
						if (m_map->CheckContiguousEnemy(idx))	//�̵��� ��ġ���� �� ������ �ִ��� �˻��մϴ�.
						{
							UI_Notice->Update(NoticePhase::AttackPhase);	//���� ���� UI�� �����մϴ�.
							m_phase = NoticePhase::AttackPhase;				//�ִٸ� ���� ����� �����ϵ��� �մϴ�.
						}
						else
						{
							UI_Notice->Update(NoticePhase::UnitWayPhase);	//���� ���� ���� ���� UI�� �����մϴ�.
							m_phase = NoticePhase::UnitWayPhase;			//���ٸ� ������ ������ �����ϰ� �մϴ�.
						}
						m_bLeftClick = FALSE;
					}
				}

			}
		}
		else if (m_phase == NoticePhase::OnlyAttackPhase)			//���ݸ� �ϴ� �б�
		{
			if (m_pCurUnit->CheckIsAttackableTile(idx))				//���ݰ��� Ÿ���̶��
			{
				m_pCurUnit->SetTargetUnit(m_map->GetUnitOnTile(idx));	//������ ���ֿ� ������ Ÿ�Ͽ� �ִ� ������ �߰��մϴ�.
				m_pCurUnit->SetNextCommand(KeyInput::Attack);

				if (m_pCurUnit->GetCanAttack())
					m_pCurUnit->HandleInput(KeyInput::Attack);

				m_phase = NoticePhase::NoActPhase;
				m_pCurUnit->ClearAttackableTile();

				m_pCurUnit = NULL;

				UI_UnitInfo->HideUI();
				UI_Notice->HideUI();
			}
			else								//���� ���� Ÿ���� �ƴ� ���
			{
				m_pCurUnit->ClearAttackableTile();	//���� ���� Ÿ���� �ʱ�ȭ �մϴ�.

				m_phase = NoticePhase::None;
				UI_Notice->Update(NoticePhase::MoveNotice);
			}
		}
		else if (m_phase == NoticePhase::AttackPhase) //�̵� - ���� �ϴ� �б�
		{
			if (m_pCurUnit->CheckIsAttackableTile(idx))	//���� ������ ���ݰ��� Ÿ�� ��Ͽ� ������ Ÿ���� �ִ��� Ȯ���մϴ�.
			{											//���ݰ��� Ÿ�� ��Ͽ� �ִ� ���
				if (m_pCurUnit->GetCanMove())
					m_map->SetUnitOnTile(m_pCurUnit->GetPrevTileIndex(), NULL);
				m_pCurUnit->SetTargetUnit(m_map->GetUnitOnTile(idx));	//������ ���ֿ� ������ Ÿ�Ͽ� �ִ� ������ �߰��մϴ�.
				m_pCurUnit->SetNextCommand(KeyInput::Attack);

				if (m_pCurUnit->GetCanMove())
					m_pCurUnit->HandleInput(KeyInput::Move);		//������ ������ Ÿ�Ϸ� �̵���ŵ�ϴ�.
				else if (m_pCurUnit->GetCanAttack())
					m_pCurUnit->HandleInput(KeyInput::Attack);

				m_phase = NoticePhase::NoActPhase;
				m_pCurUnit->ClearAttackableTile();

				m_pCurUnit = NULL;

				UI_UnitInfo->HideUI();
				UI_Notice->HideUI();

				//SortUnitArray();
			}
			else							//���ݰ��� ��Ͽ� ���� ���
			{								//�������� �ʰ� �̵��� �մϴ�.
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

		else if (m_phase == NoticePhase::SkillPhase)	//��ų ��� �б�
		{
			if (m_pCurUnit->CheckIsSkillTile(idx))		//������ Ÿ���� ��ų ���� ������ Ȯ���մϴ�.
			{											//�´� ���
				m_map->CheckSkillTile(m_pCurUnit, idx, m_pCurUnit->GetCurrentSkill()); //�ش� ������ �� ��ų�� ���������� ��ų Ÿ���� �����մϴ�.
				UI_Notice->MakeUI();
				m_phase = NoticePhase::WaitSkillPhase;	//���� ������ ��ų ������ ���� ���Է��� ��ٸ��ϴ�.
				UI_Notice->Update(NoticePhase::WaitSkillPhase);
				//m_pCurUnit->EnterNextState();
				//m_pCurUnit->SetNextCommand(KeyInput::Stop);
				//m_pCurUnit->SetSkillPos(POINT{ idx.GetXPos(), idx.GetYPos() });
				//m_phase = NoticePhase::UsingSkillPhase;

				//UI_Notice->HideUI();
			}
			//else
			//{    //�ƴ� ���
			//	m_pCurUnit->ClearSkillTile();	//������ �ʱ�ȭ�մϴ�.
			//	m_pCurUnit = NULL;

			//	m_phase = NoticePhase::None;
			//	UI_Notice->Update(NoticePhase::MoveNotice);
			//	UI_Notice->HideUI();
			//	UI_UnitInfo->HideUI();
			//}
		}
		else if (m_phase == NoticePhase::WaitSkillPhase)	// ��ų ��� Ȯ�� �б�
		{
			if (m_pCurUnit->CheckIsSkillTile(idx))			//Ŭ���� Ÿ���� ��ų ���� �ȿ� �ִ��� Ȯ���մϴ�.
			{
				m_pCurUnit->SetSkillTarget();
				m_pCurUnit->EnterNextState();				//��ų �����·� �����մϴ�.
															//m_pCurUnit->SetNextCommand(KeyInput::Stop);
				m_phase = NoticePhase::UsingSkillPhase;

				UI_Notice->HideUI();
				UI_UnitInfo->HideUI();
			}
			//else
			//{												//���� ���
			//	m_pCurUnit->ClearSkillTile();				//������ �ʱ�ȭ�մϴ�.
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
		if (m_pCurUnit != NULL)		// ������ ���õǾ� �ִ� ���
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
				m_pCurUnit->ClearSkillTile();				//������ �ʱ�ȭ�մϴ�.
				m_pCurUnit = NULL;

				m_phase = NoticePhase::None;
				UI_Notice->Update(NoticePhase::MoveNotice);
				UI_Notice->HideUI();
			}

		}
		else							//������ ���õǾ� ���� ���� ���
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

			if (m_map->CheckIsUsableTile(idx) == FALSE)	//������ Ÿ�Ͽ� ������ �ִٸ�
			{
				m_pCurUnit = m_map->GetUnitOnTile(idx);	//������ Ÿ�Ͽ� �ִ� ������ ���� ���õ� �������� �����մϴ�.

				UI_UnitInfo->SetUnit(m_pCurUnit);		//������ ����� ������ �Ѱ��ݴϴ�.
				UI_UnitInfo->OnUpdate();				//�Ѱ��� �������� �����մϴ�.
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
