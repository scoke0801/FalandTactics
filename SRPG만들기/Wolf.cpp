#include "stdafx.h"
#include "Wolf.h"

CWolf::CWolf(INDEX idx)
	:CUnit(idx)
{
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_stop, new CAnimation(_T("resource/unit/wolf/wolf_stand.bmp"), 1, 4, 0, 1)));
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_idle, new CAnimation(_T("resource/unit/wolf/wolf_idle.bmp"), 3, 4, 0, 3, 0, 12)));
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_move, new CAnimation(_T("resource/unit/wolf/wolf_move.bmp"), 6, 4, 0, 6)));
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_attack, new CAnimation(_T("resource/unit/wolf/wolf_attack.bmp"), 6, 4, 0, 6)));
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_attacked, new CAnimation(_T("resource/unit/wolf/wolf_attacked.bmp"), 2, 4, 1, 2, 1, 35)));
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_defense, new CAnimation(_T("resource/unit/wolf/wolf_defense.bmp"), 1, 4, 0, 1)));
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_die, new CAnimation(_T("resource/unit/wolf/wolf_die.bmp"), 1, 4, 0, 1)));
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_skill, new CAnimation(_T("resource/unit/wolf/wolf_die.bmp"), 1, 4, 0, 1)));

	m_pCurSprite = m_mapSprite.find(SpriteState::state_idle)->second;
	m_pState = new CIdleState(this);

	m_name = UnitName::Wolf;
	m_szName = _T("¥¡¥Î");
	m_team = UnitTeam::West;

	m_szDescription = _T("∞≥¿Œ¡ˆ ¥¡¥Î¿Œ¡ˆ");
	//m_vecSkill.push_back(SKillName::Hurricane);
}
CWolf::~CWolf()
{

}

void CWolf::PlayAttackEffect()
{
	PlayEffect(Sound_Name::EFFECT_HAND_ATTACK);
}

void CWolf::PlayMoveEffect()
{
	PlayEffect(Sound_Name::EFFECT_MOVE_GROUND);
}
