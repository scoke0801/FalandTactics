#include "stdafx.h"
#include "Unit.h"
#include "SkillImage.h"
#include "Command.h"

CUnit::CUnit(INDEX idx)
	//:m_sprite(w, h)
{
	m_ptCurrentPos.x = idx.x;
	m_ptCurrentPos.y = idx.y;

	m_idxCurretTileIndex = idx.GetIndex();
	m_idxCurretTileIndex.height = idx.height;

	m_nMaxHp = m_nHp = rand() % (MAX_STAT - 75) + 30;
	m_nMaxMp = m_nMp = rand() % (MAX_STAT - 75) + 30;
	m_nMoveRange = 5;
			
	m_nDefense = rand() % (MAX_STAT / 2) + 30;			
	m_nMagicDefense = rand() % (MAX_STAT / 2) + 30;

	m_nStrength = rand() % (MAX_STAT - 50) + 30;		
	m_nIntelligence = rand() % (MAX_STAT - 50) + 30;

	m_nAgility = rand() % (MAX_STAT );			

	m_way = (UnitWay)(rand() % 4);
	
	m_bCanAct = TRUE;
	m_bCanMove = TRUE;
	m_nextCommand = KeyInput::Stop;
	m_curCommand = KeyInput::Idle;
	m_nextState = NULL;
	m_nextWay = m_way;

	m_pSound = NULL;

	m_pStage = NULL;

	m_nLastDamage = 0;

	m_nDeathAngelCount[0] = 0;
	m_nDeathAngelCount[1] = 0;

	m_bTrueDie = FALSE;
	m_chAlpha = 0;

	m_bHit = FALSE;				
	m_nKillNum = 0;				
	m_nResurrectionNum = 0;	
}
CUnit::~CUnit()
{
	m_mapSprite.clear();
}

void CUnit::Move(INDEX idx)
{
	POINT pos = { idx.GetXPos(), idx.GetYPos()};
	m_ptCurrentPos = pos;
}

void CUnit::Move(POINT pos)
{
	m_ptCurrentPos = pos;
}

void CUnit::Jump()
{

}

UnitWay CUnit::CheckUnitWay(INDEX curIndex, INDEX nextIndex)
{
	if (curIndex.x % 2 == 0)	//짝수 
	{
		if (curIndex.x > nextIndex.x && curIndex.y > nextIndex.y)
			return UnitWay::LeftUp;
		if (curIndex.x > nextIndex.x && curIndex.y == nextIndex.y)
			return UnitWay::LeftDown;
		if (curIndex.x < nextIndex.x && curIndex.y > nextIndex.y)
			return UnitWay::RightUp;
		if (curIndex.x < nextIndex.x && curIndex.y == nextIndex.y)
			return UnitWay::RightDown;
	}
	else						//홀수
	{
		if (curIndex.x > nextIndex.x && curIndex.y == nextIndex.y)
			return UnitWay::LeftUp;
		if (curIndex.x > nextIndex.x && curIndex.y < nextIndex.y)
			return UnitWay::LeftDown;
		if (curIndex.x < nextIndex.x && curIndex.y == nextIndex.y)
			return UnitWay::RightUp;
		if (curIndex.x < nextIndex.x && curIndex.y < nextIndex.y)
			return UnitWay::RightDown;
	}
	return m_way;
}
UnitWay CUnit::CheckUnitWay(POINT input, Camera camera)
{
	
	if (m_ptCurrentPos.x  + TILE_WIDTH_HALF >= input.x - camera.viewPoint.x
		 && m_ptCurrentPos.y + TILE_HEIGHT_HALF >= input.y - camera.viewPoint.y)
	{
		return UnitWay::LeftUp;
	}
	if (m_ptCurrentPos.x + TILE_WIDTH_HALF >= input.x - camera.viewPoint.x
		&& m_ptCurrentPos.y + TILE_HEIGHT_HALF <= input.y - camera.viewPoint.y)
	{
		return UnitWay::LeftDown;
	}
	if (m_ptCurrentPos.x + TILE_WIDTH_HALF <= input.x - camera.viewPoint.x
		&& m_ptCurrentPos.y + TILE_HEIGHT_HALF >= input.y - camera.viewPoint.y)
	{
		return UnitWay::RightUp;
	}
	if (m_ptCurrentPos.x + TILE_WIDTH_HALF <= input.x - camera.viewPoint.x
		&& m_ptCurrentPos.y + TILE_HEIGHT_HALF <= input.y - camera.viewPoint.y)
	{
		return UnitWay::RightDown;
	}
	return m_way;
}

BOOL CUnit::CheckIsMovableTile(INDEX idx)
{
	if (m_mapMovableTile.find(idx) != m_mapMovableTile.end())
		return TRUE;
	return FALSE;
}
BOOL CUnit::CheckIsAttackableTile(INDEX idx)
{
	if (m_mapAttackableTile.find(idx) != m_mapAttackableTile.end())
		return TRUE;
	return FALSE;
}
BOOL CUnit::CheckIsSkillTile(INDEX idx)
{
	if (m_mapSkillTile.find(idx) != m_mapSkillTile.end())
		return TRUE;
	return FALSE;
}
BOOL CUnit::CheckSkillEnd()
{
	CSkillCommand* command = m_pState->GetSkillCommand();

	return command->CheckSkillEnd();
}
void CUnit::SetSkillPos(POINT pos)
{
	CSkillCommand* command = m_pState->GetSkillCommand();

	command->SetPos(pos);
}
void CUnit::SetTargetUnit(CUnit* target)
{ 
	ClearTargetUnit();
	m_vecTargetUnit.push_back(target); 
}
void CUnit::SetSkillTarget()
{
	std::map<INDEX, CTile* >::iterator iter;
	CUnit* unit;
	ClearTargetUnit();
	
	for (iter = m_mapSkillTile.begin(); iter != m_mapSkillTile.end(); ++iter)
	{
		if (iter->second->GetUnit() != NULL)
		{
			unit = iter->second->GetUnit();
			m_vecTargetUnit.push_back(unit);
			unit->SetNextCommand(unit->GetCurrentCommand());
		}
	}
}
void CUnit::ClearSkillList()
{
	m_vecSkill.clear();
}

void CUnit::EnterNextState()
{
	m_pState = m_nextState;
	m_pState->Enter(this);

	
}
BOOL CUnit::FindSkill(SKillName skill)
{
	for (int i = 0; i < (int)m_vecSkill.size(); ++i)
	{
		if (m_vecSkill[i] == skill)
			return TRUE;
	}
	return FALSE;
}
BOOL CUnit::CheckEnemy(CUnit* unit)
{
	if (unit == NULL)
		return FALSE;
	/*if (m_nHp <= 0 || unit->GetHp() <= 0)
		return FALSE;*/
	if (unit->GetUnitTeam() != m_team)
		return TRUE;
	return FALSE;
}

void CUnit::AddMp()
{
	int recoveryAmount;

	if (m_nMaxMp / 15 <= 3)
		recoveryAmount = 3;
	else
	{
		recoveryAmount = m_nMaxMp / 15;
	}
	m_nMp += recoveryAmount;
	if (m_nMp > m_nMaxMp)
		m_nMp = m_nMaxMp;
}
BOOL CUnit::FindUrgentUnit(CUnit** saveValue)
{
	std::map< INDEX, CTile* >::iterator iter;
	CUnit* unit = NULL;

	float rate = 1.0f;
	for (iter = m_mapSkillTile.begin(); iter != m_mapSkillTile.end(); ++iter)
	{
		if ((unit = iter->second->GetUnit()) != NULL)
		{
			if (unit->GetUnitTeam() != m_team ||
				unit->GetHp() <= 0)
				continue;
			if ((unit->GetMaxHp() * 0.5 >= unit->GetHp() && unit->GetHp() > 0)		//체력이 일정수치 이하이고
				&& rate < (float)unit->GetHp() / unit->GetMaxHp())	//마지막 유닛의 체력비율보다 더 낮은 유닛을 찾으면
			{
				rate = (float)unit->GetHp() / unit->GetMaxHp();
				*saveValue = unit;
			}
		}
	}

	if (saveValue == NULL)
		return FALSE;
	else
		return TRUE;
}

BOOL CUnit::FindUrgentUnit(CUnit** saveValue, CMap* map)
{ 
	std::map< INDEX, CTile* >::iterator iterSkill;
	std::map< INDEX, Node* >::iterator iterMovableTile;
	INDEX idx = { -1,-1, -1};
	CUnit* unit = NULL;
	float rate = 1.0f;

	for (iterMovableTile = m_mapMovableTile.begin(); iterMovableTile != m_mapMovableTile.end(); ++iterMovableTile)
	{
		//이동한 타일에서의 스킬범위를 확인합니다.
		map->CheckSkillTile(unit, iterMovableTile->first, unit->GetMoveRange(), SkillAttackType::Contiguous);
		for (iterSkill = m_mapSkillTile.begin(); iterSkill != m_mapSkillTile.end(); ++iterSkill)
		{
			if ((unit = iterSkill->second->GetUnit()) != NULL)
			{
				if (unit->GetUnitTeam() != m_team ||
					unit->GetHp() <= 0)
					continue;
				if ((unit->GetMaxHp() * 0.5 >= unit->GetHp() && unit->GetHp() > 0)		//체력이 일정수치 이하이고
					&& rate < (float)unit->GetHp() / unit->GetMaxHp())	//마지막 유닛의 체력비율보다 더 낮은 유닛을 찾으면
				{
					rate = (float)unit->GetHp() / unit->GetMaxHp();
					*saveValue = unit;
					idx = iterSkill->first;
					idx.height = map->GetHeight(idx);
				}
			}
		}
	}
	if (idx.CheckInRange(map->GetColumn(), map->GetRow()))
	{
		unit->SetNextTile(idx);
		return TRUE;
	}
	return FALSE;
}

BOOL CUnit::FindDeadUnit(CUnit** saveValue)
{
	std::map< INDEX, CTile* >::iterator iter;
	CUnit* unit = NULL;

	for (iter = m_mapSkillTile.begin(); iter != m_mapSkillTile.end(); ++iter)
	{
		if ((unit = iter->second->GetUnit()) != NULL)
		{
			if(unit->GetUnitTeam() != m_team)
				continue;
			if (unit->GetHp() == 0
				|| unit->GetCurrentCommand() == KeyInput::Die)
			{
				*saveValue = unit;
			}
		}
	}
	if (saveValue == NULL)
		return FALSE;
	else
		return TRUE;
}

BOOL CUnit::FindSkillTargetUnit(CUnit** saveValue)
{
	std::map< INDEX, CTile* >::iterator iter;
	CUnit* unit = NULL;
	float rate = 1.0f;
	bool check = 0;

	for (iter = m_mapSkillTile.begin(); iter != m_mapSkillTile.end(); ++iter)
	{
		if ((unit = iter->second->GetUnit()) != NULL)
		{
			if (unit->GetUnitTeam() == m_team ||
				unit->GetHp() <= 0)
				continue;
			if (rate >= (float)unit->GetHp() / unit->GetMaxHp())
			{
				rate = (float)unit->GetHp() / unit->GetMaxHp();
				check = 1;
				*saveValue = unit;
			}
		}
	}
	if (!check)
		return FALSE;
	else
		return TRUE;
}
BOOL CUnit::FindSkillTargetUnit(CUnit** saveValue, CMap* map)
{
	std::map< INDEX, CTile* >::iterator iterSkill;
	std::map< INDEX, Node* >::iterator iterMovableTile;
	INDEX idx = { -1,-1, -1 };
	INDEX moveIdx;
	CUnit* unit = NULL;
	float rate = 1.0f;

	for (iterMovableTile = m_mapMovableTile.begin(); iterMovableTile != m_mapMovableTile.end(); ++iterMovableTile)
	{
		//이동한 타일에서의 스킬범위를 확인합니다.
		map->CheckSkillTile(this, iterMovableTile->first, m_nMoveRange, SkillAttackType::Contiguous);
		for (iterSkill = m_mapSkillTile.begin(); iterSkill != m_mapSkillTile.end(); ++iterSkill)
		{
			if ((unit = iterSkill->second->GetUnit()) != NULL)
			{
				if (unit->GetUnitTeam() == m_team ||
					unit->GetHp() <= 0)
					continue;
				if (rate >= (float)unit->GetHp() / unit->GetMaxHp())
				{
					*saveValue = unit;
					rate = (float)unit->GetHp() / unit->GetMaxHp();
					idx = iterSkill->first;
					moveIdx = iterMovableTile->first;
					//moveIdx.height = map->GetHeight(idx);
					//idx.height = map->GetHeight(idx);
				}
			}
		}
	}

	if (idx.CheckInRange(map->GetColumn(), map->GetRow()))
	{
		this->SetNextTile(moveIdx);
		map->SetUnitOnTile(moveIdx, this);
		map->SetUnitOnTile(m_idxCurretTileIndex, NULL);
		return TRUE;
	}
	return FALSE;
}
BOOL CUnit::FindTargetUnit(CUnit** saveValue)
{
	std::map< INDEX, CTile* >::iterator iter;
	CUnit* unit = NULL;
	float rate = 1.0f;
	bool check = 0;
	for (iter = m_mapAttackableTile.begin(); iter != m_mapAttackableTile.end(); ++iter)
	{
		if ((unit = iter->second->GetUnit()) != NULL)
		{
			if (unit->GetUnitTeam() == m_team ||
				unit->GetHp() <= 0)
				continue;
			if (rate >= (float)unit->GetHp() / unit->GetMaxHp())
			{
				rate = (float)unit->GetHp() / unit->GetMaxHp();
				*saveValue = unit;
				check = 1;
			}
		}
	}
	if (!check)
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}
BOOL CUnit::FindTargetUnit(CUnit** saveValue, CMap* map)
{
	std::map< INDEX, CTile* >::iterator iterAttack;
	std::map< INDEX, Node* >::iterator iterMovableTile;
	INDEX idx = { -1,-1, -1 };
	INDEX moveIdx = { -1,-1,-1 };

	CUnit* unit = NULL;
	float rate = 1.0f;

	for (iterMovableTile = m_mapMovableTile.begin(); iterMovableTile != m_mapMovableTile.end(); ++iterMovableTile)
	{
		//이동한 타일에서의 공격범위를 확인합니다.
		if (map->CheckContiguousEnemy(this, iterMovableTile->first))
		{
			for (iterAttack = m_mapAttackableTile.begin(); iterAttack != m_mapAttackableTile.end(); ++iterAttack)
			{
				if ((unit = iterAttack->second->GetUnit()) != NULL)
				{
					if (unit->GetUnitTeam() == m_team ||
						unit->GetHp() <= 0)
						continue;
					if (rate >= (float)unit->GetHp() / unit->GetMaxHp())
					{
						*saveValue = unit;
						rate = (float)unit->GetHp() / unit->GetMaxHp();
						idx = iterAttack->first;
						moveIdx = iterMovableTile->first;
						moveIdx.height = map->GetHeight(moveIdx);
						idx.height = map->GetHeight(idx);
					}
				}
			}
		}
	}

	if (idx.CheckInRange(map->GetColumn(), map->GetRow()))
	{
		this->SetNextTile(moveIdx);
		map->SetUnitOnTile(moveIdx, this);
		map->SetUnitOnTile(m_idxCurretTileIndex, NULL);
		//unit->SetPrevTile(unit->GetCurrentTile());
		//unit->SetCurrentTile(idx);

		//unit->SetNextTile(idx);
		return TRUE;
	}
	return FALSE;
}

INDEX CUnit::FindNextTile(std::vector <CUnit*> vecUnits, CMap* map)
{
	INDEX nearIdx = { -1, -1, 0 };
	INDEX compIdx = { 0, 0, 0 };
	INDEX nextIndex = { -1,-1,-1 };
	std::map< INDEX, Node*>::iterator iter;
	int diff = 1000;

	if (vecUnits.size() == 0)
		return nextIndex;

	//nearIdx = vecUnits[0]->GetCurrentIndex();
	nearIdx = m_idxCurretTileIndex;
	for (int i = 0; i < (int)vecUnits.size(); ++i)
	{
		if (vecUnits[i]->GetUnitTeam() == UnitTeam::West //적팀이 아니거나
			|| vecUnits[i]->GetHp() == 0)	//체력이 0이라면	
			continue;
		else
		{
			compIdx = vecUnits[i]->GetCurrentIndex();
			if (diff > abs(nearIdx.x - compIdx.x) + abs(nearIdx.y - compIdx.y)
				+abs(nearIdx.height - compIdx.height) * 3)
			{
				diff = abs(nearIdx.x - compIdx.x) + abs(nearIdx.y - compIdx.y) + abs(nearIdx.height - compIdx.height) * 3;
				nearIdx = compIdx;					//유닛과 가장 가까운 적 유닛의 위치를 찾습니다.
			}
		}
	}
	if (nearIdx.x == -1)
		return nearIdx;
	diff = 1000;
	
	nextIndex = map->CheckPath(this, m_idxCurretTileIndex, nearIdx, m_nMoveRange);
	if (CheckIsMovableTile(nextIndex))
	{
		SetNextUnitWay(CheckUnitWay(m_idxCurretTileIndex, nextIndex));
		return nextIndex;
	}
	else
		nextIndex = m_idxCurretTileIndex;
	return nextIndex;
	//for (iter = m_mapMovableTile.begin(); iter != m_mapMovableTile.end(); ++iter)
	//{
	//	compIdx = iter->first;
	//	
	//	if (diff > abs(nearIdx.x - compIdx.x) 
	//		+ abs(nearIdx.y - compIdx.y) 
	//		+ abs(nearIdx.height - compIdx.height))
	//	{
	//		diff = abs(nearIdx.x - compIdx.x) + abs(nearIdx.y - compIdx.y) + abs(nearIdx.height - compIdx.height);
	//		nextIndex = compIdx;
	//		//return nextIndex;
	//	}
	//}
	//return nextIndex;
}
INDEX CUnit::FindNearUnit(std::vector <CUnit*>vecUnits, int division)
{
	INDEX nearIdx = { -1, -1, 0 };
	INDEX compIdx = { 0, 0, 0 };
	INDEX nextIndex = { -1,-1,-1 };
	INDEX idx;
	std::map< INDEX, Node*>::iterator iter;
	int diff = 1000;

	if (vecUnits.size() == 0)
		return nextIndex;

	//nearIdx = vecUnits[0]->GetCurrentIndex();
	idx = m_idxCurretTileIndex;
	if (division == 0)		//스킬 공격
	{
		for (int i = 0; i < (int)vecUnits.size(); ++i)
		{
			if (vecUnits[i]->GetUnitTeam() == UnitTeam::West //적팀이 아니거나
				|| vecUnits[i]->GetHp() == 0)	//체력이 0이라면	
				continue;
			else
			{
				compIdx = vecUnits[i]->GetCurrentIndex();
				if (CheckIsSkillTile(compIdx))
				{
					if (diff > abs(idx.x - compIdx.x) + abs(idx.y - compIdx.y)
						+ abs(idx.height - compIdx.height) * 3)
					{
						if (diff > abs(idx.x - compIdx.x) + abs(idx.y - compIdx.y)
							+ abs(idx.height - compIdx.height) * 3)
							nearIdx = compIdx;					//유닛과 가장 가까운 적 유닛의 위치를 찾습니다.
					}
				}
			}
		}
		if (CheckIsSkillTile(nearIdx))
		{
			SetNextUnitWay(CheckUnitWay(m_idxCurretTileIndex, nearIdx));
			return nearIdx;
		}
		else
			nearIdx.x = -10;

		return nearIdx;
	}
	else if(division == 1)					//이동
	{
		for (int i = 0; i < (int)vecUnits.size(); ++i)
		{
			if (vecUnits[i]->GetUnitTeam() == UnitTeam::West //적팀이 아니거나
				|| vecUnits[i]->GetHp() == 0)	//체력이 0이라면	
				continue;
			else
			{
				compIdx = vecUnits[i]->GetCurrentIndex();
				if (CheckIsMovableTile(compIdx))
				{
					if (diff > abs(idx.x - compIdx.x) + abs(idx.y - compIdx.y)
						+ abs(idx.height - compIdx.height) * 3)
					{
						if (diff > abs(idx.x - compIdx.x) + abs(idx.y - compIdx.y)
							+ abs(idx.height - compIdx.height) * 3)
							nearIdx = compIdx;					//유닛과 가장 가까운 적 유닛의 위치를 찾습니다.
					}
				}
			}
		}
		if (CheckIsMovableTile(nearIdx))
		{
			SetNextUnitWay(CheckUnitWay(m_idxCurretTileIndex, nearIdx));
			return nearIdx;
		}
		else
			nearIdx.x = -10;

		return nearIdx;
	}
	else if (division == 2)			//힐 스킬
	{
		for (int i = 0; i < (int)vecUnits.size(); ++i)
		{
			if (vecUnits[i]->GetUnitTeam() == UnitTeam::North //아군이 아니거나
				|| vecUnits[i]->GetHp() >= (float)(vecUnits[i]->GetMaxHp() / 5) //Hp가 1 / 5 이상인 경우 
				|| vecUnits[i]->GetHp() == 0)	//죽은 상태이거나
				continue;
			else
			{
				compIdx = vecUnits[i]->GetCurrentIndex();
				if (CheckIsSkillTile(compIdx))
				{
					if (diff > abs(idx.x - compIdx.x) + abs(idx.y - compIdx.y)
						+ abs(idx.height - compIdx.height) * 3)
					{
						if (diff > abs(idx.x - compIdx.x) + abs(idx.y - compIdx.y)
							+ abs(idx.height - compIdx.height) * 3)
							nearIdx = compIdx;					//유닛과 가장 가까운 적 유닛의 위치를 찾습니다.
					}
				}
			}
		}
		if (CheckIsSkillTile(nearIdx))
		{
			SetNextUnitWay(CheckUnitWay(m_idxCurretTileIndex, nearIdx));
			return nearIdx;
		}
		else
			nearIdx.x = -10;

		return nearIdx;
	}
	return nearIdx;
}
void CUnit::AddSkill(SKillName skill)
{
	for (int i = 0; i < (int)m_vecSkill.size(); ++i)
	{
		if (m_vecSkill[i] == skill)			//이미 있는 스킬이라면 추가하지 않습니다.
			return;
	}	
	m_vecSkill.push_back(skill);
}
void CUnit::AddTarget(CUnit* unit)
{
	m_vecTargetUnit.push_back(unit);
}
BOOL CUnit::CheckIsTarget(CUnit* unit)
{
	for (int i = 0; i < (int)m_vecTargetUnit.size(); ++i)
	{
		if (m_vecTargetUnit[i] == unit)
			return TRUE;
	}
	return FALSE;
}
void CUnit::FillSkillList(HWND *list)
{
	LPCTSTR szText;

	for (int i = 0; i < (int)m_vecSkill.size(); ++i)
	{
		switch (m_vecSkill[i])
		{
		case SKillName::Aid:
			szText =(_T("에이드"));
			break;
		case SKillName::Curse:
			szText = (_T("커스"));
			break;
		case SKillName::EvillEye:
			szText = _T("이블아이");
			break;
		case SKillName::Edge:
			szText = (_T("엣지"));
			break;
		case SKillName::Earthquake:
			szText = _T("어스퀘이크");
			break;
		case SKillName::Explosion:
			szText = (_T("익스플로전"));
			break;
		case SKillName::FlameBurst:
			szText = (_T("플레임버스트"));
			break;
		case SKillName::Hurricane:
			szText = (_T("허리케인"));
			break;
		case SKillName::WindBlast:
			szText = _T("윈드블레스트");
			break;
		case SKillName::ManaAid:
			szText = (_T("마나 에이드"));
			break;
		case SKillName::Mercy:
			szText = (_T("메르시"));
			break;
		case SKillName::Resurrection:
			szText = (_T("레저렉션"));
			break;
		case SKillName::Sacrifice:
			szText = (_T("세크리파이스"));
			break;
		case SKillName::Thunder:
			szText = (_T("썬더"));
			break;
		case SKillName::ThunderFlare:
			szText = _T("썬더프레어");
			break;
		}
		SendMessage(*list, LB_ADDSTRING, 0, (LPARAM)szText);
	}
}

void CUnit::ClearMovableTile()
{
	m_mapMovableTile.clear();
}

void CUnit::ClearAttackableTile()
{
	m_mapAttackableTile.clear();
}

void CUnit::ClearSkillTile()
{
	m_mapSkillTile.clear();
}

void CUnit::ClearTargetUnit()
{
	m_vecTargetUnit.clear();
}

void CUnit::AddAttackableTile(CTile* tile, INDEX idx)
{
	m_mapAttackableTile.insert(std::pair<INDEX, CTile*>(idx, tile));
}
KeyInput CUnit::GetNextCommand() const
{
	return m_nextCommand;
}
CUnit* CUnit::GetTargetUnit(int index) const 
{ 
	if (index < 0 || index >= (int)m_vecTargetUnit.size())
		return NULL;
	return m_vecTargetUnit[index];
}
void CUnit::DrawGrid(HDC hdc, Camera camera )
{
	HBRUSH oldBrush;
	HPEN  oldPen, hPen;
	
	oldBrush = (HBRUSH)::SelectObject(hdc, ::GetStockObject(NULL_BRUSH));
	switch (m_team)
	{
	case UnitTeam::East  :
		hPen = ::CreatePen(PS_DOT, 2, RGB(0, 0, 255));
		break;
	case UnitTeam::West  :
		hPen = ::CreatePen(PS_DOT, 2, RGB(255, 255, 255));
		break;
	case UnitTeam::South :
		hPen = ::CreatePen(PS_DOT, 2, RGB(255, 0, 0));
		break;
	case UnitTeam::North :
		hPen = ::CreatePen(PS_DOT, 2, RGB(0, 0, 0));
		break;
	}
	//hPen = ::CreatePen(PS_DOT, 2, RGB(0, 0, 255));
	oldPen = (HPEN)::SelectObject(hdc, hPen);

	::MoveToEx(hdc
		, m_ptCurrentPos.x + camera.viewPoint.x + 1
		, m_ptCurrentPos.y + TILE_HEIGHT / 2 + camera.viewPoint.y 
		, NULL
		);
	::LineTo(hdc
		, m_ptCurrentPos.x + TILE_WIDTH / 2 + camera.viewPoint.x
		, m_ptCurrentPos.y + camera.viewPoint.y + 1
		);
	::LineTo(hdc
		, m_ptCurrentPos.x + TILE_WIDTH + camera.viewPoint.x - 1
		, m_ptCurrentPos.y + TILE_HEIGHT / 2 + camera.viewPoint.y
		);
	::LineTo(hdc
		, m_ptCurrentPos.x + TILE_WIDTH / 2 + camera.viewPoint.x
		, m_ptCurrentPos.y + TILE_HEIGHT + camera.viewPoint.y - 1
		);
	::LineTo(hdc
		, m_ptCurrentPos.x + camera.viewPoint.x + 1
		, m_ptCurrentPos.y + TILE_HEIGHT / 2 + camera.viewPoint.y
		);
	/*::Rectangle(hdc
		, m_ptCurrentPos.x, m_ptCurrentPos.y
		, m_ptCurrentPos.x + 64
		, m_ptCurrentPos.y + 32
		);*/

	SelectObject(hdc, oldBrush);
	SelectObject(hdc, oldPen);
	DeleteObject(hPen);
}

void CUnit::DrawInterval(HDC hdc, Camera camera)
{
	if (m_chAlpha <= 255)
	{
		HDC LayDC;
		HBITMAP Lay;
		BLENDFUNCTION bf;

		bf.BlendOp = AC_SRC_OVER;
		bf.BlendFlags = 0;
		bf.AlphaFormat = 0;
		bf.SourceConstantAlpha = m_chAlpha;

		Lay = CreateCompatibleBitmap(hdc, CLIENT_WIDTH, CLIENT_HEIGHT);
		LayDC = CreateCompatibleDC(hdc);
		SelectObject(LayDC, Lay);

		StretchBlt(LayDC, 0, 0, CLIENT_WIDTH, CLIENT_HEIGHT
			, hdc, 0, 0, CLIENT_WIDTH, CLIENT_HEIGHT, SRCCOPY);

		m_pCurSprite->Draw(hdc
			/*, m_ptCurrentPos.x - m_pCurSprite->GetSpriteWidth() / 10 * 2
			, m_ptCurrentPos.y - m_pCurSprite->GetSpriteHeight() /4 * 3 */
			, m_idxCurretTileIndex.GetXPos() - m_pCurSprite->GetSpriteWidth() / 10 * 2
			, m_idxCurretTileIndex.GetYPos() - m_pCurSprite->GetSpriteHeight() / 4 * 3
			, camera
			);

		AlphaBlend(hdc, 0, 0, CLIENT_WIDTH, CLIENT_HEIGHT
			, LayDC, 0, 0, CLIENT_WIDTH, CLIENT_HEIGHT, bf);

		DeleteDC(LayDC);
		DeleteObject(Lay);
		m_chAlpha += 2;
	}
	else
	{
		if (CUI_UnitInfo::GetInstance()->CompareUnit(this))	//죽은 유닛의 정보가 표시되고 있다면
		{
			CUI_UnitInfo::GetInstance()->HideUI();		//UI가 보이지 않도록 합니다.
			CUI_UnitInfo::GetInstance()->SetUnit(NULL);
		}
		m_bTrueDie = TRUE;
	}
}

void CUnit::OnDraw(HDC hdc, Camera camera )
{
	DrawGrid(hdc, camera);
	
	if (m_nHp == 0 && m_team == UnitTeam::West)
	{
		if (m_pState->GetState() == SpriteState::state_attacked)
		{
			CSystemImage::GetInstance()->DrawDamage(hdc
				, m_ptCurrentPos
				, DamageTeam::EnemyDamage
				, m_nLastDamage
				, camera
				);
		}
		DrawInterval(hdc, camera);
	}
	else
	{
		m_pCurSprite->Draw(hdc
			/*, m_ptCurrentPos.x - m_pCurSprite->GetSpriteWidth() / 10 * 2
			, m_ptCurrentPos.y - m_pCurSprite->GetSpriteHeight() /4 * 3 */
			, m_idxCurretTileIndex.GetXPos() - m_pCurSprite->GetSpriteWidth() / 10 * 2
			, m_idxCurretTileIndex.GetYPos() - m_pCurSprite->GetSpriteHeight() / 4 * 3
			, camera
			);
		if (m_pState->GetState() == SpriteState::state_attacked)
		{
			CSystemImage::GetInstance()->DrawDamage(hdc
				, m_ptCurrentPos
				, DamageTeam::EnemyDamage
				, m_nLastDamage
				, camera
				);
		}
		if (m_pState->GetState() == SpriteState::state_defense)
		{
			if (m_team == UnitTeam::West)
			{
				m_nLastDamage = 1000;
				CSystemImage::GetInstance()->DrawDamage(hdc
					, m_ptCurrentPos
					, DamageTeam::EnemyDamage
					, m_nLastDamage
					, camera
					);
			}
			else if (m_team == UnitTeam::North)
			{
				m_nLastDamage = 1000;
				CSystemImage::GetInstance()->DrawDamage(hdc
					, m_ptCurrentPos
					, DamageTeam::AllyDagmage
					, m_nLastDamage
					, camera
					);
			}
		}
		if (m_pState->GetState() == SpriteState::state_die)
		{
			CSystemImage::GetInstance()->DrawDieAngel(hdc
				, m_ptCurrentPos
				, m_nDeathAngelCount[1]
				, camera
				);
			m_nDeathAngelCount[0]++;
			if (m_nDeathAngelCount[0] > 5)
			{
				m_nDeathAngelCount[1]++;
				m_nDeathAngelCount[0] = 0;
			}
			if (m_nDeathAngelCount[1] > 2)
				m_nDeathAngelCount[1] = 0;
		}
		if (GetNextCommand() == KeyInput::Heal)
		{
			CSystemImage::GetInstance()->DrawDamage(hdc
				, m_ptCurrentPos
				, DamageTeam::AllyDagmage
				, m_nLastDamage
				, camera
				);
		}
	}
}
void CUnit::DrawMovableTile(HDC hdc, Camera camera )
{
	std::map< INDEX, Node*>::iterator iter;

	for (iter = m_mapMovableTile.begin(); iter != m_mapMovableTile.end(); ++iter)
	{
		iter->second->Draw(hdc, camera);
	}
}
void CUnit::DrawMovableTile(HDC hdc, INDEX idx, Camera camera)
{
	/*if (m_mapMovableTile.find(idx) != m_mapMovableTile.end())
	{
	
	}*/
	m_mapMovableTile.find(idx)->second->Draw(hdc, camera);
}

void CUnit::DrawCurrentPos(HDC hdc, Camera camera)
{
	CSystemImage::GetInstance()->DrawTile(hdc, m_ptCurrentPos, 0, camera);
}

void CUnit::DrawAttackableTile(HDC hdc, Camera camera)
{
	std::map< INDEX, CTile*>::iterator iter;

	for (iter = m_mapAttackableTile.begin(); iter != m_mapAttackableTile.end(); ++iter)
	{
		iter->second->DrawSystemTile(hdc, 1, camera);
	}
}
void CUnit::DrawAttackableTile(HDC hdc, INDEX idx, Camera camera )
{
	m_mapAttackableTile.find(idx)->second->DrawSystemTile(hdc, 1, camera);
}

void CUnit::DrawWayNotice(HDC hdc, Camera camera)
{
	CSystemImage::GetInstance()->DrawWay(hdc, this, camera);
}
void CUnit::DrawSkill(HDC hdc, Camera camera )
{
	std::map< INDEX, CTile* >::iterator iter;

	CSkillCommand* command = m_pState->GetSkillCommand();

	for (iter = m_mapSkillTile.begin(); iter != m_mapSkillTile.end(); ++iter)
	{
		SetSkillPos(iter->second->GetTilePos());
		command->DrawSkill(hdc, camera);
	}
}
void CUnit::ReturnToPrevPos()
{
	m_idxCurretTileIndex = m_idxPreTileIndex;
	m_ptCurrentPos = POINT{ m_idxPreTileIndex.GetXPos(), m_idxPreTileIndex.GetYPos() };
}
int CUnit::CalculateDamage(CUnit* enemy)
{
	/*공격 유닛의 대미지 : 공격력 * 1.0
	피격 유닛의 방어율 : 방어력 255 을 퍼센트로 바꿔서 유닛의 대미지를 반감
						 2.55당 1 %

	공격력 * 1.0(기본 배율) * 1.5(방향)-방어율*/
	int damage;

	damage = int(m_nStrength - ((float)enemy->GetDefense() / 2.55f / 100 * (float)m_nStrength))
		+ (rand() % 20 - 10);	
	if (damage < 0)
		damage = 0;

	enemy->SetHp(enemy->GetHp() - damage);
	enemy->SetLastDamage(damage);

	if (enemy->GetHp() < 0)
		enemy->SetHp(0);

	/*if (enemy->GetUnitTeam() == UnitTeam::West)
	{
		CProfile::GetInstance()->AddAccumulationDamage(damage);
	}*/

	return damage;
}
int CUnit::CalculateSkillDamage(CUnit* enemy)
{
	/*공격 유닛의 대미지 : 지능 * 1.0
	피격 유닛의 방어율 : 마법 방어력 255 을 퍼센트로 바꿔서 유닛의 대미지를 반감
	2.55당 1 %

	지능 * 1.0(기본 배율) * 1.5(방향)-방어율*/
	int damage;

	damage = int(m_nIntelligence - ((float)enemy->GetMagicDefense() / 2.55f / 100 * (float)m_nIntelligence))
		+ (rand() % 20 - 10);
	if (damage < 0)
		damage = 0;

	enemy->SetHp(enemy->GetHp() - damage);
	enemy->SetLastDamage(damage);

	if (enemy->GetHp() < 0)
		enemy->SetHp(0);
	return damage;

}
int CUnit::CalculateHealAmount(CUnit* subject)
{
	/*
	힐 양 : 지능 * 0.7
	*/
	int amount = (float)m_nIntelligence * 7 / 10 
		+ (rand() % 10 - 5);
	if (amount <= 5)
		amount = 5;

	if (subject->GetHp() + amount >= subject->GetMaxHp())
		subject->SetHp(subject->GetMaxHp());
	else
		subject->SetHp(amount + subject->GetHp());
	subject->SetLastDamage(amount);
	return amount;
}
int CUnit::CalculateMpHealAmount(CUnit* subject)
{
	/*
	마나 힐 양 : 지능 * 0.4
	*/
	int amount = (float)m_nIntelligence * 4 / 10
		+ (rand() % 10 - 2);

	if (amount <= 5)
		amount = 5;

	if (subject->GetMp() + amount >= subject->GetMaxMp())
		subject->SetMp(subject->GetMaxMp());
	else
		subject->SetMp(amount + subject->GetMp());
	subject->SetLastDamage(amount);
	return amount;
}
int CUnit::CalculateResurrectionAmount(CUnit* subject)
{
	/*
	부활 시 체력의 양 : 대상 전체 체력의 1/3 + 지능 * 0.2
					    
	*/
	int amount = (float)m_nIntelligence * 2 / 10 + subject->GetMaxHp() / 3;

	if (amount <= 30)
		amount = 30 + ( rand() % 10 - 5 );
	if (amount >= subject->GetMaxHp())
		amount = subject->GetMaxHp();
	
	subject->SetHp(amount);
	
	subject->HandleInput(KeyInput::Stop);
	subject->SetCanAct(FALSE);
	subject->SetCanMove(FALSE);
	subject->SetLastDamage(amount);

	return amount;
}

BOOL CUnit::CheckDeffense()
{
	//MAX_STAT 255에서 50%의 방어확률 가지는 것으로 설정하고
	//방어확률을 계산합니다.
	//
	//여기서는 Agility 5당 1%방어 확률 증가, 최대 방어확률은 51%가 됨

	int rate = (float)m_nAgility / 5;
	if (rate == 0)
		return FALSE;

	if((rand() % 100 + 1) <= rate)
		return TRUE;
	return FALSE;
}
void CUnit::OnUpdate(float timeElapsed)
{
	m_fTick += timeElapsed;
	if (m_fTick < m_fFrequency)
		return;
	m_fTick -= m_fFrequency;

	m_pState->Excute(this);
	m_pCurSprite->OnUpdate(this);	
}

BOOL CUnit::CheckPlaySkillEffect()
{
	if (m_pCurSprite->GetImagePos() == 0)
		return TRUE;

	return FALSE;
}

BOOL CUnit::CheckPlayAttackEffect()
{
	if (m_pCurSprite->GetImagePos() == 0)
		return TRUE;
	return FALSE;
}

void CUnit::SkillSpriteUpdate(float timeElapsed)
{
	if (m_fTick + timeElapsed< m_fFrequency)
	{
		return;
	}
	CSkillCommand* command = m_pState->GetSkillCommand();

	command->UpdateSprite();
}
void CUnit::SetUnitWay(UnitWay way)
{
	m_way = way;
	//m_sprite.SubSpritePos();
	m_pCurSprite->EndSetState(this);

}
void CUnit::SetState(SpriteState state)
{
	m_pCurSprite->Init();
	m_pCurSprite = m_mapSprite.find(state)->second; 
	m_pCurSprite->EndSetState(this);
}

void CUnit::SetMovableTile(std::map < INDEX, Node* > map)
{
	m_mapMovableTile = map;
}
void CUnit::SetSkillTile(std::map < INDEX, CTile* > map)
{
	m_mapSkillTile = map;
}
void CUnit::HandleInput(KeyInput input)
{
	CState * stateNew = m_pState->HandleInput(this, input);
	if (stateNew != NULL)
	{
		delete m_pState;
		m_pState = stateNew;
	}
}
void CUnit::HandleInput(SKillName input)
{
	//CState * stateNew = m_pState->HandleInput(this, input);
	m_nextState = m_pState->HandleInput(this, input);
	/*if (stateNew != NULL)
	{
		delete m_pState;
		m_pState = stateNew;
	}*/
}
void CUnit::AddEffect(char*  szPath, Sound_Name varName)
{
	m_pSound->AddSound(szPath, varName);
}

void CUnit::PlayEffect(Sound_Name varName)
{
	m_pSound->PlayEffect(varName);
}

void CUnit::PlayAttackEffect()
{

}
void CUnit::PlayMoveEffect()
{

}

void CUnit::PlaySkillEffect()
{
	CSkillCommand* command = m_pState->GetSkillCommand();

	return command->PlayEffect();
}