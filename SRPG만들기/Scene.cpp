#include "stdafx.h"
#include "Scene.h"
#include "Tile.h"

CScene::CScene()
{
}

CScene::CScene(CFrameWork * framework, HWND hWnd)
{
	m_pFrameWork = framework;
	
	m_hWnd = hWnd;
	::GetClientRect(hWnd, &m_rcApp);

	m_pCurUnit = NULL;

	m_nTurnCount = 0;
	m_chCount = 0;
	m_nUnitNum = 0;
	m_nAlpha = 0;
}
CScene::~CScene()
{
}

void CScene::PlaySound()
{

}
void CScene::SetPhase(NoticePhase phase)
{ 
	m_phase = phase;
	CUI_Notice::GetInstance()->Update(phase);
	CUI_Notice::GetInstance()->HideUI();
}
BOOL CScene::OnProcessingKeyboardMessage(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	return FALSE;
}
BOOL CScene::OnProcessingMouseMessage(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	return FALSE;
}
BOOL CScene::OnProcessingWindowMessage(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	return FALSE;
}

void CScene::NewTurn()
{
	m_pFrameWork->GetSound()->PlayEffect(Sound_Name::EFFECT_NEW_TURN);
	for (int i = 0; i < (int)m_vecUnits.size(); ++i)
	{
		m_vecUnits[i]->SetCanAct(TRUE);
		m_vecUnits[i]->SetCanMove(TRUE);
		m_vecUnits[i]->ClearAttackableTile();
		m_vecUnits[i]->ClearMovableTile();
		m_vecUnits[i]->ClearSkillTile();
		m_vecUnits[i]->ClearTargetUnit();

		m_vecUnits[i]->SetNextCommand(KeyInput::Idle);
		m_vecUnits[i]->SetCurrentCommand(KeyInput::Idle);
		if (m_vecUnits[i]->GetHp() > 0)
		{
			m_vecUnits[i]->HandleInput(KeyInput::Idle);
		}
		m_vecUnits[i]->AddMp();
	}
	if (m_pCurUnit != NULL)
	{
		m_pCurUnit->ClearAttackableTile();
		m_pCurUnit->ClearMovableTile();
		m_pCurUnit->ClearSkillTile();
		m_pCurUnit = NULL;
	}
	
	m_nTurnCount++;
	//m_phase = NoticePhase::EnemyPhase;
}

BOOL CScene::ExecuteEnemyAct()
{
	//static int count;
	//int num = CalculateEnemyNum();
	
	m_map->CalculateEnemyAct(m_vecUnits[m_chCount++], m_vecUnits);
	if (m_chCount >= (int)m_vecUnits.size())
	{
		m_chCount = 0;
		return TRUE;
	}
	return FALSE;
}
int CScene::CalculateEnemyNum()
{
	int count = 0;
	for (int i = 0; i < (int)m_vecUnits.size(); ++i)
	{
		if (m_vecUnits[i]->GetUnitTeam() == UnitTeam::West)
		{
			count++;
		}
	}
	return count;
}
int CScene::CalculateAllyNum()
{
	int count = 0;

	for (int i = 0; i < (int)m_vecUnits.size(); ++i)
	{
		if (m_vecUnits[i]->GetUnitTeam() == UnitTeam::North)
		{
			count++;
		}
	}
	return count;
}
BOOL CScene::CheckGameLose()
{
	int num = CalculateAllyNum();
	int count = 0;

	for (int i = 0; i < (int)m_vecUnits.size(); ++i)
	{
		if (m_vecUnits[i]->GetHp() == 0
			&& m_vecUnits[i]->GetUnitTeam() == UnitTeam::North)
		{
			count++;
		}
	}
	if (num == count)
		return TRUE;
	return FALSE;
}
BOOL CScene::CheckGameWin()
{
	int num = CalculateEnemyNum();
	int count = 0;

	for (int i = 0; i < (int)m_vecUnits.size(); ++i)
	{
		if (m_vecUnits[i]->GetHp() == 0
			&& m_vecUnits[i]->GetUnitTeam() == UnitTeam::West)
		{
			count++;
		}
	}
	if (num == count)
		return TRUE;
	return FALSE;
}

void CScene::CheckAchievement()
{
	bool bOneUnitAllKill = false;

	for (int i = 0; i < (int)m_vecUnits.size(); ++i)
	{
		if (m_vecUnits[i]->GetKillNum() == m_vecUnits.size())
		{
			//CProfile::GetInstance()->GetAchievement().UnLock(Achievement::OneUnitAllKill);
			bOneUnitAllKill = TRUE;
		}
	}
	if (m_vecUnits.size() == m_nUnitNum)
	{
		//CProfile::GetInstance()->GetAchievement().UnLock(Achievement::NoKillClear);
	}
}

void CScene::SortUnitArrayUp()
{
	CUnit * temp;
	int min;
	POINT cur, compare;

	for (int i = 0; i < (int)m_vecUnits.size() - 1; ++i)
	{
		cur = m_vecUnits[i]->GetUnitPos();
		min = i;
		for (int j = i + 1; j < (int)m_vecUnits.size(); ++j)
		{
			compare = m_vecUnits[j]->GetUnitPos();

			if (cur.y == compare.y && cur.x > compare.x)
			{
				cur = compare;
				min = j;
			}
			else if (cur.y > compare.y - !(cur.x % 2))
			{

				cur = compare;
				min = j;
			}
		}

		if (min != i)
		{
			temp = m_vecUnits[i];
			m_vecUnits[i] = m_vecUnits[min];
			m_vecUnits[min] = temp;
		}
	}
}

void CScene::SortUnitArrayDown()
{
	CUnit * temp;
	int max;
	POINT cur, compare;

	for (int i = 0; i < (int)m_vecUnits.size() - 1; ++i)
	{
		cur = m_vecUnits[i]->GetUnitPos();
		max = i;
		for (int j = i + 1; j < (int)m_vecUnits.size(); ++j)
		{
			compare = m_vecUnits[j]->GetUnitPos();

			if (cur.y == compare.y && cur.x < compare.x)
			{
				cur = compare;
				max = j;
			}
			else if (cur.y < compare.y - !(cur.x % 2))
			{

				cur = compare;
				max = j;
			}
		}

		if (max != i)
		{
			temp = m_vecUnits[i];
			m_vecUnits[i] = m_vecUnits[max];
			m_vecUnits[max] = temp;
		}
	}
	for (int i = 0; i < (int)m_vecUnits.size() - 1; ++i)
	{
		for (int j = i; j < (int)m_vecUnits.size(); ++j)
		{
			if (m_vecUnits[i]->GetUnitTeam() == UnitTeam::North)
			{
				if (m_vecUnits[j]->GetUnitTeam() == UnitTeam::West)
				{
					temp = m_vecUnits[i];
					m_vecUnits[i] = m_vecUnits[j];
					m_vecUnits[j] = temp;
					break;
				}
			}
		}
	}
}