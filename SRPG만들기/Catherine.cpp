#include "stdafx.h"
#include "Catherine.h"

CCatherine::CCatherine(INDEX idx)
	:CUnit(idx)
{
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_stop, new CAnimation(_T("resource/unit/Catherine/catherine_stand.png"), 1, 4, 0, 1)));
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_idle, new CAnimation(_T("resource/unit/Catherine/catherine_idle.png"), 3, 4, 0, 3, 0, 12)));
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_move, new CAnimation(_T("resource/unit/Catherine/catherine_move.png"), 5, 4, 0, 5)));
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_attack, new CAnimation(_T("resource/unit/Catherine/catherine_attack.png"), 7, 4, 0, 7)));
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_attacked, new CAnimation(_T("resource/unit/Catherine/catherine_attacked.png"), 2, 4, 1, 2, 1, 35)));
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_defense, new CAnimation(_T("resource/unit/Catherine/catherine_defense.png"), 1, 4, 0, 1)));
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_die, new CAnimation(_T("resource/unit/Catherine/catherine_die.png"), 1, 4, 0, 1)));
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_skill, new CAnimation(_T("resource/unit/Catherine/catherine_skill.png"), 2, 4, 0, 2)));

	m_pCurSprite = m_mapSprite.find(SpriteState::state_idle)->second;
	m_pState = new CIdleState(this);

	m_name = UnitName::Catherine;
	m_szName = _T("카트린느");
	m_team = UnitTeam::West;

	/*m_vecSkill.push_back(SKillName::Explosion);
	m_vecSkill.push_back(SKillName::FlameBurst);*/
	m_vecSkill.push_back(SKillName::Curse);
	m_vecSkill.push_back(SKillName::EvillEye);

	m_szDescription = _T("인자한 풍채에서 강함이 느껴진다.");
}
CCatherine::~CCatherine()
{

}

void CCatherine::PlayAttackEffect()
{
	PlayEffect(Sound_Name::EFFECT_HAND_ATTACK);
}

void CCatherine::PlayMoveEffect()
{
	PlayEffect(Sound_Name::EFFECT_MOVE_GROUND);
}
