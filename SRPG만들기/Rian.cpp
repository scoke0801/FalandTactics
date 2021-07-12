#include "stdafx.h"
#include "Rian.h"

CRian::CRian(INDEX idx)
	:CUnit(idx)
{
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_stop, new CAnimation(_T("resource/unit/Rian/rian_stand.bmp"), 1, 4, 0, 1)));
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_idle, new CAnimation(_T("resource/unit/Rian/rian_idle.bmp"), 3, 4, 0, 3, 0, 12)));
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_move, new CAnimation(_T("resource/unit/Rian/rian_move.bmp"), 4, 4, 0, 4)));
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_attack, new CAnimation(_T("resource/unit/Rian/rian_attack.bmp"), 6, 4, 0, 3)));
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_attacked, new CAnimation(_T("resource/unit/Rian/rian_attacked.bmp"), 2, 4, 1, 2, 1, 35)));
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_defense, new CAnimation(_T("resource/unit/Rian/rian_defense.bmp"), 1, 4, 0, 1)));
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_die, new CAnimation(_T("resource/unit/Rian/rian_die.bmp"), 1, 4, 0, 1)));
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_skill, new CAnimation(_T("resource/unit/Rian/rian_skill.bmp"), 6, 4, 0, 5)));

	m_pCurSprite = m_mapSprite.find(SpriteState::state_idle)->second;
	m_pState = new CIdleState(this);

	m_name = UnitName::Rian;
	m_szName = _T("¸®¾È");
	m_team = UnitTeam::North;

	m_szDescription = _T("½Î¿ò¿¡´Â ±ò²ûÇÑ µå·¹½ºÁö!");
	
	m_vecSkill.push_back(SKillName::Curse);
	m_vecSkill.push_back(SKillName::EvillEye);
}
CRian::~CRian()
{

}

void CRian::PlayAttackEffect()
{
	PlayEffect(Sound_Name::EFFECT_SWORD_ATTACK);
}

void CRian::PlayMoveEffect()
{
	PlayEffect(Sound_Name::EFFECT_MOVE_GROUND);
}

void CRian::initializeSprite()
{
	//m_sprite.SetState(SpriteState::state_attack, 0, 6);

	//m_sprite.SetState(SpriteState::state_skill, 0, 6);
	//
	//m_sprite.SetState(SpriteState::state_stop, 0, 1);

	//m_sprite.SetState(SpriteState::state_idle, 0, 5);
	////m_sprite.SetReusePoint(SpriteState::state_idle, 1);

	//m_sprite.SetState(SpriteState::state_move, 0, 4);
}
