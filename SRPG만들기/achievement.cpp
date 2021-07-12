#include "stdafx.h"
#include "achievement.h"
void CAchievement::UnLock(Achievement achievement)
{
	switch (achievement)
	{
	case Achievement::NumerousEnemyKill:
		if (!m_bNumerousEnemyKill)
		{
			m_bNumerousEnemyKill = TRUE;
		}
		break;
	case Achievement::AllStageClear:
		if (!m_bAllStageClear)
		{
			m_bAllStageClear = TRUE;
		}
		break;
	case Achievement::NoKillClear:
		if (!m_bNoKillClear)
		{
			m_bNoKillClear = TRUE;
		}
		break;
	case Achievement::OneShotOneKill:
		if (!m_bOneShotOneKill)
		{
			m_bOneShotOneKill = TRUE;
		}
		break;
	case Achievement::OneUnitAllKill:
		if (!m_bOneUnitAllKill)
		{
			m_bOneUnitAllKill = TRUE;
		}
		break;
	case Achievement::Defeat3:
		if (!m_bDefeat3)
		{
			m_bDefeat3 = TRUE;
		}
		break;
	case Achievement::Accumulation1000:
		if (!m_bAccumulation1000)
		{
			m_bAccumulation1000 = TRUE;
		}
		break;
	case Achievement::Berserk:
		if (!m_bBerserk)
		{
			m_bBerserk = TRUE;
		}
		break;
	case Achievement::Achievement10:
		if (!m_bAchievement10)
		{
			m_bAchievement10 = TRUE;
		}
		break;
	case Achievement::Resurrection4:
		if (!m_bResurrection4)
		{
			m_bResurrection4 = TRUE;
		}
		break;
	case Achievement::AllAchievement:
		if (!m_bAllAchievement)
		{
			m_bAllAchievement = TRUE;
		}
		break;
	case Achievement::NewPlayer:
		if (!m_bNewPlayer)
		{
			m_bNewPlayer = TRUE;
		}
		break;
	case Achievement::AllSurviveClear:
		if (!m_bAllSurviveClear)
		{
			m_bAllSurviveClear = TRUE;
		}
		break;
	case Achievement::FirstClear:
		if (!m_bFirstClear)
		{
			m_bFirstClear = TRUE;
		}
		break;
	case Achievement::FirstDefeat:
		if (!m_bFirstDefeat)
		{
			m_bFirstDefeat = TRUE;
		}
		break;
	case Achievement::Retry:
		if (!m_bRetry)
		{
			m_bRetry = TRUE;
		}
		break;
	case Achievement::ReConnect:
		if (!m_bReConnect)
		{
			m_bReConnect = TRUE;
		}
		break;

	default:
		break;
	}
}
#pragma region 기능
void CAchievement::GetAchievement()
{
}
void CAchievement::StageUpdate(const CUnit& entity, Achievement achievement)
{
	switch (achievement)
	{
	case Achievement::AllStageClear:
		AllStageClear();
		break;
	case Achievement::NoKillClear:
		NoKillClear();
		break;
	case Achievement::Defeat3:
		Defeat3();
		break;
	case Achievement::AllSurviveClear:
		AllSurviveClear();
		break;
	case Achievement::FirstClear:
		FirstClear();
		break;
	case Achievement::FirstDefeat:
		FirstDefeat();
		break;
	case Achievement::Retry:
		Retry();
		break;
	default:
		break;
	}
}
void CAchievement::ETCUpdate(const CUnit& entity, Achievement achievement)
{
	switch (achievement)
	{
	case Achievement::Accumulation1000:
		Accumulation1000();
		break;
	case Achievement::Achievement10:
		Achievement10();
		break;
	case Achievement::AllAchievement:
		AllAchievement();
		break;
	case Achievement::NewPlayer:
		NewPlayer();
		break;
	case Achievement::ReConnect:
		ReConnect();
		break;
	}
}
void CAchievement::UnitUpdate(const CUnit& unit, Achievement achievement)
{
	switch (achievement)
	{
	case Achievement::NumerousEnemyKill:
		NumerousEnemyKill(unit);
		break;
	case Achievement::OneShotOneKill:
		OneShotOneKill(unit, 5);
		break;
	case Achievement::OneUnitAllKill:
		OneUnitAllKill(unit);
		break;
	case Achievement::Berserk:
		Berserk(unit);
		break;
	case Achievement::Resurrection4:
		Resurrection4(unit);
		break;
	default:
		break;
	}
}
#pragma endregion
void CAchievement::NumerousEnemyKill(const CUnit& entity)
{
	BOOL Switch;
	{
		//어떠한 연산
		Switch = TRUE;
	}
	if (Switch)
		UnLock(Achievement::NumerousEnemyKill);
}
void CAchievement::AllStageClear()
{
	BOOL Switch;
	{
		//어떠한 연산
		Switch = TRUE;
	}
	if (Switch)
		UnLock(Achievement::AllStageClear);
}
void CAchievement::NoKillClear()
{
	BOOL Switch;
	{
		//어떠한 연산
		Switch = TRUE;
	}
	if (Switch)
		UnLock(Achievement::NoKillClear);
}
void CAchievement::OneShotOneKill(const CUnit& entity, int damage)
{
	BOOL Switch;
	{
		Switch = TRUE;
	}
	if (Switch)
		UnLock(Achievement::OneShotOneKill);
}
void CAchievement::OneUnitAllKill(const CUnit& entity)
{
	BOOL Switch;
	{
		//어떠한 연산
		Switch = TRUE;
	}
	if (Switch)
		UnLock(Achievement::OneUnitAllKill);
}
void CAchievement::Defeat3()
{
	BOOL Switch;
	{
		//어떠한 연산
		Switch = TRUE;
	}
	if (Switch)
		UnLock(Achievement::Defeat3);
}
void CAchievement::Accumulation1000()
{
	BOOL Switch;
	{
		//어떠한 연산
		Switch = TRUE;
	}
	if (Switch)
		UnLock(Achievement::Accumulation1000);
}
void CAchievement::Berserk(const CUnit& entity)
{
	BOOL Switch;
	{
		//어떠한 연산
		Switch = TRUE;
	}
	if (Switch)
		UnLock(Achievement::Berserk);
}
void CAchievement::Achievement10()
{
	BOOL Switch;
	{
		//어떠한 연산
		Switch = TRUE;
	}
	if (Switch)
		UnLock(Achievement::Achievement10);
}
void CAchievement::AllAchievement()
{
	BOOL Switch;
	{
		//어떠한 연산
		Switch = TRUE;
	}
	if (Switch)
		UnLock(Achievement::AllAchievement);
}
void CAchievement::Resurrection4(const CUnit& entity)
{
	BOOL Switch;
	{
		//어떠한 연산
		Switch = TRUE;
	}
	if (Switch)
		UnLock(Achievement::Resurrection4);
}
void CAchievement::NewPlayer()
{
	BOOL Switch;
	{
		//어떠한 연산
		Switch = TRUE;
	}
	if (Switch)
		UnLock(Achievement::NewPlayer);
}
void CAchievement::AllSurviveClear()
{
	BOOL Switch;
	{
		//어떠한 연산
		Switch = TRUE;
	}
	if (Switch)
		UnLock(Achievement::AllSurviveClear);
}
void CAchievement::FirstClear()
{
	BOOL Switch;
	{
		//어떠한 연산
		Switch = TRUE;
	}
	if (Switch)
		UnLock(Achievement::FirstClear);
}
void CAchievement::FirstDefeat()
{
	BOOL Switch;
	{
		//어떠한 연산
		Switch = TRUE;
	}
	if (Switch)
		UnLock(Achievement::FirstDefeat);
}
void CAchievement::Retry()
{
	BOOL Switch;
	{
		//어떠한 연산
		Switch = TRUE;
	}
	if (Switch)
		UnLock(Achievement::Retry);
}
void CAchievement::ReConnect()
{
	BOOL Switch;
	{
		//어떠한 연산
		Switch = TRUE;
	}
	if (Switch)
		UnLock(Achievement::ReConnect);
}
BOOL CAchievement::GetNumerousEnemyKill()
{
	return m_bNumerousEnemyKill;
}
BOOL CAchievement::GetAllStageClear()
{
	return m_bAllStageClear;
}
BOOL CAchievement::GetNoKillClear()
{
	return m_bNoKillClear;
}
BOOL CAchievement::GetOneShotOneKill()
{
	return m_bOneShotOneKill;
}
BOOL CAchievement::GetOneUnitAllKill()
{
	return m_bOneUnitAllKill;
}
BOOL CAchievement::GetDefeat3()
{
	return m_bDefeat3;
}
BOOL CAchievement::GetAccumulation1000()
{
	return m_bAccumulation1000;
}
BOOL CAchievement::GetBerserk()
{
	return m_bBerserk;
}
BOOL CAchievement::GetAchievement10()
{
	return m_bAchievement10;
}
BOOL CAchievement::GetResurrection4()
{
	return m_bResurrection4;
}
BOOL CAchievement::GetAllAchievement()
{
	return m_bAllAchievement;
}
BOOL CAchievement::GetNewPlayer()
{
	return m_bNewPlayer;
}
BOOL CAchievement::GetAllSurviveClear()
{
	return m_bAllSurviveClear;
}
BOOL CAchievement::GetFirstClear()
{
	return m_bFirstClear;
}
BOOL CAchievement::GetFirstDefeat()
{
	return m_bFirstDefeat;
}
BOOL CAchievement::GetRetry()
{
	return m_bRetry;
}
BOOL CAchievement::GetReConnect()
{
	return m_bReConnect;
}
