#include "stdafx.h"
#include "Farm.h"

CFarm::CFarm(INDEX idx)
	:CUnit(idx)
{
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_stop, new CAnimation(_T("resource/unit/Farm/farm_stand.bmp"), 1, 4, 0, 1, 0, 20)));
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_idle, new CAnimation(_T("resource/unit/Farm/farm_idle.bmp"), 3, 4, 0, 3, 0, 12)));
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_move, new CAnimation(_T("resource/unit/Farm/farm_move.bmp"), 4, 4, 0, 4)));
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_attack, new CAnimation(_T("resource/unit/Farm/farm_attack.bmp"), 7, 4, 0, 7)));
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_attacked, new CAnimation(_T("resource/unit/Farm/farm_attacked.bmp"), 2, 4, 1, 2, 1, 35)));
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_defense, new CAnimation(_T("resource/unit/Farm/farm_defense.bmp"), 1, 4, 0, 1)));
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_die, new CAnimation(_T("resource/unit/Farm/farm_die.bmp"), 1, 4, 0, 1)));
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_skill, new CAnimation(_T("resource/unit/Farm/farm_skill.bmp"), 6, 4, 0, 6, 4)));
	
	m_pCurSprite = m_mapSprite.find(SpriteState::state_idle)->second;
	m_pState = new CIdleState(this);

	m_name = UnitName::Farm;
	m_szName = _T("팜");
	m_team = UnitTeam::North;
	m_vecSkill.push_back(SKillName::Aid);
	m_vecSkill.push_back(SKillName::ManaAid);
	m_vecSkill.push_back(SKillName::Mercy);
	m_vecSkill.push_back(SKillName::Resurrection);
	m_vecSkill.push_back(SKillName::Sacrifice);

	m_szDescription = _T("직업은 치유사지만 봉을 더 잘쓴다.");
}

CFarm::~CFarm()
{

}

void CFarm::PlayAttackEffect()
{
	/*static int delay = 0;
	
	if (delay == 0)
	{
		PlayEffect(Sound_Name::EFFECT_STICK_SWING);
	}
	delay++;
	if (delay > 30)
	{
		delay = 0;
		PlayEffect(Sound_Name::EFFECT_STICK_ATTACK);
	}*/
	PlayEffect(Sound_Name::EFFECT_STICK_ATTACK);
}

void CFarm::PlayMoveEffect()
{
	PlayEffect(Sound_Name::EFFECT_MOVE_GROUND);
}

void CFarm::initializeSprite()
{
	//m_sprite.SetState(SpriteState::state_attack, 0, 7);

	//m_sprite.SetState(SpriteState::state_skill, 0, 6);
	//m_sprite.SetReusePoint(SpriteState::state_skill, 4);

	//m_sprite.SetState(SpriteState::state_stop, 0, 1);

	//m_sprite.SetState(SpriteState::state_idle, 0, 5);
	////m_sprite.SetReusePoint(SpriteState::state_idle, 1);

	//m_sprite.SetState(SpriteState::state_move, 0, 4);
}
BOOL CFarm::CheckPlayAttackEffect()
{
	if (m_pCurSprite->GetImagePos() == 3)
		return TRUE;
	return FALSE;
}