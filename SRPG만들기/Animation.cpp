#include "stdafx.h"
#include "Animation.h"
#include "Unit.h"

CAnimation::CAnimation(LPCTSTR szPath,int w, int h, int start, int end, int reuseSpot, int delay)
	:CSpriteImage(szPath, w, h)
{
	//m_currentState = SpriteState::state_idle;
	
	m_iStateArray[0] = start;
	m_iStateArray[1] = end;
	m_nDelay[0] = 0;
	m_nDelay[1] = delay;

	m_ptCurrentSpritePos.x += m_iStateArray[0];

	m_nReusePoint = reuseSpot;
}
CAnimation::~CAnimation()
{

}

void CAnimation::Init()
{
	m_ptCurrentSpritePos.x = 0;
}

void CAnimation::SetState(SpriteState state, int start, int end)
{
	m_iStateArray[0] = start;
	m_iStateArray[1] = end;
}

void CAnimation::SetReusePoint(SpriteState state, int point)
{
	m_nReusePoint = point;
}

void CAnimation::EndSetState(CUnit* unit)
{
	m_ptCurrentSpritePos.y = 0;
	switch (unit->GetUnitWay())
	{
	case UnitWay::LeftDown:		//0
		break;
	case UnitWay::RightDown:	//1
		m_ptCurrentSpritePos.y++;
		break;
	case UnitWay::LeftUp:		//2
		m_ptCurrentSpritePos.y += 2;
		break;
	case UnitWay::RightUp:		//3
		m_ptCurrentSpritePos.y += 3;
		break;
	}
}

void CAnimation::EndSetState(CUnit* unit, BOOL bStop)
{
	switch (unit->GetUnitWay())
	{
	case UnitWay::LeftDown:		//0
		break;
	case UnitWay::RightDown:	//1
		m_ptCurrentSpritePos.x++;
		break;
	case UnitWay::LeftUp:		//2
		m_ptCurrentSpritePos.x += 2;
		break;
	case UnitWay::RightUp:		//3
		m_ptCurrentSpritePos.x += 3;
		break;
	}
}
void CAnimation::Update(CUnit* unit, SpriteState state)
{
	//m_currentState = state;

	m_ptCurrentSpritePos.x = 0;
	m_ptCurrentSpritePos.y = (int)unit->GetUnitWay();

	//EndSetState(unit);

}

void CAnimation::OnUpdate(CUnit* unit)
{
	m_nDelay[0]++;
	if (m_nDelay[0] >= m_nDelay[1])
	{
		m_ptCurrentSpritePos.x++;
		m_nDelay[0] = 0;
	}

	if (m_ptCurrentSpritePos.x >= m_iStateArray[1])
	{
		//unit->SetState(unit->GetState()->Exit(unit));
		//m_currentState = unit->GetState()->GetState();
		 m_ptCurrentSpritePos.x = m_nReusePoint;
	}
	/*if (m_currentState == SpriteState::state_stop)
	{
		m_ptCurrentSpritePos.x = 0;
		m_ptCurrentSpritePos.y = 0;
		EndSetState(unit, TRUE);
	}*/

}
BOOL CAnimation::CheckAnimationEnd(CUnit* unit)
{
	if (m_ptCurrentSpritePos.x + 1 >= m_iStateArray[1])
	{
		m_ptCurrentSpritePos.x = 0;
		return TRUE;
	}
	return FALSE;
}