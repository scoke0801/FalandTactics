#include "stdafx.h"
#include "Karin.h"

CKarin::CKarin(INDEX idx )
	: CUnit(idx)
{
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_stop, new CAnimation(_T("resource/unit/karin/karin_stand.bmp"), 1, 4, 0, 1)));
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_idle, new CAnimation(_T("resource/unit/karin/karin_idle.bmp"), 3, 4, 0, 3, 0, 12)));
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_move, new CAnimation(_T("resource/unit/karin/karin_move.bmp"), 4, 4, 0, 4)));
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_attack, new CAnimation(_T("resource/unit/karin/karin_attack.bmp"), 9, 4, 0, 9)));
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_attacked, new CAnimation(_T("resource/unit/karin/karin_attacked.bmp"), 2, 4, 1, 2, 1, 35)));
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_defense, new CAnimation(_T("resource/unit/karin/karin_defense.bmp"), 1, 4, 0, 1)));
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_die, new CAnimation(_T("resource/unit/karin/karin_die.bmp"), 1, 4, 0, 1)));
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_skill, new CAnimation(_T("resource/unit/karin/karin_skill.bmp"), 11, 4, 0, 11, 6)));

	m_pCurSprite = m_mapSprite.find(SpriteState::state_idle)->second;
	m_pState = new CIdleState(this);

	m_name = UnitName::Karin;
	m_szName = _T("ī��");
	m_team = UnitTeam::North;

	m_vecSkill.push_back(SKillName::Explosion);
	m_vecSkill.push_back(SKillName::FlameBurst);

	m_szDescription = _T("� �� ���� ���� ���� �⸥ �� �ϴ�.");
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