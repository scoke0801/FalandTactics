#include "stdafx.h"
#include "Fairy.h"

CFairy::CFairy(INDEX idx)
	:CUnit(idx)
{
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_stop, new CAnimation(_T("resource/unit/Fairy/fairy_stand.bmp"), 1, 4, 0, 1)));
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_idle, new CAnimation(_T("resource/unit/Fairy/fairy_idle.bmp"), 3, 4, 0, 3, 0, 12)));
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_move, new CAnimation(_T("resource/unit/Fairy/fairy_move.bmp"), 6, 4, 0, 6)));
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_attack, new CAnimation(_T("resource/unit/Fairy/fairy_attack.bmp"), 2, 4, 0, 2, 0, 35)));
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_attacked, new CAnimation(_T("resource/unit/Fairy/fairy_attacked.bmp"), 2, 4, 1, 2, 1, 35)));
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_defense, new CAnimation(_T("resource/unit/Fairy/fairy_defense.bmp"), 1, 4, 0, 1)));
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_die, new CAnimation(_T("resource/unit/Fairy/fairy_die.bmp"), 1, 4, 0, 1)));
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_skill, new CAnimation(_T("resource/unit/Fairy/fairy_skill.bmp"), 7, 4, 0, 7)));

	m_pCurSprite = m_mapSprite.find(SpriteState::state_idle)->second;
	m_pState = new CIdleState(this);

	m_name = UnitName::Fairy;
	m_szName = _T("����");
	m_team = UnitTeam::West;

	m_vecSkill.push_back(SKillName::Aid);

	m_szDescription = _T("�Ϳ��� ����Ʋ");
}
CFairy::~CFairy()
{

}

void CFairy::PlayAttackEffect()
{
	PlayEffect(Sound_Name::EFFECT_HAND_ATTACK);
}

void CFairy::PlayMoveEffect()
{
	//PlayEffect(Sound_Name::EFFECT_MOVE_FLY);
}
