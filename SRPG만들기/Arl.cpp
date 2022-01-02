#include "stdafx.h"
#include "Arl.h"

CArl::CArl(INDEX idx)
	:CUnit(idx)
{
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_stop, new CAnimation(_T("resource/unit/Arl/arl_stand.png"), 1, 4, 0, 1)));
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_idle, new CAnimation(_T("resource/unit/Arl/arl_idle.png"), 3, 4, 0, 3, 0, 12)));
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_move, new CAnimation(_T("resource/unit/Arl/arl_move.png"), 3, 4, 0, 3)));
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_attack, new CAnimation(_T("resource/unit/Arl/arl_attack.png"), 5, 4, 0, 5)));
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_attacked, new CAnimation(_T("resource/unit/Arl/arl_attacked.png"), 2, 4, 1, 2, 1, 35)));
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_defense, new CAnimation(_T("resource/unit/Arl/arl_defense.png"), 1, 4, 0, 1)));
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_die, new CAnimation(_T("resource/unit/Arl/arl_die.png"), 1, 4, 0, 1)));
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_skill, new CAnimation(_T("resource/unit/Arl/arl_skill.png"), 4, 4, 0, 4)));

	m_pCurSprite = m_mapSprite.find(SpriteState::state_idle)->second;
	m_pState = new CIdleState(this);

	m_name = UnitName::Arl;
	m_szName = _T("��");
	m_team = UnitTeam::North;

	m_szDescription = _T("��� �˻�");
}
CArl::~CArl()
{
	
}

void CArl::PlayAttackEffect()
{
	PlayEffect(Sound_Name::EFFECT_SWORD_ATTACK);
}

void CArl::PlayMoveEffect()
{
	PlayEffect(Sound_Name::EFFECT_MOVE_GROUND);
}
