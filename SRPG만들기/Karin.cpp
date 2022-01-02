#include "stdafx.h"
#include "Karin.h"

CKarin::CKarin(INDEX idx )
	: CUnit(idx)
{
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_stop, new CAnimation(_T("resource/unit/karin/karin_stand.png"), 1, 4, 0, 1)));
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_idle, new CAnimation(_T("resource/unit/karin/karin_idle.png"), 3, 4, 0, 3, 0, 12)));
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_move, new CAnimation(_T("resource/unit/karin/karin_move.png"), 4, 4, 0, 4)));
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_attack, new CAnimation(_T("resource/unit/karin/karin_attack.png"), 9, 4, 0, 9)));
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_attacked, new CAnimation(_T("resource/unit/karin/karin_attacked.png"), 2, 4, 1, 2, 1, 35)));
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_defense, new CAnimation(_T("resource/unit/karin/karin_defense.png"), 1, 4, 0, 1)));
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_die, new CAnimation(_T("resource/unit/karin/karin_die.png"), 1, 4, 0, 1)));
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_skill, new CAnimation(_T("resource/unit/karin/karin_skill.png"), 11, 4, 0, 11, 6)));

	m_pCurSprite = m_mapSprite.find(SpriteState::state_idle)->second;
	m_pState = new CIdleState(this);

	m_name = UnitName::Karin;
	m_szName = _T("카린");
	m_team = UnitTeam::North;

	m_vecSkill.push_back(SKillName::Explosion);
	m_vecSkill.push_back(SKillName::FlameBurst);

	m_szDescription = _T("어릴 때 보다 힘을 많이 기른 듯 하다.");
}
CKarin::~CKarin()
{

}

void CKarin::PlayAttackEffect()
{
	PlayEffect(Sound_Name::EFFECT_HAND_ATTACK);
}

void CKarin::PlayMoveEffect()
{
	PlayEffect(Sound_Name::EFFECT_MOVE_GROUND);
}

void CKarin::initializeSprite()
{
	/*m_sprite.SetState(SpriteState::state_attack, 0, 9);
	
	m_sprite.SetState(SpriteState::state_skill, 0, 11);
	m_sprite.SetReusePoint(SpriteState::state_skill, 6);

	m_sprite.SetState(SpriteState::state_stop, 0, 1);

	m_sprite.SetState(SpriteState::state_idle, 0, 5);
	m_sprite.SetReusePoint(SpriteState::state_idle, 1);

	m_sprite.SetState(SpriteState::state_move, 0, 4);*/
}