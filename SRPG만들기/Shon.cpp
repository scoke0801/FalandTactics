#include "stdafx.h"
#include "Shon.h"

CShon::CShon(INDEX idx)
	:CUnit(idx)
{
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_stop, new CAnimation(_T("resource/unit/Shon/shon_stand.png"), 1, 4, 0, 1)));
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_idle, new CAnimation(_T("resource/unit/Shon/shon_idle.png"), 3, 4, 0, 3, 0, 12)));
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		//(SpriteState::state_move, new CAnimation(_T("resource/unit/Shon/shon_move.png"), 12, 4, 0, 12)));
		(SpriteState::state_move, new CAnimation(_T("resource/unit/Shon/shon_move.png"), 6, 4, 0, 6)));
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_attack, new CAnimation(_T("resource/unit/Shon/shon_attack.png"), 10, 4, 0, 10)));
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_attacked, new CAnimation(_T("resource/unit/Shon/shon_attacked.png"), 2, 4, 1, 2, 1, 35)));
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_defense, new CAnimation(_T("resource/unit/Shon/shon_defense.png"), 1, 4, 0, 1)));
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_die, new CAnimation(_T("resource/unit/Shon/shon_die.png"), 1, 4, 0, 1)));
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_skill, new CAnimation(_T("resource/unit/Shon/shon_skill.png"), 7, 4, 0, 7,6)));

	m_pCurSprite = m_mapSprite.find(SpriteState::state_idle)->second;
	m_pState = new CIdleState(this);

	m_name = UnitName::Shon;	
	m_szName = _T("¼ð");
	m_team = UnitTeam::West;
	m_szDescription = _T("Ã¤Âï ³Ê¹« ÁÁ.. ¾Æ¹«°Íµµ ¾Æ´Õ´Ï´Ù.");
	m_vecSkill.push_back(SKillName::Thunder);
	m_vecSkill.push_back(SKillName::ThunderFlare);
}
CShon::~CShon()
{

}


void CShon::PlayAttackEffect()
{
	PlayEffect(Sound_Name::EFFECT_HAND_ATTACK);
}

void CShon::PlayMoveEffect()
{
	//PlayEffect(Sound_Name::EFFECT_MOVE_FLY);
}
