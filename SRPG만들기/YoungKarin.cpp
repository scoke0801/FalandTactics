#include "stdafx.h"
#include "YoungKarin.h"

CYoungKarin::CYoungKarin(INDEX idx)
	: CUnit(idx)
{
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_stop, new CAnimation(_T("resource/unit/karin/young_karin_stand.png"), 1, 4, 0, 1)));
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_idle, new CAnimation(_T("resource/unit/karin/young_karin_idle.png"), 3, 4, 0, 3, 0, 12)));
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_move, new CAnimation(_T("resource/unit/karin/young_karin_move.png"), 4, 4, 0, 4)));
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_attack, new CAnimation(_T("resource/unit/karin/young_karin_attack.png"), 6, 4, 0, 6)));
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_attacked, new CAnimation(_T("resource/unit/karin/young_karin_attacked.png"), 2, 4, 1, 2, 1, 35)));
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_defense, new CAnimation(_T("resource/unit/karin/young_karin_defense.png"), 1, 4, 0, 1)));
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_die, new CAnimation(_T("resource/unit/karin/young_karin_die.png"), 1, 4, 0, 1)));
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_skill, new CAnimation(_T("resource/unit/karin/young_karin_skill.png"), 8, 4, 0, 8, 1)));
	
	m_pCurSprite = m_mapSprite.find(SpriteState::state_idle)->second;
	m_pState = new CIdleState(this);

	m_name = UnitName::YoungKarin;
	m_szName = _T("어린 카린");
	m_team = UnitTeam::North;
	
	m_vecSkill.push_back(SKillName::Explosion);
	m_vecSkill.push_back(SKillName::FlameBurst);

	m_szDescription = _T("꼬마마법사");
}
CYoungKarin::~CYoungKarin()
{
	m_mapSprite.clear();
}

void CYoungKarin::PlayAttackEffect()
{
	PlayEffect(Sound_Name::EFFECT_HAND_ATTACK);
}

void CYoungKarin::PlayMoveEffect()
{
	PlayEffect(Sound_Name::EFFECT_MOVE_GROUND);
}

void CYoungKarin::initializeSprite()
{
	//m_mapSprite.find(SpriteState::state_attack)->second->SetState(SpriteState::state_attack, 0, 6);
	//.SetState(SpriteState::state_attack, 0, 6);
	 
	//m_sprite.SetState(SpriteState::state_skill, 0, 8);
	//m_sprite.SetReusePoint(SpriteState::state_skill, 1);

	//m_sprite.SetState(SpriteState::state_stop, 0, 1);

	//m_sprite.SetState(SpriteState::state_idle, 0, 5);
	//m_sprite.SetReusePoint(SpriteState::state_idle, 0);

	//m_sprite.SetState(SpriteState::state_move, 0, 4);

}