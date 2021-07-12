#include "stdafx.h"
#include "BlackKnight.h"

CBlackKnight::CBlackKnight(INDEX idx)
	:CUnit(idx)
{
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_stop, new CAnimation(_T("resource/unit/Knight/black_knight_stand.bmp"), 1, 4, 0, 1)));
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_idle, new CAnimation(_T("resource/unit/Knight/black_knight_idle.bmp"), 3, 4, 0, 3, 0, 12)));
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_move, new CAnimation(_T("resource/unit/Knight/black_knight_move.bmp"), 4, 4, 0, 4)));
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_attack, new CAnimation(_T("resource/unit/Knight/black_knight_attack.bmp"), 3, 4, 0, 3, 0 , 8)));
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_attacked, new CAnimation(_T("resource/unit/Knight/black_knight_attacked.bmp"), 2, 4, 1, 2, 1, 35)));
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_defense, new CAnimation(_T("resource/unit/Knight/black_knight_defense.bmp"), 1, 4, 0, 1)));
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_die, new CAnimation(_T("resource/unit/Knight/black_knight_die.bmp"), 1, 4, 0, 1)));
	m_mapSprite.insert(std::pair <SpriteState, CAnimation* >
		(SpriteState::state_skill, new CAnimation(_T("resource/unit/Knight/black_knight_skill.bmp"), 9, 4, 0, 9, 8)));

	m_pCurSprite = m_mapSprite.find(SpriteState::state_idle)->second;
	m_pState = new CIdleState(this);

	m_name = UnitName::BlackKnight;
	m_szName = _T("»Ê±‚ªÁ");
	m_team = UnitTeam::North;
	m_vecSkill.push_back(SKillName::Explosion);
	m_vecSkill.push_back(SKillName::FlameBurst);
	m_szDescription = _T("∫Ò¿≤¿Ã ∏¡«ﬂ¥Ÿ.");
	//AddEffect("resource/sound/Effect/move.wav", Sound_Name::EFFECT_MOVE_GROUND);
}
CBlackKnight::~CBlackKnight()
{

}

void CBlackKnight::PlayAttackEffect()
{
	PlayEffect(Sound_Name::EFFECT_SWORD_ATTACK);
}

void CBlackKnight::PlayMoveEffect()
{
	PlayEffect(Sound_Name::EFFECT_MOVE_GROUND);
}
