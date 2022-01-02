#include "stdafx.h"
#include "crab.h"

CCrab::CCrab(INDEX idx)
	:CUnit(idx)
{
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_stop, new CAnimation(_T("resource/unit/crab/crab_stand.png"), 1, 4, 0, 1)));
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_idle, new CAnimation(_T("resource/unit/crab/crab_idle.png"), 3, 4, 0, 3, 0, 12)));
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_move, new CAnimation(_T("resource/unit/crab/crab_move.png"), 4, 4, 0, 4)));
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_attack, new CAnimation(_T("resource/unit/crab/crab_attack.png"), 4, 4, 0, 4)));
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_attacked, new CAnimation(_T("resource/unit/crab/crab_attacked.png"), 2, 4, 1, 2, 1, 35)));
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_defense, new CAnimation(_T("resource/unit/crab/crab_defense.png"), 1, 4, 0, 1)));
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_die, new CAnimation(_T("resource/unit/crab/crab_die.png"), 1, 4, 0, 1)));
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_skill, new CAnimation(_T("resource/unit/crab/crab_skill.png"), 3, 4, 0, 3, 2)));

	m_pCurSprite = m_mapSprite.find(SpriteState::state_idle)->second;
	m_pState = new CIdleState(this);
	m_szDescription = _T("ũ�� �Ƹ��ٿ� ����");
	m_name = UnitName::Crab;
	m_szName = _T("��");
	m_team = UnitTeam::West;
}
CCrab::~CCrab()
{

}

void CCrab::PlayAttackEffect()
{
	PlayEffect(Sound_Name::EFFECT_HAND_ATTACK);
}

void CCrab::PlayMoveEffect()
{
	PlayEffect(Sound_Name::EFFECT_MOVE_GROUND);
}
