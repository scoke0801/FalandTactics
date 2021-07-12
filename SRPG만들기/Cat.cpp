#include "stdafx.h"
#include "Cat.h"

CCat::CCat(INDEX idx)
	:CUnit(idx)
{
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_stop, new CAnimation(_T("resource/unit/Cat/cat_stand.bmp"), 1, 4, 0, 1)));
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_idle, new CAnimation(_T("resource/unit/Cat/cat_idle.bmp"), 3, 4, 0, 3, 0, 12)));
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_move, new CAnimation(_T("resource/unit/Cat/cat_move.bmp"), 5, 4, 0, 5)));
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_attack, new CAnimation(_T("resource/unit/Cat/cat_attack.bmp"), 11, 4, 0, 11)));
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_attacked, new CAnimation(_T("resource/unit/Cat/cat_attacked.bmp"), 2, 4, 1, 2, 1, 35)));
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_defense, new CAnimation(_T("resource/unit/Cat/cat_defense.bmp"), 1, 4, 0, 1)));
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_die, new CAnimation(_T("resource/unit/Cat/cat_die.bmp"), 1, 4, 0, 1)));
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_skill, new CAnimation(_T("resource/unit/Cat/cat_skill.bmp"), 5, 4, 0, 5,4)));

	m_pCurSprite = m_mapSprite.find(SpriteState::state_idle)->second;
	m_pState = new CIdleState(this);

	m_szDescription = _T("고양이인지 여우인지");

	m_name = UnitName::Cat;
	m_szName = _T("고양이");
	m_team = UnitTeam::West;
}
CCat::~CCat()
{

}

void CCat::PlayAttackEffect()
{
	PlayEffect(Sound_Name::EFFECT_HAND_ATTACK);
}

void CCat::PlayMoveEffect()
{
	PlayEffect(Sound_Name::EFFECT_MOVE_GROUND);
}
BOOL CCat::CheckPlayAttackEffect()
{
	if (m_pCurSprite->GetImagePos() == 5)
		return TRUE;
	return FALSE;
}