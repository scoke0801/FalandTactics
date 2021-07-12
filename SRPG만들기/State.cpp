#include "stdafx.h"
#include "state.h"
#include "Unit.h"
#include "Command.h"

#pragma region Cstate
CState::CState(CUnit* unit)
{
	m_command = NULL;
	m_skillCommand = NULL;
}

CState::~CState()
{
}

CState* CState::HandleInput(CUnit* unit, KeyInput input)
{	
	return NULL;
}
CState* CState::HandleInput(CUnit* unit, SKillName input)
{
	if (input == SKillName::Explosion)
	{
		return new CSkillState(unit, input);
	}
	else if (input == SKillName::FlameBurst)
	{
		return new CSkillState(unit, input);
	}
	else
	{
		return new CSkillState(unit, input);
	}
	return NULL;
}

void CState::Enter(CUnit* unit)
{
}
void CState::Excute(CUnit* unit)
{
}
CState* CState::Exit(CUnit* unit)
{
	return NULL;
}
#pragma endregion


#pragma region CIdleState		
CIdleState::CIdleState(CUnit* unit)
{
	Enter(unit);
}

CState* CIdleState::HandleInput(CUnit* unit, KeyInput input)
{
	if (input == KeyInput::Attack)
	{
		return new CAttackState(unit);
	}
	else if (input == KeyInput::Move)
	{
		return new CMoveState(unit);
	}
	else if (input == KeyInput::Stop)
	{
		return new CStopState(unit);
	}
	else if (input == KeyInput::Die)
	{
		return new CDieState(unit);
	}
	else if (input == KeyInput::Attacked)
	{
		return new CAttackedState(unit);
	}
	else if (input == KeyInput::Defense)
	{
		return new CDefenseState(unit);
	}
	return NULL;
}

void CIdleState::Enter(CUnit* unit)
{
	unit->SetState(SpriteState::state_idle);
}
void CIdleState::Excute(CUnit* unit)
{

}
CState* CIdleState::Exit(CUnit* unit)
{
	unit->SetState(SpriteState::state_move);

	return new CMoveState(unit);
}
#pragma endregion



#pragma region CMoveState
CMoveState::CMoveState(CUnit* unit)
{
	Enter(unit);
}

CState* CMoveState::HandleInput(CUnit* unit, KeyInput input)
{
	if (input == KeyInput::Attack)
	{
		return new CAttackState(unit);
	}
	else if (input == KeyInput::Stop)
	{
		return new CStopState(unit);
	}
	else if (input == KeyInput::Idle)
	{
		return new CIdleState(unit);
	}
	else if (input == KeyInput::Die)
	{
		return new CDieState(unit);
	}
	else if (input == KeyInput::Attacked)
	{
		return new CAttackedState(unit);
	}
	else if (input == KeyInput::Defense)
	{
		return new CDefenseState(unit);
	}
	return NULL;
}
void CMoveState::Enter(CUnit* unit)
{
	unit->SetState(SpriteState::state_move);
	m_command = new CMoveCommand(unit);

}
void CMoveState::Excute(CUnit* unit)
{
	if (m_command->Execute(unit))
	{
		//Exit(unit);
		
		if (unit->GetUnitTeam() == UnitTeam::West)
		{
			if(unit->GetNextCommand() != KeyInput::Attack)
				unit->GetStage()->SetPhase(NoticePhase::EnemyPhase);
			if (unit->GetNextCommand() == KeyInput::Skill)
			{
				unit->EnterNextState();
				unit->GetStage()->SetPhase(NoticePhase::UsingSkillPhase);
				unit->ClearMovableTile();
				return;
			}

		}
		else
			unit->GetStage()->SetPhase(NoticePhase::None);
		unit->SetCurrentCommand(unit->GetNextCommand());
		unit->HandleInput(unit->GetNextCommand());
		unit->ClearMovableTile();
	}
		
}
CState* CMoveState::Exit(CUnit* unit)
{
	unit->SetState(SpriteState::state_idle);

	return new CIdleState(unit);
}
#pragma endregion



#pragma region CAttackState
CAttackState::CAttackState(CUnit* unit)
{
	m_bPlaySonud = FALSE;
	Enter(unit);
}
CState* CAttackState::HandleInput(CUnit* unit, KeyInput input)
{
	if (input == KeyInput::Move)
	{
		return new CMoveState(unit);
	}
	else if (input == KeyInput::Stop)
	{
		return new CStopState(unit);
	}
	else if (input == KeyInput::Idle)
	{
		return new CIdleState(unit);
	}
	else if (input == KeyInput::Die)
	{
		return new CDieState(unit);
	}
	else if (input == KeyInput::Attacked)
	{
		return new CAttackedState(unit);
	}
	else if (input == KeyInput::Defense)
	{
		return new CDefenseState(unit);
	}
	return NULL;
}

void CAttackState::Enter(CUnit* unit)
{
	m_command = new CAttackCommand(unit);
	if(unit->GetTargetUnit(0) != NULL)
	unit->SetUnitWay(
		unit->CheckUnitWay(
			unit->GetCurrentIndex()
			, unit->GetTargetUnit(0)->GetCurrentIndex())
		);
	
	unit->SetState(SpriteState::state_attack);
}
void CAttackState::Excute(CUnit* unit)
{
	if (m_command->Execute(unit))
	{
		unit->ClearAttackableTile();
		unit->ClearMovableTile();

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
		if(unit->GetTargetUnit(0)->GetHp() > 0)
		{		
			unit->GetTargetUnit(0)->HandleInput(
				unit->GetTargetUnit(0)->GetCurrentCommand()
				);
		}
		
		if (unit->GetStage()->GetPhase() == NoticePhase::NoActPhase)
		{
			if (unit->GetUnitTeam() == UnitTeam::West)
			{
				unit->GetStage()->SetPhase(NoticePhase::EnemyPhase);
			}
			else
				unit->GetStage()->SetPhase(NoticePhase::None);
		}
	}
	if (unit->CheckPlayAttackEffect())
	{
		if (!m_bPlaySonud)
		{
			unit->PlayAttackEffect();
			m_bPlaySonud = TRUE;
		}
	}
	
	//unit->PlayAttackEffect();
}
CState* CAttackState::Exit(CUnit* unit)
{
	unit->SetState(SpriteState::state_stop);

	return new CStopState(unit);
}
#pragma endregion



#pragma region CSkilState
CSkillState::CSkillState(CUnit* unit, SKillName name)
{
	this->name = name;
	m_nDelay = 30;

	switch (name)
	{
	case SKillName::Explosion:
		m_skillCommand = new CBurstSkill(2, SkillAttackType::Contiguous, unit, 10);
		m_skillCommand->SetUnit(unit);
		//unit->PlaySkillEffect();
		break;
	case SKillName::FlameBurst:
		m_skillCommand = new CBurstSkill(2, SkillAttackType::Line, unit, 20);
		m_skillCommand->SetUnit(unit);
		break;
	case SKillName::Aid:
		m_skillCommand = new CAidSkill(1, SkillAttackType::Contiguous, unit, 5);
		m_skillCommand->SetUnit(unit);
		break;
	case SKillName::ManaAid:
		m_skillCommand = new CAidSkill(1, SkillAttackType::Contiguous, unit, 10, 1);
		m_skillCommand->SetUnit(unit);
		break;
	case SKillName::Mercy:
		m_skillCommand = new CAidSkill(2, SkillAttackType::Contiguous, unit, 10);
		m_skillCommand->SetUnit(unit);
		break;
	case SKillName::Resurrection:
		m_skillCommand = new CResurrectionSkill(1, SkillAttackType::Contiguous, unit, 15);
		m_skillCommand->SetUnit(unit);
		break;
	case SKillName::Sacrifice:
		m_skillCommand = new CResurrectionSkill(3, SkillAttackType::Contiguous, unit, 30);
		m_skillCommand->SetUnit(unit);
		break;
	case SKillName::Curse:
		m_skillCommand = new CDarkSkill(2, SkillAttackType::Contiguous, unit, 10);
		m_skillCommand->SetUnit(unit);
		break;
	case SKillName::EvillEye:
		m_skillCommand = new CDarkSkill(2, SkillAttackType::Line, unit, 20);
		m_skillCommand->SetUnit(unit);
		break;
	case SKillName::Hurricane:
		m_skillCommand = new CWindSKill(2, SkillAttackType::Contiguous, unit, 10);
		m_skillCommand->SetUnit(unit);
		break;
	case SKillName::WindBlast:
		m_skillCommand = new CWindSKill(2, SkillAttackType::Line, unit, 20);
		m_skillCommand->SetUnit(unit);
		break;
	case SKillName::Edge:
		m_skillCommand = new CEdgeSkill(2, SkillAttackType::Contiguous, unit, 10);
		m_skillCommand->SetUnit(unit);
		break;
	case SKillName::Earthquake:
		m_skillCommand = new CEdgeSkill(2, SkillAttackType::Line, unit, 20);
		m_skillCommand->SetUnit(unit);
		break;
	case SKillName::Thunder:
		m_skillCommand = new CThunderSkill(2, SkillAttackType::Contiguous, unit, 10);
		m_skillCommand->SetUnit(unit);
		break;
	case SKillName::ThunderFlare:
		m_skillCommand = new CThunderSkill(2, SkillAttackType::Line, unit, 20);
		m_skillCommand->SetUnit(unit);
		break;
	}
	
}
CState* CSkillState::HandleInput(CUnit* unit, KeyInput input)
{
	if (input == KeyInput::Attack)
	{
		return new CAttackState(unit);
	}
	else if (input == KeyInput::Move)
	{
		return new CMoveState(unit);
	}
	else if (input == KeyInput::Stop)
	{
		return new CStopState(unit);
	}
	else if (input == KeyInput::Idle)
	{
		return new CIdleState(unit);
	}
	else if (input == KeyInput::Die)
	{
		return new CDieState(unit);
	}
	else if (input == KeyInput::Attacked)
	{
		return new CAttackedState(unit);
	}
	else if (input == KeyInput::Defense)
	{
		return new CDefenseState(unit);
	}
	return NULL;
}
void CSkillState::Enter(CUnit* unit)
{
	std::vector<CUnit*> vecTarget = unit->GetTargetUnit();

	unit->ClearMovableTile();
	unit->SetCanAct(FALSE);
	unit->SetState(SpriteState::state_skill);
	unit->PlaySkillEffect();
	
	m_skillCommand->Enter();
}
void CSkillState::Excute(CUnit* unit)
{
	if (unit->CheckSkillEnd())
	{
		m_nDelay--;
	}
	if (m_nDelay < 0)
	{
		m_skillCommand->Execute(unit);
	}
}
CState* CSkillState::Exit(CUnit* unit)
{
	unit->SetState(SpriteState::state_stop);
	
	return new CStopState(unit);
}
#pragma endregion



#pragma region CStopState
CStopState::CStopState(CUnit* unit)
{
	Enter(unit);
}
CState* CStopState::HandleInput(CUnit* unit, KeyInput input)
{
	if (input == KeyInput::Attack)
	{
		return new CAttackState(unit);
	}
	else if (input == KeyInput::Move)
	{
		return new CMoveState(unit);
	}

	else if (input == KeyInput::Idle)
	{
		return new CIdleState(unit);
	}
	else if (input == KeyInput::Die)
	{
		return new CDieState(unit);
	}
	else if (input == KeyInput::Attacked)
	{
		return new CAttackedState(unit);
	}
	else if (input == KeyInput::Defense)
	{
		return new CDefenseState(unit);
	}
	return NULL;
}

void CStopState::Enter(CUnit* unit)
{
	unit->SetState(SpriteState::state_stop);
}
void CStopState::Excute(CUnit* unit)
{

}
CState* CStopState::Exit(CUnit* unit)
{
	unit->SetState(SpriteState::state_idle);

	return new CIdleState(unit);
}
#pragma endregion 



#pragma region CDieState
CDieState::CDieState(CUnit* unit)
{
	Enter(unit);
}
CState* CDieState::HandleInput(CUnit* unit, KeyInput input)
{
	if (input == KeyInput::Attack)
	{
		return new CAttackState(unit);
	}
	else if (input == KeyInput::Move)
	{
		return new CMoveState(unit);
	}
	else if (input == KeyInput::Stop)
	{
		return new CStopState(unit);
	}
	else if (input == KeyInput::Idle)
	{
		return new CIdleState(unit);
	}
	else if (input == KeyInput::Attacked)
	{
		return new CAttackedState(unit);
	}
	else if (input == KeyInput::Defense)
	{
		return new CDefenseState(unit);
	}
	return NULL;
}

void CDieState::Enter(CUnit* unit)
{
	unit->SetState(SpriteState::state_die);
}
void CDieState::Excute(CUnit* unit)
{
	unit->SetCanAct(FALSE);
	unit->SetCanMove(FALSE);
}
CState* CDieState::Exit(CUnit* unit)
{
	unit->SetState(SpriteState::state_stop);

	return new CStopState(unit);
}
#pragma endregion



#pragma region CDefenseState
CDefenseState::CDefenseState(CUnit* unit)
{
	Enter(unit);
}
CState* CDefenseState::HandleInput(CUnit* unit, KeyInput input)
{
	if (input == KeyInput::Attack)
	{
		return new CAttackState(unit);
	}
	else if (input == KeyInput::Move)
	{
		return new CMoveState(unit);
	}

	else if (input == KeyInput::Stop)
	{
		return new CStopState(unit);
	}
	else if (input == KeyInput::Idle)
	{
		return new CIdleState(unit);
	}
	else if (input == KeyInput::Die)
	{
		return new CDieState(unit);
	}
	else if (input == KeyInput::Attacked)
	{
		return new CAttackedState(unit);
	}
	
	return NULL;
}

void CDefenseState::Enter(CUnit* unit)
{
	unit->SetState(SpriteState::state_defense);
}
void CDefenseState::Excute(CUnit* unit)
{

}
CState* CDefenseState::Exit(CUnit* unit)
{
	unit->SetState(SpriteState::state_stop);

	return new CStopState(unit);
}
#pragma endregion



#pragma region CAttackedState
CAttackedState::CAttackedState(CUnit* unit)
{
	Enter(unit);
	//unit->GetStage()->SetPhase(NoticePhase::AttackedPhase);
}
CState* CAttackedState::HandleInput(CUnit* unit, KeyInput input)
{
	/*m_delay--;
	if (m_delay > 0)
	{
		HandleInput(unit, input);
	}*/

	if (input == KeyInput::Attack)
	{
		return new CAttackState(unit);
	}
	else if (input == KeyInput::Move)
	{
		return new CMoveState(unit);
	}
	
	else if (input == KeyInput::Stop)
	{
		return new CStopState(unit);
	}
	else if (input == KeyInput::Idle)
	{
		return new CIdleState(unit);
	}
	else if (input == KeyInput::Die)
	{
		return new CDieState(unit);
	}
	else if (input == KeyInput::Defense)
	{
		return new CDefenseState(unit);
	}
	return NULL;
 }

void CAttackedState::Enter(CUnit* unit)
{
	unit->SetState(SpriteState::state_attacked);
	m_command = new CAttackedCommand();
	m_delay = 60;
}
void CAttackedState::Excute(CUnit* unit)
{
	m_delay--;
	if (m_delay > 0)
		return;

	if (m_command->Execute(unit))
	{
		if (unit->GetHp() <= 0)
		{
			unit->SetDied(TRUE);	//유닛이 죽은 적이 있는 것으로 설정합니다.
			unit->HandleInput(KeyInput::Die);
		}
		else
			unit->HandleInput(unit->GetCurrentCommand());
	}
}
CState* CAttackedState::Exit(CUnit* unit)
{
	unit->SetState(SpriteState::state_stop);

	return new CStopState(unit);
}
#pragma endregion