#include "stdafx.h"
#include "Ruru.h"

CRuru::CRuru(INDEX idx)
	:CUnit(idx)
{
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_stop, new CAnimation(_T("resource/unit/Ruru/ruru_stand.bmp"), 1, 4, 0, 1)));
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_idle, new CAnimation(_T("resource/unit/Ruru/ruru_idle.bmp"), 3, 4, 0, 3, 0, 12)));
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_move, new CAnimation(_T("resource/unit/Ruru/ruru_move.bmp"), 4, 4, 0, 4)));
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_attack, new CAnimation(_T("resource/unit/Ruru/ruru_attack.bmp"), 4, 4, 0, 4)));
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_attacked, new CAnimation(_T("resource/unit/Ruru/ruru_attacked.bmp"), 2, 4, 1, 2, 1, 35)));
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_defense, new CAnimation(_T("resource/unit/Ruru/ruru_defense.bmp"), 1, 4, 0, 1)));
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_die, new CAnimation(_T("resource/unit/Ruru/ruru_die.bmp"), 1, 4, 0, 1)));
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_skill, new CAnimation(_T("resource/unit/Ruru/ruru_skill.bmp"), 3, 4, 0, 3)));

	m_pCurSprite = m_mapSprite.find(SpriteState::state_idle)->second;
	m_pState = new CIdleState(this);

	m_name = UnitName::Ruru;
	m_szName = _T("루루");
	m_team = UnitTeam::North;
	m_szDescription = _T("솔직히 이 게임에서 가장 귀여운 것 같다.");
	m_vecSkill.push_back(SKillName::Edge);
	m_vecSkill.push_back(SKillName::Earthquake);
}
CRuru::~CRuru()
{

}

void CRuru::PlayAttackEffect()
{
	PlayEffect(Sound_Name::EFFECT_HAND_ATTACK);
}

void CRuru::PlayMoveEffect()
{
	PlayEffect(Sound_Name::EFFECT_MOVE_GROUND);
}
