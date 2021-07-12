#include "stdafx.h"
#include "Command.h"
#include "Unit.h"
#include "SkillImage.h"

void CGameCommand::SetUnitInfo(CUnit* unit)
{
	m_pUnit = unit;
}
CUnit* CGameCommand::Undo(CUnit* unit)
{
	//if(m_pUnit)
	return m_pUnit;
}

BOOL CGameCommand::Execute(CUnit* unit)
{
	
	return TRUE;
}
BOOL CDefenseCommand::Execute(CUnit* unit)
{
	return NULL;
}

CMoveCommand::CMoveCommand(CUnit* unit)
{
	INDEX idx = unit->GetNextTileIndex();
	Node* node = unit->GetMovableTile().find(idx)->second;

	while (node != NULL)
	{
		m_vecMoveTile.push_back(node);
		node = node->link;
	}
	m_nCurrentIndex = m_vecMoveTile.size() - 1;
}
BOOL CMoveCommand::Execute(CUnit* unit)
{
	static int count = 0;

	if (m_nCurrentIndex < 0)
	{
		unit->ClearMovableTile();
		unit->SetNextTile(unit->GetCurrentIndex());
		unit->SetUnitWay(unit->GetNextUnitWay());
		unit->SetCanMove(FALSE);
		return TRUE;
	}
	count++;
	if (count > 9)
	{
		unit->PlayMoveEffect();
		if (m_nCurrentIndex - 1 >= 0)
		{
			unit->SetUnitWay(
				unit->CheckUnitWay(
					m_vecMoveTile[m_nCurrentIndex]->GetIndex()
					, m_vecMoveTile[m_nCurrentIndex - 1]->GetIndex())
				);
		}
		unit->SetCurrentTile(m_vecMoveTile[m_nCurrentIndex]->GetIndex());
		unit->SetCurrentPos(m_vecMoveTile[m_nCurrentIndex--]->GetLeftTop());
		count = 0;
	}
	return FALSE;
}

CAttackCommand::CAttackCommand(CUnit* unit)
{
	m_pTarget = unit->GetTargetUnit(0);
	
	if (m_pTarget == NULL)
		return;
	if (m_pTarget->CheckDeffense())
	{
		int temp = (int)unit->CheckUnitWay(
			unit->GetCurrentIndex()
			, unit->GetTargetUnit(0)->GetCurrentIndex());
		if (temp == 0)
			temp = 3;
		else if (temp == 1)
			temp = 2;
		else if (temp == 2)
			temp = 1;
		else if (temp == 3)
			temp = 0;
		m_pTarget->SetUnitWay((UnitWay)temp);
		m_pTarget->SetLastDamage(1000);			//miss출력하도록 설정합니다, 값이 4자리이상이면 miss출력하도록 설정
		m_pTarget->HandleInput(KeyInput::Defense);
		return;
	}

	unit->CalculateDamage(m_pTarget);
	if (m_pTarget->GetHp() <= 0)
	{
		if (m_pTarget->GetUnitTeam() == UnitTeam::West)	//죽은 유닛이 적군 유닛이라면
		{
			unit->IncreaseKillNum();
			//if (!m_pTarget->GetHitted())	//타겟 유닛이 이전에 맞은 적이 없는 유닛이라면
			//{								//oneshotonekill 업적 해제
			//	CProfile::GetInstance()->GetAchievement().UnLock(Achievement::OneShotOneKill);
			//}
			//CProfile::GetInstance()->AddAccumulationKill();	//누적 킬 수 추가
		}
		m_pTarget->ClearMovableTile();
		m_pTarget->SetCanAct(FALSE);
		m_pTarget->SetCanMove(FALSE);

		//m_pTarget->HandleInput(KeyInput::Die);
	}
	
	m_pTarget->HandleInput(KeyInput::Attacked);
	m_pTarget->SetHitted(TRUE);
	//unit->PlayAttackEffect();
}

BOOL CAttackCommand::Execute(CUnit* unit)
{
	if (unit->CheckAnimationEnd())
	{
		unit->SetCanAct(FALSE);
		return TRUE;
	}
	
	return FALSE;
}

CAttackedCommand::CAttackedCommand()
{
	m_delay = 1;
}
BOOL CAttackedCommand::Execute(CUnit* unit)
{
	/*if (unit->CheckAnimationEnd())
	{
		m_delay--;
		if (m_delay <= 0)
		{
			m_delay = 1;
			return TRUE;
		}
	}*/
	if (unit->GetHp() <= 0)
		return TRUE;
	return FALSE;
}


CSkillCommand::CSkillCommand(CUnit* unit)
{
	m_nImagePos[0] = 0;
	m_nImagePos[1] = 0;
	m_nSkillRange = 1;

	m_ptPos = { 0,0 };

	m_pUnit = unit;
}
void CSkillCommand::Enter()
{
	std::vector<CUnit*> vecTarget = m_pUnit->GetTargetUnit();
	int mp = m_pUnit->GetMp() - m_nMpConsumption;
	
	if (mp < 0)
		mp = 0;
	m_pUnit->SetMp(mp);

	for (int i = 0; i < (int)vecTarget.size(); ++i)
	{
		if (m_pUnit->GetTargetUnit(i) != NULL)
		{
			m_pTarget = m_pUnit->GetTargetUnit(i);
			if (!m_pUnit->CheckEnemy(m_pTarget))
			{
				continue;
			}
			if (m_pTarget->GetHp() <= 0)
				continue;
			m_pUnit->CalculateSkillDamage(m_pTarget);
			if (m_pTarget->GetHp() <= 0)
			{
				if (m_pTarget->GetUnitTeam() == UnitTeam::West)	//죽은 유닛이 적군 유닛이라면
				{
					m_pUnit->IncreaseKillNum();
					//if (!m_pTarget->GetHitted())	//타겟 유닛이 이전에 맞은 적이 없는 유닛이라면
					//{								//oneshotonekill 업적 해제
					//	CProfile::GetInstance()->GetAchievement().UnLock(Achievement::OneShotOneKill);
					//}
					//CProfile::GetInstance()->AddAccumulationKill();	//누적 킬 수 추가
				}
				m_pTarget->ClearMovableTile();
				m_pTarget->SetCanAct(FALSE);
				m_pTarget->SetCanMove(FALSE);
				//m_pTarget->HandleInput(KeyInput::Die);
			}
			m_pTarget->SetHitted(TRUE);
			m_pTarget->HandleInput(KeyInput::Attacked);
		}
	}
}
CSkillCommand::~CSkillCommand()
{

}

BOOL CSkillCommand::Execute(CUnit* unit)
{
	std::vector<CUnit*> vecTarget = unit->GetTargetUnit();


	if (unit->GetUnitTeam() == UnitTeam::West)
	{
		unit->GetStage()->SetPhase(NoticePhase::EnemyPhase);
	}
	else
		unit->GetStage()->SetPhase(NoticePhase::None);

	if (unit->GetCanMove())
	{
		unit->SetCurrentCommand(KeyInput::Idle);
		unit->HandleInput(KeyInput::Idle);
	}
	else
	{
		unit->SetCurrentCommand(KeyInput::Stop);
		unit->HandleInput(KeyInput::Stop);
	}
	
	for (int i = 0; i < (int)vecTarget.size(); ++i)
	{
		if (vecTarget[i] != NULL)
		{
			if (vecTarget[i]->GetHp() > 0)
			{
				vecTarget[i]->HandleInput(
					vecTarget[i]->GetCurrentCommand()
					);
			}
		}
	}
	unit->ClearSkillTile();
	return FALSE;
}

BOOL CSkillCommand::CheckSkillEnd()
{
	return FALSE;
}
void CSkillCommand::UpdateSprite()
{
	m_nImagePos[0]++;

	if (m_nImagePos[0] > 3)
	{
		m_nImagePos[0] = 0;
		m_nImagePos[1]++;
	}
}

CBurstSkill::CBurstSkill(int skillRange, SkillAttackType type, CUnit* unit, int mpConsumtion)
	:CSkillCommand(unit)
{
	m_nSkillRange = skillRange;
	m_attackType = type;
	m_nMpConsumption = mpConsumtion;
}

CBurstSkill::~CBurstSkill()
{

}


void CBurstSkill::DrawSkill(HDC hdc, Camera camera)
{
	CSkillImage::GetInstance()->DrawBurst(hdc
		, m_ptPos
		, m_nImagePos[1]
		, camera
		);
}
BOOL CBurstSkill::CheckSkillEnd()
{
	if (m_nImagePos[1] > 11)
	{
		//m_nImagePos[1] = 0;
		return TRUE;
	}
	return FALSE;
}

void CBurstSkill::PlayEffect() 
{
	m_pUnit->PlayEffect(Sound_Name::EFFECT_BURST);
}

CAidSkill::CAidSkill(int skillRange, SkillAttackType type, CUnit* unit, int mpConsumption, int kind)
	:CSkillCommand(unit)
{
	m_nSkillRange = skillRange;
	m_attackType = type;
	m_nMpConsumption = mpConsumption;
	m_nKind = kind;

	
}
CAidSkill::~CAidSkill()
{

}
void CAidSkill::Enter()
{
	if (m_pUnit->CheckIsSkillTile(m_pUnit->GetCurrentIndex())
		&& !m_pUnit->CheckIsTarget(m_pUnit))
	{
		m_pUnit->AddTarget(m_pUnit);
	}
	std::vector<CUnit*> vecTarget = m_pUnit->GetTargetUnit();
	int mp = m_pUnit->GetMp() - m_nMpConsumption;

	if (mp < 0)
		mp = 0;
	m_pUnit->SetMp(mp);

	for (int i = 0; i < (int)vecTarget.size(); ++i)
	{
		if (m_pUnit->GetTargetUnit(i) != NULL)
		{
			m_pTarget = m_pUnit->GetTargetUnit(i);
			if (m_pUnit->CheckEnemy(m_pTarget)) //적팀인 경우
			{
				continue;						//증감문으로 이동
			}
			if (m_pTarget->GetHp() <= 0)		//죽어있는 경우
				continue;
			if (m_nKind == 0)
				m_pUnit->CalculateHealAmount(m_pTarget);
			else
				m_pUnit->CalculateMpHealAmount(m_pTarget);
			m_pTarget->SetNextCommand(KeyInput::Heal);
		}
	}

}

BOOL CAidSkill::Execute(CUnit* unit)
{
	std::vector<CUnit*> vecTarget = unit->GetTargetUnit();


	if (unit->GetUnitTeam() == UnitTeam::West)
	{
		unit->GetStage()->SetPhase(NoticePhase::EnemyPhase);
	}
	else
		unit->GetStage()->SetPhase(NoticePhase::None);

	if (unit->GetCanMove())
	{
		unit->SetCurrentCommand(KeyInput::Idle);
		unit->HandleInput(KeyInput::Idle);
	}
	else
	{
		unit->SetCurrentCommand(KeyInput::Stop);
		unit->HandleInput(KeyInput::Stop);
	}

	for (int i = 0; i < (int)vecTarget.size(); ++i)
	{
		if (vecTarget[i] != NULL)
		{
			if (vecTarget[i]->GetHp() > 0)
			{
				vecTarget[i]->HandleInput(
					vecTarget[i]->GetCurrentCommand()
					);
				vecTarget[i]->SetNextCommand(KeyInput::Idle);
			}
		}
	}
	unit->ClearSkillTile();

	return FALSE;
}

void CAidSkill::DrawSkill(HDC hdc,Camera camera )
{
	CSkillImage::GetInstance()->DrawAid(hdc
		, m_ptPos
		, m_nImagePos[1]
		, m_nKind
		, camera
		);
}

BOOL CAidSkill::CheckSkillEnd()
{
	if (m_nImagePos[1] > 19)
	{
		//m_nImagePos[1] = 0;
		return TRUE;
	}
	return FALSE;
}

void CAidSkill::PlayEffect()
{
	m_pUnit->PlayEffect(Sound_Name::EFFECT_AID);
}

CResurrectionSkill::CResurrectionSkill(int skillRange, SkillAttackType type, CUnit* unit, int mpConsumption)
	:CSkillCommand(unit)
{
	m_nSkillRange = skillRange;
	m_attackType = type;
	m_nMpConsumption = mpConsumption;
}
CResurrectionSkill::~CResurrectionSkill()
{

}
void CResurrectionSkill::Enter()
{
	std::vector<CUnit*> vecTarget = m_pUnit->GetTargetUnit();
	int mp = m_pUnit->GetMp() - m_nMpConsumption;

	if (mp < 0)
		mp = 0;
	m_pUnit->SetMp(mp);

	for (int i = 0; i < (int)vecTarget.size(); ++i)
	{
		if (m_pUnit->GetTargetUnit(i) != NULL)
		{
			m_pTarget = m_pUnit->GetTargetUnit(i);
			if (m_pUnit->CheckEnemy(m_pTarget)) //적팀인 경우
			{
				continue;						//증감문으로 이동
			}
			if (m_pTarget->GetHp() != 0)		//살아있는 경우
			{
				m_pTarget->SetLastDamage(1000);
				m_pTarget->SetNextCommand(KeyInput::Heal);
				continue;						//증감문으로 이동
			}
			m_pUnit->IncreaseResurrectionNum();
			m_pUnit->CalculateResurrectionAmount(m_pTarget);
			m_pTarget->SetNextCommand(KeyInput::Heal);
		}
	}
}

BOOL CResurrectionSkill::Execute(CUnit* unit)
{
	std::vector<CUnit*> vecTarget = unit->GetTargetUnit();


	if (unit->GetUnitTeam() == UnitTeam::West)
	{
		unit->GetStage()->SetPhase(NoticePhase::EnemyPhase);
	}
	else
		unit->GetStage()->SetPhase(NoticePhase::None);

	if (unit->GetCanMove())
	{
		unit->SetCurrentCommand(KeyInput::Idle);
		unit->HandleInput(KeyInput::Idle);
	}
	else
	{
		unit->SetCurrentCommand(KeyInput::Stop);
		unit->HandleInput(KeyInput::Stop);
	}

	for (int i = 0; i < (int)vecTarget.size(); ++i)
	{
		if (vecTarget[i] != NULL)
		{
			if (unit->CheckEnemy(vecTarget[i])) //적팀인 경우
			{
				continue;						//증감문으로 이동
			}
			vecTarget[i]->HandleInput(
				vecTarget[i]->GetCurrentCommand()
				);
			vecTarget[i]->SetNextCommand(KeyInput::Idle);
		}
	}
	unit->ClearSkillTile();

	return FALSE;
}

void CResurrectionSkill::DrawSkill(HDC hdc, Camera camera)
{
	CSkillImage::GetInstance()->DrawResurrection(hdc
		, m_ptPos
		, m_nImagePos[1]
		, camera
		);
}

BOOL CResurrectionSkill::CheckSkillEnd()
{
	if (m_nImagePos[1] > 24)
	{
		//m_nImagePos[1] = 0;
		return TRUE;
	}
	return FALSE;
}

void CResurrectionSkill::PlayEffect()
{
	m_pUnit->PlayEffect(Sound_Name::EFFECT_RESURRECTION);
}

CEdgeSkill::CEdgeSkill(int skillRange, SkillAttackType type, CUnit* unit, int mpConsumption)
	:CSkillCommand(unit)
{
	m_nSkillRange = skillRange;
	m_attackType = type;
	m_nMpConsumption = mpConsumption;
}

CEdgeSkill::~CEdgeSkill()
{

}


void CEdgeSkill::DrawSkill(HDC hdc, Camera camera )
{
	CSkillImage::GetInstance()->DrawEdge(hdc
		, m_ptPos
		, m_nImagePos[1]
		, camera
		);
}

BOOL CEdgeSkill::CheckSkillEnd()
{
	if (m_nImagePos[1] > 20)
	{
		//m_nImagePos[1] = 0;
		return TRUE;
	}
	return FALSE;
}

void CEdgeSkill::PlayEffect()
{
	m_pUnit->PlayEffect(Sound_Name::EFFECT_EDGE);
}

CThunderSkill::CThunderSkill(int skillRange, SkillAttackType type, CUnit* unit, int mpConsumption)
	:CSkillCommand(unit)
{
	m_nSkillRange = skillRange;
	m_attackType = type;
	m_nMpConsumption = mpConsumption;
}
CThunderSkill::~CThunderSkill()
{

}

void CThunderSkill::DrawSkill(HDC hdc, Camera camera )
{
	CSkillImage::GetInstance()->DrawThunder(hdc
		, m_ptPos
		, m_nImagePos[1]
		, camera
		);
}

BOOL CThunderSkill::CheckSkillEnd()
{
	if (m_nImagePos[1] > 10)
	{
		//m_nImagePos[1] = 0;
		return TRUE;
	}
	return FALSE;
}

void CThunderSkill::PlayEffect()
{
	m_pUnit->PlayEffect(Sound_Name::EFFECT_THUNDER);
}

CDarkSkill::CDarkSkill(int skillRange, SkillAttackType type, CUnit* unit, int mpConsumption)
	:CSkillCommand(unit)
{
	m_nSkillRange = skillRange;
	m_attackType = type;
	m_nMpConsumption = mpConsumption;
}
CDarkSkill::~CDarkSkill()
{

}

void CDarkSkill::DrawSkill(HDC hdc, Camera camera )
{
	CSkillImage::GetInstance()->DrawCurse(hdc
		, m_ptPos
		, m_nImagePos[1]
		, camera
		);
}

BOOL CDarkSkill::CheckSkillEnd()
{
	if (m_nImagePos[1] > 15)
	{
		//m_nImagePos[1] = 0;
		return TRUE;
	}
	return FALSE;
}

void CDarkSkill::PlayEffect()
{
	m_pUnit->PlayEffect(Sound_Name::EFFECT_CURSE);
}

CWindSKill::CWindSKill(int skillRange, SkillAttackType type, CUnit* unit, int mpConsumption)
	:CSkillCommand(unit)
{
	m_nSkillRange = skillRange;
	m_attackType = type;
	m_nMpConsumption = mpConsumption;
}
CWindSKill::~CWindSKill()
{

}

void CWindSKill::DrawSkill(HDC hdc, Camera camera)
{
	CSkillImage::GetInstance()->DrawHurricane(hdc
		, m_ptPos
		, m_nImagePos[1]
		, camera
		);
}

BOOL CWindSKill::CheckSkillEnd()
{
	if (m_nImagePos[1] > 18)
	{
		//m_nImagePos[1] = 0;
		return TRUE;
	}
	return FALSE;
}

void CWindSKill::PlayEffect()
{
	m_pUnit->PlayEffect(Sound_Name::EFFECT_HURRICANE);
}