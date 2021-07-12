#include "stdafx.h"
#include "Rucia.h"

CRucia::CRucia(INDEX idx)
	:CUnit(idx)
{
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_stop, new CAnimation(_T("resource/unit/Rucia/rucia_stand.bmp"), 1, 4, 0, 1)));
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_idle, new CAnimation(_T("resource/unit/Rucia/rucia_idle.bmp"), 3, 4, 0, 3, 0, 12)));
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_move, new CAnimation(_T("resource/unit/Rucia/rucia_move.bmp"), 6, 4, 0, 6)));
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_attack, new CAnimation(_T("resource/unit/Rucia/rucia_attack.bmp"), 6, 4, 0, 6)));
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_attacked, new CAnimation(_T("resource/unit/Rucia/rucia_attacked.bmp"), 2, 4, 1, 2, 1, 35)));
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_defense, new CAnimation(_T("resource/unit/Rucia/rucia_defense.bmp"), 1, 4, 0, 1)));
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_die, new CAnimation(_T("resource/unit/Rucia/rucia_die.bmp"), 1, 4, 0, 1)));
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_skill, new CAnimation(_T("resource/unit/Rucia/rucia_skill.bmp"), 5, 4, 0, 5,4)));

	m_pCurSprite = m_mapSprite.find(SpriteState::state_idle)->second;
	m_pState = new CIdleState(this);

	m_name = UnitName::Rucia;
	m_szName = _T("루시아");
	m_team = UnitTeam::West;

	m_szDescription = _T("까마귀");

	m_vecSkill.push_back(SKillName::Hurricane);
	m_vecSkill.push_back(SKillName::WindBlast);
}
CRucia::~CRucia()
{

}

void CRucia::PlayAttackEffect()
{
	PlayEffect(Sound_Name::EFFECT_SWORD_ATTACK);
}

void CRucia::PlayMoveEffect()
{
	//PlayEffect(Sound_Name::EFFECT_MOVE_FLY);
}
