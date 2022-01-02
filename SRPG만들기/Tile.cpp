#include "stdafx.h"
#include "tile.h"

#include "Karin.h"
#include "YoungKarin.h"
#include "Rian.h"
#include "Farm.h"
#include "Reon.h"
#include "Cat.h"
#include "Arl.h"
#include "Aris.h"
#include "Rucia.h"
#include "Marcia.h"
#include "Catherine.h"
#include "Ivan.h"
#include "Wolf.h"
#include "Ruru.h"
#include "Fairy.h"
#include "Shon.h"
#include "BlackKnight.h"
#include "Crab.h"
#pragma region CTile
CTile::CTile(TileType tag,int cx, int cy, int xPos, int yPos)
{
	m_tag = tag;	

	m_iCx = cx;
	m_iCy = cy;

	m_bIsObstacle = FALSE;	//기본 설정은 장애물이 아닌 것으로 합니다.
	m_bIsUsable = TRUE;		//장애물이 아니고, 유닛이 없을 것이므로 초기값을 사용가능으로 설정합니다.
	m_iHeight = 0;			//기본 설정은 높이가 없는 것(0)으로 합니다.
	
	m_pUnit = NULL;
	//m_iShadow = shadow;
	SetImagePos(xPos, yPos);
}

CTile::CTile(LPCTSTR szPath)
{

}

CTile::~CTile()
{
	delete m_upTile;
}
void CTile::DrawSystemTile(HDC hdc, int kind, Camera camera)
{
	//SystemTile = CSystemImage::GetInstance();
	//SystemTile->DrawTile(hdc, POINT{ m_iCx,m_iCy }, kind, camera);
	CSystemImage::GetInstance()->DrawTile(hdc, POINT{ m_iCx,m_iCy - m_iHeight * TILE_HEIGHT_HALF}, kind, camera);
}
INDEX CTile::GetContiguousTile(int xIndex, int yIndex, ContiguousTile contiguous_tile)
{
	INDEX idx;
	switch (contiguous_tile)
	{
	case ContiguousTile::LeftUp:
		break;
	case ContiguousTile::RightUp:
		break;
	case ContiguousTile::LeftDown:
		break; 
	case ContiguousTile::RightDown:
		break;
	}
	return idx;
}
BOOL CTile::GetIsUsable() const
{
	if (m_pUnit == NULL)
		return TRUE;
	return FALSE;
}
void CTile::SetUnit(CUnit* unit)
{
	if (unit == NULL)
	{
		m_bIsUsable = TRUE;
		m_pUnit = NULL;
	}
	else
	{ 
		m_bIsUsable = FALSE;
		m_pUnit = unit;
	}
}
INDEX CTile::GetTilePos()
{
	INDEX idx = { m_iCx, m_iCy, m_iHeight };
	idx.height = m_iHeight;
	if (m_iHeight > 0)
	{
		idx.y = m_iCy - TILE_HEIGHT_HALF * m_iHeight;
	}
	return idx;
}
INDEX CTile::GetTileIndex()
{
	INDEX idx;

	idx.x = m_iCx / TILE_WIDTH_HALF;
	idx.y = m_iCy / TILE_HEIGHT - (idx.x % 2);
	return idx;
}
void CTile::SetImagePos(int xPos, int yPos)
{
	switch (m_tag)
	{
	case TileType::PLAIN:
	case TileType::HILL:
		m_nImageCx = xPos * TILE_WIDTH;
		m_nImageCy = yPos * TILE_HEIGHT;
		break;

	}
}
BOOL CTile::CheckEnemy(CUnit* unit) const
{
	if (unit == NULL || m_pUnit == NULL)
		return FALSE;
	if (unit->GetHp() <= 0 || m_pUnit->GetHp() <= 0)
		return FALSE;
	if (unit->GetUnitTeam() != m_pUnit->GetUnitTeam())
		return TRUE;
	return FALSE;
}

void CTile::MakeUptile(int yPos)
{
	m_upTile = new CTile((TileType)((int)m_tag - 1), m_iCx, m_iCy 
		, m_nImageCx / TILE_WIDTH 
		, m_nImageCy / TILE_HEIGHT - 12 + yPos
		);
}
#pragma endregion

//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
#pragma region CMap
CMap::CMap(int mapSize)
{
	//우선은 임의의 값으로만 크기를 할당합니다.
	m_nColumn = 30;
	m_nRow = 20;

	std::vector <CTile*> vecTemp;
	for (int i = 0; i < m_nRow; ++i)
	{
		vecTemp.resize(m_nColumn);
		m_vecTiles.push_back(vecTemp);
	}

	LoadTileImage(_T("resource/tile/tile_cur.png"));
	MakeMap();
}

CMap::CMap(LPCTSTR szPath)
{
	LoadTileImage(_T("resource/tile/tile_cur.png"));
	MakeMap(szPath);
}

CMap::~CMap()
{
	m_tileImage.Destroy();	//할당한 이미지를 해제합니다.

	m_vecTiles.clear();	//완벽한 소멸이 되었는지 확실하지 않습니다.

	assert(!m_vecTiles.empty());//단언문을 통해 소멸을 확인합니다.
}

void CMap::LoadTileImage(LPCTSTR szPath)
{
	m_tileImage.Load(szPath);
}
void CMap::AddContiguousTile(std::map <INDEX, Node*> *map, INDEX idx, Node* parent)
{
	INDEX addIdx;
	//switch(m_vecTiles[idx.x][idx.y])
	if (idx.x % 2 == 0)	//인덱스의 x값이 짝수를 나타내는 경우
	{
		//LeftUp: i - 1, j - 1;
		addIdx.x = idx.x - 1;
		addIdx.y = idx.y - 1;

		if (addIdx.CheckInRange(m_nColumn, m_nRow))
		{
			addIdx.height = m_vecTiles[addIdx.x][addIdx.y]->GetHeight();
			if (CheckHeightDifference(idx, addIdx) && !m_vecTiles[addIdx.x][addIdx.y]->GetIsObstacle()
				&& m_vecTiles[addIdx.x][addIdx.y]->GetIsUsable())

			{
				map->insert(std::pair< INDEX, Node*>(addIdx, new Node(addIdx
				 	,m_vecTiles[addIdx.x][addIdx.y]->GetTilePos()
					,m_vecTiles[addIdx.x][addIdx.y]->GetHeight()
					, parent)));
				//vector->push_back(addIdx);
			}
		}

		//	RightUp: i + 1, j - 1;
		addIdx.x = idx.x + 1;
		addIdx.y = idx.y - 1;
		
		if (addIdx.CheckInRange(m_nColumn, m_nRow))
		{
			addIdx.height = m_vecTiles[addIdx.x][addIdx.y]->GetHeight();
			if (CheckHeightDifference(idx, addIdx) && !m_vecTiles[addIdx.x][addIdx.y]->GetIsObstacle()
				&& m_vecTiles[addIdx.x][addIdx.y]->GetIsUsable())
			{
				map->insert(std::pair< INDEX, Node*>(addIdx, new Node(addIdx
					, m_vecTiles[addIdx.x][addIdx.y]->GetTilePos()
					, m_vecTiles[addIdx.x][addIdx.y]->GetHeight()
					, parent)));
				//vector->push_back(addIdx);
			}
		}

		//LeftDown: i - 1, j;
		addIdx.x = idx.x - 1;
		addIdx.y = idx.y;
	
		if (addIdx.CheckInRange(m_nColumn, m_nRow))
		{
			addIdx.height = m_vecTiles[addIdx.x][addIdx.y]->GetHeight();
			if (CheckHeightDifference(idx, addIdx) && !m_vecTiles[addIdx.x][addIdx.y]->GetIsObstacle()
				&& m_vecTiles[addIdx.x][addIdx.y]->GetIsUsable())
			{
				map->insert(std::pair< INDEX, Node*>(addIdx, new Node(addIdx
					, m_vecTiles[addIdx.x][addIdx.y]->GetTilePos()
					, m_vecTiles[addIdx.x][addIdx.y]->GetHeight()
					, parent)));
				//vector->push_back(addIdx);
			}
		}

		//RightDown: i + 1, j;
		addIdx.x = idx.x + 1;
		addIdx.y = idx.y;
		
		if (addIdx.CheckInRange(m_nColumn, m_nRow))
		{
			addIdx.height = m_vecTiles[addIdx.x][addIdx.y]->GetHeight();
			if (CheckHeightDifference(idx, addIdx) && !m_vecTiles[addIdx.x][addIdx.y]->GetIsObstacle()
				&& m_vecTiles[addIdx.x][addIdx.y]->GetIsUsable())
			{
				map->insert(std::pair< INDEX, Node*>(addIdx, new Node(addIdx
					, m_vecTiles[addIdx.x][addIdx.y]->GetTilePos()
					, m_vecTiles[addIdx.x][addIdx.y]->GetHeight()
					, parent)));
				//vector->push_back(addIdx);
			}
		}
	}
	else if (idx.x % 2 == 1)	//인덱스의 x값이 홀수를 나타내는 경우
	{
	//LeftUp: i - 1, j;
		addIdx.x = idx.x - 1;
		addIdx.y = idx.y;
		
		if (addIdx.CheckInRange(m_nColumn, m_nRow))
		{
			addIdx.height = m_vecTiles[addIdx.x][addIdx.y]->GetHeight();
			if (CheckHeightDifference(idx, addIdx) && !m_vecTiles[addIdx.x][addIdx.y]->GetIsObstacle()
				&& m_vecTiles[addIdx.x][addIdx.y]->GetIsUsable())
			{
				map->insert(std::pair< INDEX, Node*>(addIdx, new Node(addIdx
					, m_vecTiles[addIdx.x][addIdx.y]->GetTilePos()
					, m_vecTiles[addIdx.x][addIdx.y]->GetHeight()
					, parent)));
			}
		}

	//LeftDown: i - 1, j + 1;
		addIdx.x = idx.x - 1;
		addIdx.y = idx.y + 1;
		
		if (addIdx.CheckInRange(m_nColumn, m_nRow))
		{
			addIdx.height = m_vecTiles[addIdx.x][addIdx.y]->GetHeight();
			if (CheckHeightDifference(idx, addIdx) && !m_vecTiles[addIdx.x][addIdx.y]->GetIsObstacle()
				&& m_vecTiles[addIdx.x][addIdx.y]->GetIsUsable())
			{
				map->insert(std::pair< INDEX, Node*>(addIdx, new Node(addIdx
					, m_vecTiles[addIdx.x][addIdx.y]->GetTilePos()
					, m_vecTiles[addIdx.x][addIdx.y]->GetHeight()
					, parent)));
				//vector->push_back(addIdx);
			}
		}

	//RightUp: i + 1, j;
		addIdx.x = idx.x + 1;
		addIdx.y = idx.y;
		
		if (addIdx.CheckInRange(m_nColumn, m_nRow))
		{
			addIdx.height = m_vecTiles[addIdx.x][addIdx.y]->GetHeight();
			if (CheckHeightDifference(idx, addIdx) && !m_vecTiles[addIdx.x][addIdx.y]->GetIsObstacle()
				&& m_vecTiles[addIdx.x][addIdx.y]->GetIsUsable())
			{
				map->insert(std::pair< INDEX, Node*>(addIdx, new Node(addIdx
					, m_vecTiles[addIdx.x][addIdx.y]->GetTilePos()
					, m_vecTiles[addIdx.x][addIdx.y]->GetHeight()
					, parent)));
				//vector->push_back(addIdx);
			}
		}

	//RightDown: i + 1, j + 1;
		addIdx.x = idx.x + 1;
		addIdx.y = idx.y + 1;
	
		if (addIdx.CheckInRange(m_nColumn, m_nRow))
		{
			addIdx.height = m_vecTiles[addIdx.x][addIdx.y]->GetHeight();
			if (CheckHeightDifference(idx, addIdx) && !m_vecTiles[addIdx.x][addIdx.y]->GetIsObstacle()
				&& m_vecTiles[addIdx.x][addIdx.y]->GetIsUsable())
			{
				map->insert(std::pair< INDEX, Node*>(addIdx, new Node(addIdx
					, m_vecTiles[addIdx.x][addIdx.y]->GetTilePos()
					, m_vecTiles[addIdx.x][addIdx.y]->GetHeight()
					, parent)));
				//vector->push_back(addIdx);
			}
		}
	}
}

void CMap::CheckPath(std::map <INDEX, Node*> *map, INDEX idx, Node* parent)
{
	INDEX addIdx;

	if (idx.x % 2 == 0)	//인덱스의 x값이 짝수를 나타내는 경우
	{
		addIdx.x = idx.x - 1;
		addIdx.y = idx.y - 1;

		if (addIdx.CheckInRange(m_nColumn, m_nRow))
		{
			addIdx.height = m_vecTiles[addIdx.x][addIdx.y]->GetHeight();
			if (CheckHeightDifference(idx, addIdx) 
				&& !m_vecTiles[addIdx.x][addIdx.y]->GetIsObstacle())
			{
				map->insert(std::pair< INDEX, Node*>(addIdx, new Node(addIdx
					, m_vecTiles[addIdx.x][addIdx.y]->GetTilePos()
					, m_vecTiles[addIdx.x][addIdx.y]->GetHeight()
					, parent)));
			}
		}
		//	RightUp: i + 1, j - 1;
		addIdx.x = idx.x + 1;
		addIdx.y = idx.y - 1;

		if (addIdx.CheckInRange(m_nColumn, m_nRow))
		{
			addIdx.height = m_vecTiles[addIdx.x][addIdx.y]->GetHeight();
			if (CheckHeightDifference(idx, addIdx) && !m_vecTiles[addIdx.x][addIdx.y]->GetIsObstacle())
			{
				map->insert(std::pair< INDEX, Node*>(addIdx, new Node(addIdx
					, m_vecTiles[addIdx.x][addIdx.y]->GetTilePos()
					, m_vecTiles[addIdx.x][addIdx.y]->GetHeight()
					, parent)));
				//vector->push_back(addIdx);
			}
		}

		//LeftDown: i - 1, j;
		addIdx.x = idx.x - 1;
		addIdx.y = idx.y;

		if (addIdx.CheckInRange(m_nColumn, m_nRow))
		{
			addIdx.height = m_vecTiles[addIdx.x][addIdx.y]->GetHeight();
			if (CheckHeightDifference(idx, addIdx) && !m_vecTiles[addIdx.x][addIdx.y]->GetIsObstacle())
			{
				map->insert(std::pair< INDEX, Node*>(addIdx, new Node(addIdx
					, m_vecTiles[addIdx.x][addIdx.y]->GetTilePos()
					, m_vecTiles[addIdx.x][addIdx.y]->GetHeight()
					, parent)));
				//vector->push_back(addIdx);
			}
		}

		//RightDown: i + 1, j;
		addIdx.x = idx.x + 1;
		addIdx.y = idx.y;

		if (addIdx.CheckInRange(m_nColumn, m_nRow))
		{
			addIdx.height = m_vecTiles[addIdx.x][addIdx.y]->GetHeight();
			if (CheckHeightDifference(idx, addIdx) && !m_vecTiles[addIdx.x][addIdx.y]->GetIsObstacle())
			{
				map->insert(std::pair< INDEX, Node*>(addIdx, new Node(addIdx
					, m_vecTiles[addIdx.x][addIdx.y]->GetTilePos()
					, m_vecTiles[addIdx.x][addIdx.y]->GetHeight()
					, parent)));
				//vector->push_back(addIdx);
			}
		}
	}
	else if (idx.x % 2 == 1)	//인덱스의 x값이 홀수를 나타내는 경우
	{
		//LeftUp: i - 1, j;
		addIdx.x = idx.x - 1;
		addIdx.y = idx.y;

		if (addIdx.CheckInRange(m_nColumn, m_nRow))
		{
			addIdx.height = m_vecTiles[addIdx.x][addIdx.y]->GetHeight();
			if (CheckHeightDifference(idx, addIdx) && !m_vecTiles[addIdx.x][addIdx.y]->GetIsObstacle())
			{
				map->insert(std::pair< INDEX, Node*>(addIdx, new Node(addIdx
					, m_vecTiles[addIdx.x][addIdx.y]->GetTilePos()
					, m_vecTiles[addIdx.x][addIdx.y]->GetHeight()
					, parent)));
			}
		}

		//LeftDown: i - 1, j + 1;
		addIdx.x = idx.x - 1;
		addIdx.y = idx.y + 1;

		if (addIdx.CheckInRange(m_nColumn, m_nRow))
		{
			addIdx.height = m_vecTiles[addIdx.x][addIdx.y]->GetHeight();
			if (CheckHeightDifference(idx, addIdx) && !m_vecTiles[addIdx.x][addIdx.y]->GetIsObstacle())
			{
				map->insert(std::pair< INDEX, Node*>(addIdx, new Node(addIdx
					, m_vecTiles[addIdx.x][addIdx.y]->GetTilePos()
					, m_vecTiles[addIdx.x][addIdx.y]->GetHeight()
					, parent)));
				//vector->push_back(addIdx);
			}
		}

		//RightUp: i + 1, j;
		addIdx.x = idx.x + 1;
		addIdx.y = idx.y;

		if (addIdx.CheckInRange(m_nColumn, m_nRow))
		{
			addIdx.height = m_vecTiles[addIdx.x][addIdx.y]->GetHeight();
			if (CheckHeightDifference(idx, addIdx) && !m_vecTiles[addIdx.x][addIdx.y]->GetIsObstacle())
			{
				map->insert(std::pair< INDEX, Node*>(addIdx, new Node(addIdx
					, m_vecTiles[addIdx.x][addIdx.y]->GetTilePos()
					, m_vecTiles[addIdx.x][addIdx.y]->GetHeight()
					, parent)));
				//vector->push_back(addIdx);
			}
		}

		//RightDown: i + 1, j + 1;
		addIdx.x = idx.x + 1;
		addIdx.y = idx.y + 1;

		if (addIdx.CheckInRange(m_nColumn, m_nRow))
		{
			addIdx.height = m_vecTiles[addIdx.x][addIdx.y]->GetHeight();
			if (CheckHeightDifference(idx, addIdx) && !m_vecTiles[addIdx.x][addIdx.y]->GetIsObstacle())
			{
				map->insert(std::pair< INDEX, Node*>(addIdx, new Node(addIdx
					, m_vecTiles[addIdx.x][addIdx.y]->GetTilePos()
					, m_vecTiles[addIdx.x][addIdx.y]->GetHeight()
					, parent)));
				//vector->push_back(addIdx);
			}
		}
	}
}

BOOL CMap::CheckContiguousEnemy(INDEX idx)
{
	INDEX addIdx;
	CUnit* unit = m_vecTiles[idx.x][idx.y]->GetUnit();
	int count = 0;

	if (unit == NULL)
		return FALSE;
	if (unit->GetCanAttack() == FALSE)
		return FALSE;

	unit->ClearAttackableTile();
	if (idx.x % 2 == 0)	//인덱스의 x값이 짝수를 나타내는 경우
	{
		//LeftUp: i - 1, j - 1;
		addIdx.x = idx.x - 1;
		addIdx.y = idx.y - 1;
		if (addIdx.CheckInRange(m_nColumn, m_nRow))
		{
			addIdx.height = m_vecTiles[addIdx.x][addIdx.y]->GetHeight();
			if (CheckHeightDifference(idx, addIdx) && !CheckIsObstacle(idx))
			{
				if (m_vecTiles[addIdx.x][addIdx.y]->CheckEnemy(unit))
				{
					unit->AddAttackableTile(m_vecTiles[addIdx.x][addIdx.y], addIdx);
					count++;
				}
			}
		}

		//	RightUp: i + 1, j - 1;
		addIdx.x = idx.x + 1;
		addIdx.y = idx.y - 1;
		if (addIdx.CheckInRange(m_nColumn, m_nRow))
		{
			addIdx.height = m_vecTiles[addIdx.x][addIdx.y]->GetHeight();
			if (CheckHeightDifference(idx, addIdx) && !CheckIsObstacle(idx))
			{
				if (m_vecTiles[addIdx.x][addIdx.y]->CheckEnemy(unit))
				{
					unit->AddAttackableTile(m_vecTiles[addIdx.x][addIdx.y], addIdx);
					count++;
				}
			}
		}

		//LeftDown: i - 1, j;
		addIdx.x = idx.x - 1;
		addIdx.y = idx.y;
		if (addIdx.CheckInRange(m_nColumn, m_nRow))
		{
			addIdx.height = m_vecTiles[addIdx.x][addIdx.y]->GetHeight();
			if (CheckHeightDifference(idx, addIdx) && !CheckIsObstacle(idx))
			{
				if (m_vecTiles[addIdx.x][addIdx.y]->CheckEnemy(unit))
				{
					unit->AddAttackableTile(m_vecTiles[addIdx.x][addIdx.y], addIdx);
					count++;
				}
			}
		}

		//RightDown: i + 1, j;
		addIdx.x = idx.x + 1;
		addIdx.y = idx.y;
		if (addIdx.CheckInRange(m_nColumn, m_nRow))
		{
			addIdx.height = m_vecTiles[addIdx.x][addIdx.y]->GetHeight();
			if (CheckHeightDifference(idx, addIdx) && !CheckIsObstacle(idx))
			{
				if (m_vecTiles[addIdx.x][addIdx.y]->CheckEnemy(unit))
				{
					unit->AddAttackableTile(m_vecTiles[addIdx.x][addIdx.y], addIdx);
					count++;
				}
			}
		}
	}
	else if (idx.x % 2 == 1)	//인덱스의 x값이 홀수를 나타내는 경우
	{
		//LeftUp: i - 1, j;
		addIdx.x = idx.x - 1;
		addIdx.y = idx.y;
		if (addIdx.CheckInRange(m_nColumn, m_nRow))
		{
			addIdx.height = m_vecTiles[addIdx.x][addIdx.y]->GetHeight();
			if (CheckHeightDifference(idx, addIdx) && !CheckIsObstacle(idx))
			{
				if (m_vecTiles[addIdx.x][addIdx.y]->CheckEnemy(unit))
				{
					unit->AddAttackableTile(m_vecTiles[addIdx.x][addIdx.y], addIdx);
					count++;
				}
			}
		}

		//LeftDown: i - 1, j + 1;
		addIdx.x = idx.x - 1;
		addIdx.y = idx.y + 1;
		if (addIdx.CheckInRange(m_nColumn, m_nRow))
		{
			addIdx.height = m_vecTiles[addIdx.x][addIdx.y]->GetHeight();
			if (CheckHeightDifference(idx, addIdx) && !CheckIsObstacle(idx))
			{
				if (m_vecTiles[addIdx.x][addIdx.y]->CheckEnemy(unit))
				{
					unit->AddAttackableTile(m_vecTiles[addIdx.x][addIdx.y], addIdx);
					count++;
				}
			}
		}

		//RightUp: i + 1, j;
		addIdx.x = idx.x + 1;
		addIdx.y = idx.y;
		if (addIdx.CheckInRange(m_nColumn, m_nRow))
		{
			addIdx.height = m_vecTiles[addIdx.x][addIdx.y]->GetHeight();
			if (CheckHeightDifference(idx, addIdx) && !CheckIsObstacle(idx))
			{
				if (m_vecTiles[addIdx.x][addIdx.y]->CheckEnemy(unit))
				{
					unit->AddAttackableTile(m_vecTiles[addIdx.x][addIdx.y], addIdx);
					count++;
				}
			}
		}

		//RightDown: i + 1, j + 1;
		addIdx.x = idx.x + 1;
		addIdx.y = idx.y + 1;
		if (addIdx.CheckInRange(m_nColumn, m_nRow))
		{
			addIdx.height = m_vecTiles[addIdx.x][addIdx.y]->GetHeight();
			if (CheckHeightDifference(idx, addIdx) && !CheckIsObstacle(idx))
			{
				if (m_vecTiles[addIdx.x][addIdx.y]->CheckEnemy(unit))
				{
					unit->AddAttackableTile(m_vecTiles[addIdx.x][addIdx.y], addIdx);
					count++;
				}
			}
		}
	}
	if(count != 0)
		return TRUE;
	return FALSE;
}
BOOL CMap::CheckContiguousEnemy(CUnit* unit, INDEX idx)
{
	INDEX addIdx;
	int count = 0;

	if (unit == NULL)
		return FALSE;
	if (unit->GetCanAttack() == FALSE)
		return FALSE;

	unit->ClearAttackableTile();
	if (idx.x % 2 == 0)	//인덱스의 x값이 짝수를 나타내는 경우
	{
		//LeftUp: i - 1, j - 1;
		addIdx.x = idx.x - 1;
		addIdx.y = idx.y - 1;
		if (addIdx.CheckInRange(m_nColumn, m_nRow))
		{
			addIdx.height = m_vecTiles[addIdx.x][addIdx.y]->GetHeight();
			if (CheckHeightDifference(idx, addIdx) && !CheckIsObstacle(idx))
			{
				if (m_vecTiles[addIdx.x][addIdx.y]->CheckEnemy(unit))
				{
					unit->AddAttackableTile(m_vecTiles[addIdx.x][addIdx.y], addIdx);
					count++;
				}
			}
		}

		//	RightUp: i + 1, j - 1;
		addIdx.x = idx.x + 1;
		addIdx.y = idx.y - 1;
		if (addIdx.CheckInRange(m_nColumn, m_nRow))
		{
			addIdx.height = m_vecTiles[addIdx.x][addIdx.y]->GetHeight();
			if (CheckHeightDifference(idx, addIdx) && !CheckIsObstacle(idx))
			{
				if (m_vecTiles[addIdx.x][addIdx.y]->CheckEnemy(unit))
				{
					unit->AddAttackableTile(m_vecTiles[addIdx.x][addIdx.y], addIdx);
					count++;
				}
			}
		}

		//LeftDown: i - 1, j;
		addIdx.x = idx.x - 1;
		addIdx.y = idx.y;
		if (addIdx.CheckInRange(m_nColumn, m_nRow))
		{
			addIdx.height = m_vecTiles[addIdx.x][addIdx.y]->GetHeight();
			if (CheckHeightDifference(idx, addIdx) && !CheckIsObstacle(idx))
			{
				if (m_vecTiles[addIdx.x][addIdx.y]->CheckEnemy(unit))
				{
					unit->AddAttackableTile(m_vecTiles[addIdx.x][addIdx.y], addIdx);
					count++;
				}
			}
		}

		//RightDown: i + 1, j;
		addIdx.x = idx.x + 1;
		addIdx.y = idx.y;
		if (addIdx.CheckInRange(m_nColumn, m_nRow))
		{
			addIdx.height = m_vecTiles[addIdx.x][addIdx.y]->GetHeight();
			if (CheckHeightDifference(idx, addIdx) && !CheckIsObstacle(idx))
			{
				if (m_vecTiles[addIdx.x][addIdx.y]->CheckEnemy(unit))
				{
					unit->AddAttackableTile(m_vecTiles[addIdx.x][addIdx.y], addIdx);
					count++;
				}
			}
		}
	}
	else if (idx.x % 2 == 1)	//인덱스의 x값이 홀수를 나타내는 경우
	{
		//LeftUp: i - 1, j;
		addIdx.x = idx.x - 1;
		addIdx.y = idx.y;
		if (addIdx.CheckInRange(m_nColumn, m_nRow))
		{
			addIdx.height = m_vecTiles[addIdx.x][addIdx.y]->GetHeight();
			if (CheckHeightDifference(idx, addIdx) && !CheckIsObstacle(idx))
			{
				if (m_vecTiles[addIdx.x][addIdx.y]->CheckEnemy(unit))
				{
					unit->AddAttackableTile(m_vecTiles[addIdx.x][addIdx.y], addIdx);
					count++;
				}
			}
		}

		//LeftDown: i - 1, j + 1;
		addIdx.x = idx.x - 1;
		addIdx.y = idx.y + 1;
		if (addIdx.CheckInRange(m_nColumn, m_nRow))
		{
			addIdx.height = m_vecTiles[addIdx.x][addIdx.y]->GetHeight();
			if (CheckHeightDifference(idx, addIdx) && !CheckIsObstacle(idx))
			{
				if (m_vecTiles[addIdx.x][addIdx.y]->CheckEnemy(unit))
				{
					unit->AddAttackableTile(m_vecTiles[addIdx.x][addIdx.y], addIdx);
					count++;
				}
			}
		}

		//RightUp: i + 1, j;
		addIdx.x = idx.x + 1;
		addIdx.y = idx.y;
		if (addIdx.CheckInRange(m_nColumn, m_nRow))
		{
			addIdx.height = m_vecTiles[addIdx.x][addIdx.y]->GetHeight();
			if (CheckHeightDifference(idx, addIdx) && !CheckIsObstacle(idx))
			{
				if (m_vecTiles[addIdx.x][addIdx.y]->CheckEnemy(unit))
				{
					unit->AddAttackableTile(m_vecTiles[addIdx.x][addIdx.y], addIdx);
					count++;
				}
			}
		}

		//RightDown: i + 1, j + 1;
		addIdx.x = idx.x + 1;
		addIdx.y = idx.y + 1;
		if (addIdx.CheckInRange(m_nColumn, m_nRow))
		{
			addIdx.height = m_vecTiles[addIdx.x][addIdx.y]->GetHeight();
			if (CheckHeightDifference(idx, addIdx) && !CheckIsObstacle(idx))
			{
				if (m_vecTiles[addIdx.x][addIdx.y]->CheckEnemy(unit))
				{
					unit->AddAttackableTile(m_vecTiles[addIdx.x][addIdx.y], addIdx);
					count++;
				}
			}
		}
	}
	if (count != 0)
		return TRUE;
	return FALSE;
}
INDEX CMap::CheckPath(CUnit* unit,INDEX start, INDEX end, int moveRange)
{
	std::map < INDEX, Node* > mapPath;

	std::map< INDEX, Node* > openMap;	//탐색목록
	std::map < INDEX, Node*> closeMap;  //추가된 목록(확인ok)
	std::map < INDEX, Node* > searchedValue;
	std::map< INDEX, Node*>::iterator mapIter;
	std::vector < INDEX >::iterator vecIter;
	std::vector < Node* > vecPath;
	Node* node;
	INDEX idx, last;
	int count = 0;
	openMap.insert(std::pair< INDEX, Node*>(start, new Node(start, m_vecTiles[start.x][start.y]->GetTilePos())));
	
	while(closeMap.find(end) == closeMap.end() && count < 100)
	{
		if (openMap.size() == 0)
			break;
		for (mapIter = openMap.begin(); mapIter != openMap.end(); ++mapIter)
		{
			if (closeMap.find(mapIter->first) != closeMap.end())	//이미 탐색한 목록에 있다면
				continue;											//건너뜁니다.

			idx = mapIter->first;
			CheckPath(&searchedValue, idx, mapIter->second); //탐색목록에 있는 값을 토대로 주변 타일들을 검색 및 추가합니다.
			closeMap.insert(std::pair< INDEX, Node*>(mapIter->first, mapIter->second));
			//한 번 탐색한 타일은 재탐색하지 않도록 값을 저장해둡니다.
		}
		openMap.clear();	//검색된 값을 토대로 탐색목록을 재구성하기 전, 기존 값을 삭제합니다.

		openMap = searchedValue;
		searchedValue.clear();	//탐색이 끝난 후에는 탐색값을 삭제합니다.
		count++;
		last = idx;
	}
	
	node = closeMap.find(end)->second;
	
	while (node != NULL)
	{
		vecPath.push_back(node);
		node = node->link;
	}
	int size = vecPath.size() - 1;
	if (size > moveRange)
	{
		for (int i = 0; i < moveRange; ++i)
		{
			idx = vecPath[size - moveRange + i]->GetIndex();
			if (unit->CheckIsMovableTile(idx))
			{
				return idx;
			}
		}
		idx = vecPath[size - moveRange]->GetIndex();
	}
	return idx;
}
void CMap::AddContiguousTile(CUnit* unit, std::map <INDEX, CTile*> *map, INDEX idx)
{
	INDEX addIdx;
	int count = 0;
	
	//if (unit->CheckEnemy(m_vecTiles[addIdx.x][addIdx.y]->GetUnit())
	//	|| m_vecTiles[addIdx.x][addIdx.y]->GetUnit() == NULL)
	if (idx.x % 2 == 0)	//인덱스의 x값이 짝수를 나타내는 경우
	{
		//LeftUp: i - 1, j - 1;
		addIdx.x = idx.x - 1;
		addIdx.y = idx.y - 1;
		if (addIdx.CheckInRange(m_nColumn, m_nRow)
			&& !CheckIsObstacle(addIdx))
		{
			{
				map->insert(std::pair< INDEX, CTile*>(addIdx
					, m_vecTiles[addIdx.x][addIdx.y])
					);
			}
		}

		//	RightUp: i + 1, j - 1;
		addIdx.x = idx.x + 1;
		addIdx.y = idx.y - 1;
		if (addIdx.CheckInRange(m_nColumn, m_nRow)
			&& !CheckIsObstacle(addIdx))
		{
			{
				map->insert(std::pair< INDEX, CTile*>(addIdx
					, m_vecTiles[addIdx.x][addIdx.y])
					);
			}
		}

		//LeftDown: i - 1, j;
		addIdx.x = idx.x - 1;
		addIdx.y = idx.y;
		if (addIdx.CheckInRange(m_nColumn, m_nRow)
			&& !CheckIsObstacle(addIdx))
		{
			{
				map->insert(std::pair< INDEX, CTile*>(addIdx
					, m_vecTiles[addIdx.x][addIdx.y])
					);
			}
		}

		//RightDown: i + 1, j;
		addIdx.x = idx.x + 1;
		addIdx.y = idx.y;
		if (addIdx.CheckInRange(m_nColumn, m_nRow)
			&& !CheckIsObstacle(addIdx))
		{
			{
				map->insert(std::pair< INDEX, CTile*>(addIdx
					, m_vecTiles[addIdx.x][addIdx.y])
					);
			}
		}
	}
	else if (idx.x % 2 == 1)	//인덱스의 x값이 홀수를 나타내는 경우
	{
		//LeftUp: i - 1, j;
		addIdx.x = idx.x - 1;
		addIdx.y = idx.y;
		if (addIdx.CheckInRange(m_nColumn, m_nRow)
			&& !CheckIsObstacle(addIdx))
		{
			{
				map->insert(std::pair< INDEX, CTile*>(addIdx
					, m_vecTiles[addIdx.x][addIdx.y])
					);
			}
		}

		//LeftDown: i - 1, j + 1;
		addIdx.x = idx.x - 1;
		addIdx.y = idx.y + 1;
		if (addIdx.CheckInRange(m_nColumn, m_nRow)
			&& !CheckIsObstacle(addIdx))
		{
			{
				map->insert(std::pair< INDEX, CTile*>(addIdx
					, m_vecTiles[addIdx.x][addIdx.y])
					);
			}
		}

		//RightUp: i + 1, j;
		addIdx.x = idx.x + 1;
		addIdx.y = idx.y;
		if (addIdx.CheckInRange(m_nColumn, m_nRow)
			&& !CheckIsObstacle(addIdx))
		{
			{
				map->insert(std::pair< INDEX, CTile*>(addIdx
					, m_vecTiles[addIdx.x][addIdx.y])
					);
			}
		}

		//RightDown: i + 1, j + 1;
		addIdx.x = idx.x + 1;
		addIdx.y = idx.y + 1;
		if (addIdx.CheckInRange(m_nColumn, m_nRow)
			&& !CheckIsObstacle(addIdx))
		{
			{
				map->insert(std::pair< INDEX, CTile*>(addIdx
					, m_vecTiles[addIdx.x][addIdx.y])
					);
			}
		}
	}
}
void CMap::AddLineTile(CUnit* unit, std::map <INDEX, CTile* > *map, INDEX idx, UnitWay way, int range)
{
	INDEX addIdx = idx;

	for (int i = 0; i < range; ++i)
	{
		if (way == UnitWay::LeftUp)
		{
			if (addIdx.x % 2 == 0)
			{
				addIdx.x = addIdx.x - 1;
				addIdx.y = addIdx.y - 1;
				if (addIdx.CheckInRange(m_nColumn, m_nRow)
					&& !CheckIsObstacle(addIdx))
				{
					map->insert(std::pair< INDEX, CTile*>(addIdx
						, m_vecTiles[addIdx.x][addIdx.y])
						);
				}
			}
			else
			{
				addIdx.x = addIdx.x - 1;
				addIdx.y = addIdx.y;
				if (addIdx.CheckInRange(m_nColumn, m_nRow)
					&& !CheckIsObstacle(addIdx))
				{
					map->insert(std::pair< INDEX, CTile*>(addIdx
						, m_vecTiles[addIdx.x][addIdx.y])
						);
				}
			}
		}
		else if (way == UnitWay::LeftDown)
		{
			if (addIdx.x % 2 == 0)
			{
				addIdx.x = addIdx.x - 1;
				addIdx.y = addIdx.y;

				if (addIdx.CheckInRange(m_nColumn, m_nRow)
					&& !CheckIsObstacle(addIdx))
				{
					map->insert(std::pair< INDEX, CTile*>(addIdx
						, m_vecTiles[addIdx.x][addIdx.y])
						);
				}
			}
			else
			{
				addIdx.x = addIdx.x - 1;
				addIdx.y = addIdx.y + 1;
				if (addIdx.CheckInRange(m_nColumn, m_nRow)
					&& !CheckIsObstacle(addIdx))
				{
					map->insert(std::pair< INDEX, CTile*>(addIdx
						, m_vecTiles[addIdx.x][addIdx.y])
						);
				}
			}
		}
		else if (way == UnitWay::RightUp)
		{
			if (addIdx.x % 2 == 0)
			{
				addIdx.x = addIdx.x + 1;
				addIdx.y = addIdx.y - 1;
				if (addIdx.CheckInRange(m_nColumn, m_nRow)
					&& !CheckIsObstacle(addIdx))
				{
					map->insert(std::pair< INDEX, CTile*>(addIdx
						, m_vecTiles[addIdx.x][addIdx.y])
						);
				}
			}
			else
			{
				addIdx.x = addIdx.x + 1;
				addIdx.y = addIdx.y;
				if (addIdx.CheckInRange(m_nColumn, m_nRow)
					&& !CheckIsObstacle(addIdx))
				{
					map->insert(std::pair< INDEX, CTile*>(addIdx
						, m_vecTiles[addIdx.x][addIdx.y])
						);
				}
			}
		}
		else if (way == UnitWay::RightDown)
		{
			if (addIdx.x % 2 == 0)
			{
				addIdx.x = addIdx.x + 1;
				addIdx.y = addIdx.y;
				if (addIdx.CheckInRange(m_nColumn, m_nRow)
					&& !CheckIsObstacle(addIdx))
				{
					map->insert(std::pair< INDEX, CTile*>(addIdx
						, m_vecTiles[addIdx.x][addIdx.y])
						);
				}
			}
			else
			{
				addIdx.x = addIdx.x + 1;
				addIdx.y = addIdx.y + 1;
				if (addIdx.CheckInRange(m_nColumn, m_nRow)
					&& !CheckIsObstacle(addIdx))
				{
					map->insert(std::pair< INDEX, CTile*>(addIdx
						, m_vecTiles[addIdx.x][addIdx.y])
						);
				}
			}
		}
	}
}
BOOL CMap::CheckHeightDifference(INDEX idx1, INDEX idx2)
{
	//if (m_vecTiles[idx1.x][idx1.y]->GetUnit() != NULL)
	//{
	//	if (m_vecTiles[idx1.x][idx1.y]->GetUnit()->GetUnitName() == UnitName::Shon
	//		|| m_vecTiles[idx1.x][idx1.y]->GetUnit()->GetUnitName() == UnitName::Fairy
	//		|| m_vecTiles[idx1.x][idx1.y]->GetUnit()->GetUnitName() == UnitName::Marcia
	//		|| m_vecTiles[idx1.x][idx1.y]->GetUnit()->GetUnitName() == UnitName::Rucia)
	//		return TRUE;
	//}
	if (abs(m_vecTiles[idx1.x][idx1.y]->GetHeight() - m_vecTiles[idx2.x][idx2.y]->GetHeight()) >= 2)
	{
		return FALSE;
	}
	
	return TRUE;
}
BOOL CMap::IsInTile(CTile* tile, POINT inputPos, Camera camera)
{
	POINT vertex[4];
	double constant[4];

	//전달받은 인자의 위, 아래, 좌, 우측에 타일크기의 절반만큼되는 위치의 좌표를 구한다.
	//여기서는 왼쪽, 위쪽, 오른쪽, 아래쪽의 순서로 배열에 정리함.
	vertex[0].x = tile->GetX() + camera.viewPoint.x;
	vertex[0].y = vertex[2].y = tile->GetY() + TILE_HEIGHT_HALF + camera.viewPoint.y
		- TILE_HEIGHT_HALF * tile->GetHeight();

	vertex[1].x = vertex[3].x = tile->GetX() + TILE_WIDTH_HALF + camera.viewPoint.x;
	vertex[1].y = tile->GetY() + camera.viewPoint.y
		- TILE_HEIGHT_HALF * tile->GetHeight();
	vertex[2].x = tile->GetX() + TILE_WIDTH + camera.viewPoint.x;

	vertex[3].y = tile->GetY() + TILE_HEIGHT + camera.viewPoint.y
		- TILE_HEIGHT_HALF * tile->GetHeight();

	//위에서 구한 좌표 4개를 이용해서 선형방적식을 구하고
	//구한 방정식에서의 상수(C)값을 구한다.
	//y = mx + c;	--> c = y - mx; 
	constant[0] = vertex[0].y - (-TILE_GRADIENT) * vertex[0].x;
	constant[1] = vertex[1].y - TILE_GRADIENT * vertex[1].x;
	constant[2] = vertex[2].y - (-TILE_GRADIENT) * vertex[2].x;
	constant[3] = vertex[3].y - TILE_GRADIENT * vertex[3].x;
	
	//이제 마우스 좌표값과 위에서 구한 값을 이용해서
	//마우스 좌표값이 마름모 내부에 존재하는지 검사.
	if (!(-TILE_GRADIENT * inputPos.x - inputPos.y + constant[0] <= 0.0f))
		return FALSE;
	if (!(TILE_GRADIENT * inputPos.x - inputPos.y + constant[1] <= 0.0f))
		return FALSE;
	if (!(-TILE_GRADIENT * inputPos.x - inputPos.y + constant[2] >= 0.0f))
		return FALSE;
	if (!(TILE_GRADIENT * inputPos.x - inputPos.y + constant[3] >= 0.0f))
		return FALSE;
	return TRUE;
}
double CMap::CalculateDistance(double gradient, POINT pointA, POINT inputPos)
{
	//abs(aX1 + bY1 + c)
	//  / sqrt(pow(x) + pow(y))
	//
	return abs(inputPos.x + (1 / gradient) * inputPos.y + (1 / gradient)*pointA.y - pointA.x)
		/ sqrt(1 + pow(1 / gradient, 2));
}
BOOL CMap::CalculateEnemyAct(CUnit* unit, std::vector <CUnit*> vecUnits)
{
	if (unit->GetUnitTeam() == UnitTeam::North
		|| unit->GetCanAttack() == FALSE
		|| unit->GetCanMove() == FALSE)
		return FALSE;

	CUnit* target = NULL;
	INDEX idx, idxSave;

	if (unit->GetSkillNum() != 0)	//스킬이 있는 경우
	{
		if (unit->FindSkill(SKillName::Aid))
		{
		
			if (unit->GetMp() >= 5)//힐링 스킬이 있는 경우
			{
				CheckSkillTile(unit, unit->GetCurrentIndex(), 5, SkillAttackType::Contiguous);
				target = NULL;
				idx = unit->FindNearUnit(vecUnits, 2);
				if (idx.CheckInRange(m_nColumn, m_nRow))			//힐 스킬이 필요한 유닛이 있는 경우
				{
					target = m_vecTiles[idx.x][idx.y]->GetUnit();
					unit->SetNextUnitWay(unit->CheckUnitWay(unit->GetCurrentIndex(), idx));
					CheckSkillTile(unit, target->GetCurrentIndex(), 1, SkillAttackType::Contiguous);
					unit->SetSkillTarget();

					unit->HandleInput(SKillName::Aid);

					unit->GetStage()->SetCurrentUnit(unit);
					unit->GetStage()->SetPhase(NoticePhase::UsingSkillPhase);
					unit->EnterNextState();				//스킬 사용상태로 진입합니다.

					return TRUE;
				}
				//이동하지 않고, 힐 스킬을 사용할 유닛을 찾지 못한 경우
				if (unit->GetMovableTile().size() == 0)
					CheckMovableTile(unit);
				target = NULL;
				idx = unit->FindNextTile(vecUnits, this);
				idxSave = idx;
				if (idx.CheckInRange(m_nColumn, m_nRow)		//맵의 범위 안이고
					&& m_vecTiles[idx.x][idx.y]->GetIsUsable())	//지정된 위치에 다른 유닛이 없다면
				{
					unit->SetPrevTile(unit->GetCurrentIndex());
					unit->SetCurrentTile(idx);

					CheckSkillTile(unit, unit->GetCurrentIndex(), 5, SkillAttackType::Contiguous);
					idx = unit->FindNearUnit(vecUnits, 2);
					if (idx.CheckInRange(m_nColumn, m_nRow))
					{
						target = m_vecTiles[idx.x][idx.y]->GetUnit();
						unit->SetNextUnitWay(unit->CheckUnitWay(unit->GetCurrentIndex(), idx));
						CheckSkillTile(unit, target->GetCurrentIndex(), 1, SkillAttackType::Contiguous);
						unit->SetSkillTarget();

						unit->HandleInput(SKillName::Aid);

						unit->GetStage()->SetCurrentUnit(unit);
						unit->SetNextCommand(KeyInput::Skill);

						unit->ReturnToPrevPos();
						unit->SetNextTile(idxSave);
						SetUnitOnTile(idxSave, unit);
						SetUnitOnTile(unit->GetCurrentIndex(), NULL);
						unit->HandleInput(KeyInput::Move);
						unit->GetStage()->SetPhase(NoticePhase::NoActPhase);
						return TRUE;
					}
					else
					{
						unit->ReturnToPrevPos();
						/*unit->SetNextTile(idxSave);
						SetUnitOnTile(idxSave, unit);
						SetUnitOnTile(unit->GetCurrentIndex(), NULL);
						unit->HandleInput(KeyInput::Move);
						unit->GetStage()->SetPhase(NoticePhase::NoActPhase);
						return TRUE;*/
					}
				}
			}
			//return 되지 않고 이 부분까지 오면
			//스킬의 범위에 적이 들어오지 않은 경우입니다.
			if (CheckContiguousEnemy(unit->GetCurrentIndex()))//유닛이 이동하지 않고 공격이 가능한지 확인합니다.
			{
				if (unit->FindTargetUnit(&target))
				{
					unit->SetTargetUnit(target);
					unit->HandleInput(KeyInput::Attack);
					unit->GetStage()->SetPhase(NoticePhase::NoActPhase);
					return TRUE;
				}
				//가장 체력이 낮은 적을 공격합니다.
			}
			else	//유닛이 이동하고 공격이 가능한지 확인합니다.
			{
				if (unit->GetMovableTile().size() == 0)
					CheckMovableTile(unit);
				if (unit->FindTargetUnit(&target, this))
				{		//가장 체력이 낮은 적을 공격합니다.
					unit->SetNextCommand(KeyInput::Attack);
					unit->SetTargetUnit(target);
					unit->HandleInput(KeyInput::Move);
					/*unit->SetCanMove(FALSE);
					unit->SetCanAct(FALSE);*/
					unit->GetStage()->SetPhase(NoticePhase::NoActPhase);
					return TRUE;
				}
				else	//불가능한 경우
				{
					1;
				}
			}
		}
		else //기타 공격 스킬이 있는 경우
		{
			if (unit->GetMp() >= 10 && (unit->FindSkill(SKillName::Explosion)
				|| unit->FindSkill(SKillName::Curse)
				|| unit->FindSkill(SKillName::Edge)
				|| unit->FindSkill(SKillName::Thunder)
				|| unit->FindSkill(SKillName::Hurricane)))
			{
				CheckSkillTile(unit, unit->GetCurrentIndex(), 5, SkillAttackType::Contiguous);
				target = NULL;
				idx = unit->FindNearUnit(vecUnits);
				if (idx.CheckInRange(m_nColumn, m_nRow))
				{
					target = m_vecTiles[idx.x][idx.y]->GetUnit();
					unit->SetNextUnitWay(unit->CheckUnitWay(unit->GetCurrentIndex(), idx));
					CheckSkillTile(unit, target->GetCurrentIndex(), 1, SkillAttackType::Contiguous);
					unit->SetSkillTarget();
					if (unit->FindSkill(SKillName::Explosion))
						unit->HandleInput(SKillName::Explosion);

					else if (unit->FindSkill(SKillName::Curse))
						unit->HandleInput(SKillName::Curse);

					else if (unit->FindSkill(SKillName::Edge))
						unit->HandleInput(SKillName::Edge);

					else if (unit->FindSkill(SKillName::Hurricane))
						unit->HandleInput(SKillName::Hurricane);

					else if (unit->FindSkill(SKillName::Thunder))
						unit->HandleInput(SKillName::Thunder);

					unit->GetStage()->SetCurrentUnit(unit);
					unit->GetStage()->SetPhase(NoticePhase::UsingSkillPhase);
					unit->EnterNextState();				//스킬 사용상태로 진입합니다.

					return TRUE;
				}

				if (unit->GetMovableTile().size() == 0)
					CheckMovableTile(unit);
				target = NULL;
				idx = unit->FindNextTile(vecUnits, this);
				idxSave = idx;
				if (idx.CheckInRange(m_nColumn, m_nRow)		//맵의 범위 안이고
					&& m_vecTiles[idx.x][idx.y]->GetIsUsable())	//지정된 위치에 다른 유닛이 없다면
				{
					unit->SetPrevTile(unit->GetCurrentIndex());
					unit->SetCurrentTile(idx);

					CheckSkillTile(unit, unit->GetCurrentIndex(), 5, SkillAttackType::Contiguous);
					idx = unit->FindNearUnit(vecUnits, 0);
					if (idx.CheckInRange(m_nColumn, m_nRow))
					{
						target = m_vecTiles[idx.x][idx.y]->GetUnit();
						unit->SetNextUnitWay(unit->CheckUnitWay(unit->GetCurrentIndex(), idx));
						CheckSkillTile(unit, target->GetCurrentIndex(), 1, SkillAttackType::Contiguous);
						unit->SetNextUnitWay(unit->CheckUnitWay(unit->GetCurrentIndex(), idx));
						unit->SetSkillTarget();
						if (unit->FindSkill(SKillName::Explosion))
							unit->HandleInput(SKillName::Explosion);

						else if (unit->FindSkill(SKillName::Curse))
							unit->HandleInput(SKillName::Curse);

						else if (unit->FindSkill(SKillName::Edge))
							unit->HandleInput(SKillName::Edge);

						else if (unit->FindSkill(SKillName::Hurricane))
							unit->HandleInput(SKillName::Hurricane);

						else if (unit->FindSkill(SKillName::Thunder))
							unit->HandleInput(SKillName::Thunder);
						unit->GetStage()->SetCurrentUnit(unit);
						unit->SetNextCommand(KeyInput::Skill);

						unit->ReturnToPrevPos();
						unit->SetNextTile(idxSave);
						SetUnitOnTile(idxSave, unit);
						SetUnitOnTile(unit->GetCurrentIndex(), NULL);
						unit->HandleInput(KeyInput::Move);
						unit->GetStage()->SetPhase(NoticePhase::NoActPhase);
						return TRUE;
					}
					else
					{
						unit->ReturnToPrevPos();
						unit->SetNextTile(idxSave);
						SetUnitOnTile(idxSave, unit);
						SetUnitOnTile(unit->GetCurrentIndex(), NULL);
						unit->HandleInput(KeyInput::Move);
						unit->GetStage()->SetPhase(NoticePhase::NoActPhase);
						return TRUE;
					}
					//unit->ReturnToPrevPos();
				}
			}
			if (unit->GetMp() >= 20 && (unit->FindSkill(SKillName::FlameBurst)
				|| unit->FindSkill(SKillName::EvillEye)
				|| unit->FindSkill(SKillName::Earthquake)
				|| unit->FindSkill(SKillName::ThunderFlare)
				|| unit->FindSkill(SKillName::WindBlast)))
			{
				CheckSkillTile(unit, unit->GetCurrentIndex(), 5, SkillAttackType::Line);
				target = NULL;
				idx = unit->FindNearUnit(vecUnits);
				if (idx.CheckInRange(m_nColumn, m_nRow))
				{
					target = m_vecTiles[idx.x][idx.y]->GetUnit();
					unit->SetNextUnitWay(unit->CheckUnitWay(unit->GetCurrentIndex(), idx));
					CheckSkillTile(unit, unit->GetCurrentIndex(), 5, SkillAttackType::Line);
					unit->SetSkillTarget();
					if (unit->FindSkill(SKillName::FlameBurst))
						unit->HandleInput(SKillName::FlameBurst);

					else if (unit->FindSkill(SKillName::EvillEye))
						unit->HandleInput(SKillName::EvillEye);

					else if (unit->FindSkill(SKillName::Earthquake))
						unit->HandleInput(SKillName::Earthquake);

					else if (unit->FindSkill(SKillName::WindBlast))
						unit->HandleInput(SKillName::WindBlast);

					else if (unit->FindSkill(SKillName::ThunderFlare))
						unit->HandleInput(SKillName::ThunderFlare);

					unit->GetStage()->SetCurrentUnit(unit);
					unit->GetStage()->SetPhase(NoticePhase::UsingSkillPhase);
					unit->EnterNextState();				//스킬 사용상태로 진입합니다.

					return TRUE;
				}

				if (unit->GetMovableTile().size() == 0)
					CheckMovableTile(unit);
				target = NULL;
				idx = unit->FindNextTile(vecUnits, this);
				idxSave = idx;
				if (idx.CheckInRange(m_nColumn, m_nRow)		//맵의 범위 안이고
					&& m_vecTiles[idx.x][idx.y]->GetIsUsable())	//지정된 위치에 다른 유닛이 없다면
				{
					unit->SetPrevTile(unit->GetCurrentIndex());
					unit->SetCurrentTile(idx);

					CheckSkillTile(unit, unit->GetCurrentIndex(), 5, SkillAttackType::Line);
					idx = unit->FindNearUnit(vecUnits, 0);
					if (idx.CheckInRange(m_nColumn, m_nRow))
					{
						target = m_vecTiles[idx.x][idx.y]->GetUnit();
						unit->SetNextUnitWay(unit->CheckUnitWay(unit->GetCurrentIndex(), idx));
						CheckSkillTile(unit, unit->GetCurrentIndex(), 5, SkillAttackType::Line);
						unit->SetNextUnitWay(unit->CheckUnitWay(unit->GetCurrentIndex(), idx));
						unit->SetSkillTarget();
						if (unit->FindSkill(SKillName::FlameBurst))
							unit->HandleInput(SKillName::FlameBurst);

						else if (unit->FindSkill(SKillName::EvillEye))
							unit->HandleInput(SKillName::EvillEye);

						else if (unit->FindSkill(SKillName::Earthquake))
							unit->HandleInput(SKillName::Earthquake);

						else if (unit->FindSkill(SKillName::WindBlast))
							unit->HandleInput(SKillName::WindBlast);

						else if (unit->FindSkill(SKillName::ThunderFlare))
							unit->HandleInput(SKillName::ThunderFlare);
						unit->GetStage()->SetCurrentUnit(unit);
						unit->SetNextCommand(KeyInput::Skill);

						unit->ReturnToPrevPos();
						unit->SetNextTile(idxSave);
						SetUnitOnTile(idxSave, unit);
						SetUnitOnTile(unit->GetCurrentIndex(), NULL);
						unit->HandleInput(KeyInput::Move);
						unit->GetStage()->SetPhase(NoticePhase::NoActPhase);
						return TRUE;
					}
					else
					{
						unit->ReturnToPrevPos();
						unit->SetNextTile(idxSave);
						SetUnitOnTile(idxSave, unit);
						SetUnitOnTile(unit->GetCurrentIndex(), NULL);
						unit->HandleInput(KeyInput::Move);
						unit->GetStage()->SetPhase(NoticePhase::NoActPhase);
						return TRUE;
					}
					//unit->ReturnToPrevPos();
				}
			}
		}
		//return 되지 않고 이 부분까지 오면
		//스킬의 사용범위 + 이동범위에 스킬의 대상이 없는 경우입니다.
		//이 경우에는 공격 범위 역시 같은 결과값을 가지니
		//이동을 하도록 합니다.
	}
								//스킬이 없는 경우
	{
		if (CheckContiguousEnemy(unit->GetCurrentIndex()))//유닛이 이동하지 않고 공격이 가능한지 확인합니다.
		{
			if (unit->FindTargetUnit(&target))
			{
				unit->SetTargetUnit(target);
				unit->HandleInput(KeyInput::Attack);
				unit->GetStage()->SetPhase(NoticePhase::NoActPhase);
				return TRUE;
			}
			//가장 체력이 낮은 적을 공격합니다.
		}
		else	//유닛이 이동하고 공격이 가능한지 확인합니다.
		{
			if (unit->GetMovableTile().size() == 0)
				CheckMovableTile(unit);
			if (unit->FindTargetUnit(&target, this))
			{		//가장 체력이 낮은 적을 공격합니다.
				unit->SetNextCommand(KeyInput::Attack);
				unit->SetTargetUnit(target);
				unit->HandleInput(KeyInput::Move);
				/*unit->SetCanMove(FALSE);
				unit->SetCanAct(FALSE);*/
				unit->GetStage()->SetPhase(NoticePhase::NoActPhase);
				return TRUE;
			}
			else	//불가능한 경우
			{		
				1;
			}
		}
	}
	//여기까지 오면 유닛이 공격 및 스킬을 사용할 대상을 찾지 못한 것입니다.
	//유닛을 이동시킵니다.
	//가장 가까운 적 유닛쪽으로 유닛을 이동시킵니다.
	if(unit->GetMovableTile().size() == 0)
		CheckMovableTile(unit);
	idx = unit->FindNextTile(vecUnits, this);
	if (idx.CheckInRange(m_nColumn, m_nRow)
		&& m_vecTiles[idx.x][idx.y]->GetIsUsable())
	{
		unit->SetNextUnitWay(unit->CheckUnitWay(unit->GetCurrentIndex(), idx));
		unit->SetNextTile(idx);
		unit->SetNextCommand(KeyInput::Idle);
		SetUnitOnTile(idx, unit);
		SetUnitOnTile(unit->GetCurrentIndex(), NULL);
		unit->HandleInput(KeyInput::Move);
		unit->GetStage()->SetPhase(NoticePhase::NoActPhase);
	}
	unit->SetCanAct(FALSE);
	unit->SetCanMove(FALSE);
	return TRUE;
}

BOOL CMap::CheckIsUsableTile(INDEX idx)
{
	return m_vecTiles[idx.x][idx.y]->GetIsUsable();
}
BOOL CMap::CheckIsObstacle(INDEX idx)
{
	return m_vecTiles[idx.x][idx.y]->GetIsObstacle();
}
std::vector< std::vector<CTile*> > CMap::GetTileArray()
{
	return m_vecTiles;
}
INDEX CMap::GetTilePos(int index_i, int index_j)
{
	if (index_i < 0 && index_i >= m_nRow)
	{
		assert(!_T("에러"));
	}
	else if (index_j < 0 && index_j >= m_nRow)
	{
		assert(!_T("에러"));
	}
	return m_vecTiles[index_i][index_j]->GetTilePos();
}
POINT CMap::GetTilePos(POINT mouseValue, CIndex *idx, Camera camera)
{
	BOOL bChecked = FALSE;
	POINT returnPoint = { -1, -1 };
	INDEX returnIndex;
	for (int i = 0; i < m_nRow; ++i)
	{
		for (int j = 0; j < m_nColumn; ++j)
		{
			if (IsInTile(m_vecTiles[i][j], mouseValue, camera))
			{
				returnPoint.x = m_vecTiles[i][j]->GetX() + camera.viewPoint.x;
				returnPoint.y = m_vecTiles[i][j]->GetY() - m_vecTiles[i][j]->GetHeight() * 16 + camera.viewPoint.y;
				idx->x = i;
				idx->y = j;
				idx->height = m_vecTiles[i][j]->GetHeight();
				
				if (bChecked)
				{
					if (idx->height > returnIndex.height)
					{
						returnIndex.x = idx->x;
						returnIndex.y = idx->y;
						returnIndex.height = idx->height;

						//returnPoint = mouseValue;
					}
				}
				else// if (idx->CheckInRange(m_nColumn, m_nRow))
				{
					returnIndex.x = i;
					returnIndex.y = j;
					returnIndex.height = idx->height;

					//returnPoint = mouseValue;
					bChecked = TRUE;
					//return mouseValue;
				}
			}
			
		}
	}
	//if (returnPoint.x != -1)
	//{
	//	idx->x = returnIndex.x;
	//	idx->y = returnIndex.y;
	//	idx->height = returnIndex.height;

	//	
	//}
	return returnPoint;
	mouseValue.x = -1;
	mouseValue.y = -1;
	return mouseValue;
}
CUnit* CMap::GetUnitOnTile(INDEX idx)
{
	return m_vecTiles[idx.x][idx.y]->GetUnit();
}
int CMap::GetHeight	(INDEX idx)
{ 
	if (idx.CheckInRange())
	{
		return m_vecTiles[idx.x][idx.y]->GetHeight();
	}
	return 0;
}
void CMap::SetUnitOnTile(INDEX idx, CUnit* unit)
{
	m_vecTiles[idx.x][idx.y]->SetUnit(unit);
}

void CMap::SetTileIsUsable(INDEX idx, BOOL inputValue)
{
	m_vecTiles[idx.x][idx.y]->SetIsUsalbe(inputValue);
}
void CMap::CheckMovableTile(CUnit* unit)
{
	unit->ClearMovableTile(); //새로 함수가 실행되면 이전에 저장된 내용은 삭제한다.

	if (unit->GetHp() <= 0)
		return;

	INDEX idx = unit->GetCurrentIndex();
	idx.height = m_vecTiles[idx.x][idx.y]->GetHeight();

	std::map< INDEX, Node* > openMap;	//탐색목록
	std::map < INDEX, Node*> closeMap;  //추가된 목록(확인ok)
	std::map < INDEX, Node* > searchedValue;

	openMap.insert(std::pair< INDEX, Node*>(idx, new Node(idx, m_vecTiles[idx.x][idx.y]->GetTilePos())));
	
	if (unit->GetCanMove() == FALSE)	//유닛이 이미 이동하고 난 뒤라면
		return;							//이동 가능 타일을 생성하지 않음

	std::map< INDEX, Node*>::iterator mapIter;
	std::vector < INDEX >::iterator vecIter;
	for (int i = 0; i <= unit->GetMoveRange(); ++i)
	{
		for (mapIter = openMap.begin(); mapIter != openMap.end(); ++mapIter)
		{
			if (closeMap.find(mapIter->first) != closeMap.end())	//이미 탐색한 목록에 있다면
				continue;											//건너뜁니다.
	
			idx = mapIter->first;
			AddContiguousTile(&searchedValue, idx, mapIter->second); //탐색목록에 있는 값을 토대로 주변 타일들을 검색 및 추가합니다.
			closeMap.insert(std::pair< INDEX, Node*>(mapIter->first, mapIter->second));	
			//한 번 탐색한 타일은 재탐색하지 않도록 값을 저장해둡니다.
		}
		openMap.clear();	//검색된 값을 토대로 탐색목록을 재구성하기 전, 기존 값을 삭제합니다.
		
		openMap = searchedValue;
		searchedValue.clear();	//탐색이 끝난 후에는 탐색값을 삭제합니다.
	}
	openMap.clear();
	unit->SetMovableTile(closeMap);
}

void CMap::CheckSkillTile(CUnit* unit, INDEX idx, int skillRange, SkillAttackType type)
{
	unit->ClearSkillTile(); //새로 함수가 실행되면 이전에 저장된 내용은 삭제한다.
	unit->ClearTargetUnit();

	if (unit->GetHp() <= 0)
		return;
	if (!unit->GetCanAttack())
		return;
	//INDEX idx = unit->GetCurrentIndex();	//유닛이 위치한 타일의 인덱스를 가져옵니다.

	std::map< INDEX, CTile* > openMap;	//탐색목록
	std::map < INDEX, CTile*> closeMap;  //추가된 목록(확인ok)
	std::map < INDEX, CTile* > searchedValue;

	std::map< INDEX, CTile*>::iterator mapIter;
	std::vector < INDEX >::iterator vecIter;
	
	openMap.insert(std::pair< INDEX, CTile*>(idx, m_vecTiles[idx.x][idx.y]));
	//유닛이 위치한 타일을 추가합니다.

	if (type == SkillAttackType::Contiguous)
	{
		for (int i = 0; i <= skillRange; ++i)
		{
			for (mapIter = openMap.begin(); mapIter != openMap.end(); ++mapIter)
			{
				if (closeMap.find(mapIter->first) != closeMap.end())	//이미 탐색한 목록에 있다면
					continue;											//건너뜁니다.

				idx = mapIter->first;

				AddContiguousTile(unit,&searchedValue, idx); //탐색목록에 있는 값을 토대로 주변 타일들을 검색 및 추가합니다.
				closeMap.insert(std::pair< INDEX, CTile*>(mapIter->first, mapIter->second));
				//한 번 탐색한 타일은 재탐색하지 않도록 값을 저장해둡니다.
			}
			openMap.clear();	//검색된 값을 토대로 탐색목록을 재구성하기 전, 기존 값을 삭제합니다.

			openMap = searchedValue;
			searchedValue.clear();	//탐색이 끝난 후에는 탐색값을 삭제합니다.
		}
		openMap.clear();
		unit->SetSkillTile(closeMap);
	}
	else if (type == SkillAttackType::Line)
	{
		for (int i = 0; i < 4; ++i)
		{
			AddLineTile(unit,&searchedValue, idx, (UnitWay)i, skillRange);
		}
		unit->SetSkillTile(searchedValue);
	}
}
void CMap::CheckSkillTile(CUnit* unit, INDEX idx, SKillName skill)
{
	switch (skill)
	{
	case SKillName::Explosion :
		CheckSkillTile(unit, idx, 1 , SkillAttackType::Contiguous);
		break;
	case SKillName::FlameBurst:
		CheckSkillTile(unit, unit->GetCurrentIndex(), 5, SkillAttackType::Line);
		break;
	case SKillName::Aid:
		CheckSkillTile(unit, idx, 0, SkillAttackType::Contiguous);
		break;
	case SKillName::ManaAid:
		CheckSkillTile(unit, idx, 0, SkillAttackType::Contiguous);
		break;
	case SKillName::Mercy:
		CheckSkillTile(unit, idx, 1, SkillAttackType::Contiguous);
		break;
	case SKillName::Resurrection:
		CheckSkillTile(unit, idx, 0, SkillAttackType::Contiguous);
		break;
	case SKillName::Sacrifice:
		CheckSkillTile(unit, idx, 1, SkillAttackType::Contiguous);
		break;
	case SKillName::Edge:
		CheckSkillTile(unit, idx, 1, SkillAttackType::Contiguous);
		break;
	case SKillName::Earthquake:
		CheckSkillTile(unit, unit->GetCurrentIndex(), 5, SkillAttackType::Line);
		break;
	case SKillName::Hurricane:
		CheckSkillTile(unit, idx, 1, SkillAttackType::Contiguous);
		break;
	case SKillName::WindBlast:
			CheckSkillTile(unit, unit->GetCurrentIndex(), 5, SkillAttackType::Line);
			break;
	case SKillName::Thunder:
		CheckSkillTile(unit, idx, 1, SkillAttackType::Contiguous);
		break;
	case SKillName::ThunderFlare:
		CheckSkillTile(unit, unit->GetCurrentIndex(), 5, SkillAttackType::Line);
		break;
	case SKillName::Curse:
		CheckSkillTile(unit, idx, 1, SkillAttackType::Contiguous);
		break;
	case SKillName::EvillEye:
		CheckSkillTile(unit, unit->GetCurrentIndex(), 5, SkillAttackType::Line);
		break;
	}
}

void CMap::MakeMap()		//랜덤 맵 생성
{
	//하드코딩입니다.
	//수정이 필요합니다.
	int random = rand() % 100;
	for (int i = 0; i < m_nRow; ++i)
	{
		for (int j = 0; j < m_nColumn; ++j)
		{
			random = rand() % 10;
			switch (random)
			{
			case 0:
			case 1:
			case 2:
			case 3:
				m_vecTiles[i][j] = new CTile(CTile::TileType::PLAIN
					, TILE_WIDTH / 2 * (j % 2) + TILE_WIDTH * i
					, TILE_HEIGHT * j / 2
					, 0 
					, 0	
					);
				break;
			case 4:
				m_vecTiles[i][j] = new CTile(CTile::TileType::HILL
					, TILE_WIDTH / 2 * (j % 2) + TILE_WIDTH * i
					, TILE_HEIGHT * j / 2
					, 0
					, 12
					);
				m_vecTiles[i][j]->MakeUptile();
				m_vecTiles[i][j]->SetHeight(rand() % 5 + 1);
				break;
			case 5:
			case 6:
			case 7:
			case 8:
				m_vecTiles[i][j] = new CTile(CTile::TileType::PLAIN
					, TILE_WIDTH / 2 * (j % 2) + TILE_WIDTH * i
					, TILE_HEIGHT * j / 2
					, 1
					, 0
					);
				break;
			case 9:
				m_vecTiles[i][j] = new CTile(CTile::TileType::HILL
					, TILE_WIDTH / 2 * (j % 2) + TILE_WIDTH * i
					, TILE_HEIGHT * j / 2
					, 1
					, 12
					);
				m_vecTiles[i][j]->MakeUptile();
				m_vecTiles[i][j]->SetHeight(rand() % 5 + 1);
				break;
			}
		}
	}
}
void CMap::MakeMap(LPCTSTR szPath)
{
	std::ifstream ifile;

	char line[30]; // 한 줄씩 읽어서 임시로 저장할 공간
	int num[3];		
	int i = 0, j = 0;
	int space = 0;

	ifile.open(szPath);  // 파일 열기
	
	if (ifile.is_open())
	{
		ifile.getline(line, sizeof(line));
		space = 0;
		num[0] = atoi(&line[0]);

		for (int i = 1; i < num[0]; i *= 10)
			space++;
		num[1] = atoi(&line[space + 1]);
		
		m_nRow = num[0];
		m_nColumn = num[1];

		std::vector <CTile*> vecTemp;
		for (int i = 0; i < m_nRow; ++i)
		{
			vecTemp.resize(m_nColumn);
			m_vecTiles.push_back(vecTemp);
		}

		while (ifile.getline(line, sizeof(line))) // 한 줄씩 읽어 처리를 시작한다.
		{
			space = 0;
			num[0] = atoi(&line[0]);
			if (num[0] >= 10)
				space++;
			num[1] = atoi(&line[space + 1]);
			if (num[1] >= 10)
				space++;
			if (num[1] >= 100)
				space++;
			if (num[1] >= 1000)
				space++;
			num[2] = atoi(&line[space + 3]);
			/*m_ptLeftTop.x = TILE_WIDTH * m_idxIndex.x / 2;
			m_ptLeftTop.y = TILE_HEIGHT / 2 * (m_idxIndex.x % 2) + TILE_HEIGHT * m_idxIndex.y
				- TILE_HEIGHT_HALF * height; */
			if (num[0] == 0)
			{
				m_vecTiles[i][j] = new CTile(CTile::TileType::PLAIN
					, TILE_WIDTH * i / 2
					, TILE_HEIGHT / 2 * (i % 2) + TILE_HEIGHT * j 
					, num[1]
					, num[2]
					);
			}
			else
			{
				m_vecTiles[i][j] = new CTile(CTile::TileType::HILL
					, TILE_WIDTH * i / 2
					, TILE_HEIGHT / 2 * (i % 2) + TILE_HEIGHT * j
					, num[1]
					, 12
					);
				
				m_vecTiles[i][j]->SetHeight(num[0]);
				m_vecTiles[i][j]->MakeUptile(num[2]);
				
			}
			if (num[0] == 0 && num[1] == 0 && num[2] == 11
				 || num[1] == 9)
				m_vecTiles[i][j]->SetIsObstacle(TRUE);

			j++;
			if (j >= m_nColumn)
			{
				i++;
				j = 0;
			}
		}
	}

	ifile.close(); // 파일 닫기

}
void CMap::LoadUnit(LPCTSTR szPath,std::vector <CUnit*> *vecUnits)
{
	std::ifstream ifile;

	char line[150]; // 한 줄씩 읽어서 임시로 저장할 공간
	int num[14];
	std::vector <short> skill;
	int i = 0, j = 0;
	int space = 0;
	int unitCount = 0;

	ifile.open(szPath);  // 파일 열기

	if (ifile.is_open())
	{
		ifile.getline(line, sizeof(line));
		while (ifile.getline(line, sizeof(line))) // 한 줄씩 읽어 처리를 시작한다.
		{
			INDEX idx;
			INDEX parament;

			space = 0;
			num[0] = atoi(&line[0]);
			skill.clear();				//스킬 벡터 초기화

			for (int i = 0; i < 14; ++i)
			{
				num[i] = atoi(&line[space + i]);
				if (num[i] == 0)
					space++;
				else
				{
					for (int j = 1; j <= num[i]; j *= 10)
						space++;
				}
			}
			if (line[space + 13] != '\0')
			{
				int i = 13;
				while (line[space + i] != '\0')
				{
					skill.push_back(atoi(&line[space + i]));
					if (atoi(&line[space + i]) == 0)
						space++;
					else
					{
						for (int j = 1; j <= atoi(&line[space + i]); j *= 10)
							space++;
					}
					++i;
				}
			}
			idx.x = num[2];
			idx.y = num[3];
			idx.height = m_vecTiles[idx.x][idx.y]->GetHeight();

			parament = { idx.GetXPos(), idx.GetYPos(), idx.height };
			parament.height = idx.height;

			GetTilePos(idx.x, idx.y);
			switch ((UnitName)(num[0] + num[1] * 9))
			{
			case UnitName::Aris:
				vecUnits->push_back(new CAris(parament));
				SetUnitOnTile((idx), (*vecUnits)[unitCount]);
				break;
			case UnitName::Arl:
				vecUnits->push_back(new CArl(parament));
				SetUnitOnTile((idx), (*vecUnits)[unitCount]);
				break;
			case UnitName::BlackKnight:
				vecUnits->push_back(new CBlackKnight(parament));
				SetUnitOnTile((idx), (*vecUnits)[unitCount]);
				break;
			case UnitName::Cat:
				vecUnits->push_back(new CCat(parament));
				SetUnitOnTile((idx), (*vecUnits)[unitCount]);
				break;
			case UnitName::Catherine:
				vecUnits->push_back(new CCatherine(parament));
				SetUnitOnTile((idx), (*vecUnits)[unitCount]);
				break;
			case UnitName::Crab:
				vecUnits->push_back(new CCrab(parament));
				SetUnitOnTile((idx), (*vecUnits)[unitCount]);
				break;
			case UnitName::Fairy:
				vecUnits->push_back(new CFairy(parament));
				SetUnitOnTile((idx), (*vecUnits)[unitCount]);
				break;
			case UnitName::Farm:
				vecUnits->push_back(new CFarm(parament));
				SetUnitOnTile((idx), (*vecUnits)[unitCount]);
				break;
			case UnitName::Ivan:
				vecUnits->push_back(new CIvan(parament));
				SetUnitOnTile((idx), (*vecUnits)[unitCount]);
				break;
			case UnitName::Karin:
				vecUnits->push_back(new CKarin(parament));
				SetUnitOnTile((idx), (*vecUnits)[unitCount]);
				break;
			case UnitName::Marcia:
				vecUnits->push_back(new CMarcia(parament));
				SetUnitOnTile((idx), (*vecUnits)[unitCount]);
				break;
			case UnitName::Reon:
				vecUnits->push_back(new CReon(parament));
				SetUnitOnTile((idx), (*vecUnits)[unitCount]);
				break;
			case UnitName::Rian:
				vecUnits->push_back(new CRian(parament));
				SetUnitOnTile((idx), (*vecUnits)[unitCount]);
				break;
			case UnitName::Rucia:
				vecUnits->push_back(new CRucia(parament));
				SetUnitOnTile((idx), (*vecUnits)[unitCount]);
				break;
			case UnitName::Ruru:
				vecUnits->push_back(new CRuru(parament));
				SetUnitOnTile((idx), (*vecUnits)[unitCount]);
				break;
			case UnitName::Shon:
				vecUnits->push_back(new CShon(parament));
				SetUnitOnTile((idx), (*vecUnits)[unitCount]);
				break;
			case UnitName::Wolf:
				vecUnits->push_back(new CWolf(parament));
				SetUnitOnTile((idx), (*vecUnits)[unitCount]);
				break;
			case UnitName::YoungKarin:
				vecUnits->push_back(new CYoungKarin(parament));
				SetUnitOnTile((idx), (*vecUnits)[unitCount]);
				break;
			}
			if (num[4] == 0)
				(*vecUnits)[unitCount]->SetTeam(UnitTeam::North);
			else 
				(*vecUnits)[unitCount]->SetTeam(UnitTeam::West);
			(*vecUnits)[unitCount]->SetMaxHp(num[5]);
			(*vecUnits)[unitCount]->SetHp(num[5]);
			(*vecUnits)[unitCount]->SetMaxMp(num[6]);
			(*vecUnits)[unitCount]->SetMp(num[6]);
			(*vecUnits)[unitCount]->SetMoveRange(num[7]);
			(*vecUnits)[unitCount]->SetStrength(num[8]);
			(*vecUnits)[unitCount]->SetIntelligence(num[9]);
			(*vecUnits)[unitCount]->SetAgility(num[10]);
			(*vecUnits)[unitCount]->SetDefense(num[11]);
			(*vecUnits)[unitCount]->SetMagicDefense(num[12]);

			if (num[13] != 0)
			{
				(*vecUnits)[unitCount]->ClearSkillList();
				
				for (int k = 0; k < (int)skill.size(); ++k)
				{
					(*vecUnits)[unitCount]->AddSkill((SKillName)skill[k]);
				}
			}
			unitCount++;
		}
	}
}
void CMap::DrawTile(HDC hdc, CTile* tile, int cy, Camera camera)
{
	/*if (tile->GetImageX() / TILE_WIDTH == 0 && tile->GetImageY() / TILE_HEIGHT == 11)
	{
		m_tileImage.TransparentBlt(hdc
			, tile->GetX() + camera.viewPoint.x
			, cy + camera.viewPoint.y
			, TILE_WIDTH
			, TILE_HEIGHT
			, 9 * TILE_WIDTH
			, 0
			, TILE_WIDTH
			, TILE_HEIGHT
			, RGB(255, 0, 255)
			);
	}*/
	m_tileImage.TransparentBlt(hdc
		, tile->GetX() + camera.viewPoint.x
		, cy + camera.viewPoint.y
		, TILE_WIDTH
		, TILE_HEIGHT
		, tile->GetImageX()
		, tile->GetImageY()
		, TILE_WIDTH
		, TILE_HEIGHT
		, RGB(255, 0, 255)
		);
}
void CMap::DrawTile(HDC hdc, CTile* tile, Camera camera)
{
	if (tile->GetHeight() != 0)
	{
		DrawHill(hdc, tile, camera);
		return;
	}
	DrawTile(hdc, tile, tile->GetY(), camera);
}

void CMap::DrawHill(HDC hdc, CTile* tile, Camera camera)
{
	//int height = 1;
	int height = tile->GetHeight();

	for (int i = 0; i < height; ++i)
	{
		DrawTile(hdc, tile, tile->GetY() - (16 * i), camera);
	}
	DrawTile(hdc, tile->GetUpTile(), tile->GetY() - (16 * height), camera);
}

void CMap::DrawMap(HDC hdc, int division, Camera camera )
{
	if (division == 1)
	{
		for (int i = 0; i < m_nColumn; ++i)
		{
			for (int j = 0; j < m_nRow; ++j)
			{
				DrawTile(hdc
					, m_vecTiles[j][i]
					, camera
					);
			}
		}
	}
	else if (division == 2)
	{	
	/*	for (int i = 0; i < m_nColumn; ++i)
		{
			for (int j = 0; j < m_nRow; ++j)
			{
				if (j % 2 == 0)
				{
					DrawTile(hdc
						, m_vecTiles[j][i]
						, camera
						);
				}
			}
			for (int j = 0; j < 30; ++j)
			{
				if (j % 2 == 1)
				{
					DrawTile(hdc
						, m_vecTiles[j][i]
						, camera
						);
				}
			}
		}*/
		for (int i = 0; i < m_nColumn; ++i)
		{
			for (int j = 0; j < m_nRow; j += 2)
			{

				DrawTile(hdc
					, m_vecTiles[j][i]
					, camera
					);

			}
			for (int j = 1; j < m_nRow; j += 2)
			{
				DrawTile(hdc
					, m_vecTiles[j][i]
					, camera
					);
			}
		}
	}
}

void CMap::OnDraw(HDC hdc, std::vector <CUnit*>unit,int divison, Camera camera )
{
	if (divison == 0)
	{
		for (int i = 0; i < m_nColumn; ++i)
		{
			for (int j = 0; j < m_nRow; j += 2)
			{
				DrawTile(hdc
					, m_vecTiles[j][i]
					, camera
					);
				for (int k = 0; k < (int)unit.size(); ++k)
				{
					if (unit[k]->GetCurrentIndex().x == j
						&& unit[k]->GetCurrentIndex().y == i)
					{
						unit[k]->OnDraw(hdc, camera);
					}
				}
			}

			for (int j = 1; j < m_nRow; j += 2)
			{
				DrawTile(hdc
					, m_vecTiles[j][i]
					, camera
					);
				for (int k = 0; k < (int)unit.size(); ++k)
				{
					if (unit[k]->GetCurrentIndex().x == j
						&& unit[k]->GetCurrentIndex().y == i)
					{
						unit[k]->OnDraw(hdc, camera);
					}
				}
			}
		}
	}
	else if (divison == 1)
	{
		for (int i = 0; i < m_nColumn; ++i)
		{
			for (int j = 0; j < m_nRow; j += 2)
			{
				DrawTile(hdc
					, m_vecTiles[j][i]
					, camera
					);
				
				for (int k = 0; k < (int)unit.size(); ++k)
				{
					if (unit[k]->CheckIsMovableTile(INDEX{ j,i , 0})
						&& unit[k]->GetUnitTeam() != UnitTeam::West)
					{
						unit[k]->DrawMovableTile(hdc, INDEX{ j,i ,0}, camera);
					}	
					if (unit[k]->GetCurrentIndex().x == j
						&& unit[k]->GetCurrentIndex().y == i)
					{
						unit[k]->OnDraw(hdc, camera);
						break;
					}
				}
			}

			for (int j = 1; j < m_nRow; j += 2)
			{
				DrawTile(hdc
					, m_vecTiles[j][i]
					, camera
					);
			
				for (int k = 0; k < (int)unit.size(); ++k)
				{
					if (unit[k]->CheckIsMovableTile(INDEX{ j,i , 0})
						 && unit[k]->GetUnitTeam() != UnitTeam::West)
					{
						unit[k]->DrawMovableTile(hdc, INDEX{ j,i , 0}, camera);
					}
					if (unit[k]->GetCurrentIndex().x == j
						&& unit[k]->GetCurrentIndex().y == i)
					{
						unit[k]->OnDraw(hdc, camera);
						break;
					}
				}
			}
		}
	}
	else if (divison == 2)
	{
		for (int i = 0; i < m_nColumn; ++i)
		{
			for (int j = 0; j < m_nRow; j += 2)
			{
				DrawTile(hdc
					, m_vecTiles[j][i]
					, camera
					);
				for (int k = 0; k < (int)unit.size(); ++k)
				{
					if (unit[k]->CheckIsAttackableTile(INDEX{ j, i , 0})
						&& unit[k]->GetUnitTeam() != UnitTeam::West)
					{
						unit[k]->DrawAttackableTile(hdc, INDEX{ j,i , 0}, camera);
						break;
					}
				}
				for (int k = 0; k < (int)unit.size(); ++k)
				{
					if (unit[k]->GetCurrentIndex().x == j
						&& unit[k]->GetCurrentIndex().y == i)
					{
						unit[k]->OnDraw(hdc, camera);
						break;
					}
				}
			}

			for (int j = 1; j < m_nRow; j += 2)
			{
				DrawTile(hdc
					, m_vecTiles[j][i]
					, camera
					);
				
				for (int k = 0; k < (int)unit.size(); ++k)
				{
					if (unit[k]->CheckIsAttackableTile(INDEX{ j, i, 0})
						&& unit[k]->GetUnitTeam() != UnitTeam::West)
					{
						unit[k]->DrawAttackableTile(hdc, INDEX{ j,i ,0}, camera);
						break;
					}
				}
				for (int k = 0; k < (int)unit.size(); ++k)
				{
					if (unit[k]->GetCurrentIndex().x == j
						&& unit[k]->GetCurrentIndex().y == i)
					{
						unit[k]->OnDraw(hdc, camera);
						break;
					}
				}
			}
		}
	}
	else if (divison == 3)
	{
		for (int i = 0; i < m_nColumn; ++i)
		{
			for (int j = 0; j < m_nRow; j += 2)
			{
				DrawTile(hdc
					, m_vecTiles[j][i]
					, camera
					);
				for (int k = 0; k < (int)unit.size(); ++k)
				{
					if (unit[k]->CheckIsSkillTile(INDEX{ j, i , 0 })
						&& unit[k]->GetUnitTeam() != UnitTeam::West)
					{
						//unit[k]->DrawAttackableTile(hdc, INDEX{ j,i , 0 }, camera);
						//break;
						CSystemImage::GetInstance()->DrawTile(hdc, m_vecTiles[j][i]->GetTilePos(), 1, camera);
					}
				}
				for (int k = 0; k < (int)unit.size(); ++k)
				{
					if (unit[k]->GetCurrentIndex().x == j
						&& unit[k]->GetCurrentIndex().y == i)
					{
						unit[k]->OnDraw(hdc, camera);
						break;
					}
				}
			}

			for (int j = 1; j < m_nRow; j += 2)
			{
				DrawTile(hdc
					, m_vecTiles[j][i]
					, camera
					);

				for (int k = 0; k < (int)unit.size(); ++k)
				{
					if (unit[k]->CheckIsSkillTile(INDEX{ j, i, 0 })
						&& unit[k]->GetUnitTeam() != UnitTeam::West)
					{
						CSystemImage::GetInstance()->DrawTile(hdc, m_vecTiles[j][i]->GetTilePos(), 1, camera);
						break;
					}
				}
				for (int k = 0; k < (int)unit.size(); ++k)
				{
					if (unit[k]->GetCurrentIndex().x == j
						&& unit[k]->GetCurrentIndex().y == i)
					{
						unit[k]->OnDraw(hdc, camera);
						break;
					}
				}
			}
		}
	}
}
#pragma endregion