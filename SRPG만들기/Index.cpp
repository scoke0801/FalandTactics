#include "stdafx.h"
#include "Index.h"

CIndex::operator POINT const()
{
	POINT pt = { this->x, this->y };
	height = 0;
	return pt;
}
bool CIndex::operator<(CIndex index)
{
	if (y == index.y)
	{
		if (x <= x)
			return false;
		else
			return true;
	}
	else
	{
		if (y <= index.y)
			return false;
		else
			return true;
	}
	return false;
}
bool operator<(CIndex index1, CIndex index2)
{
	if (index1.y == index2.y)
	{
		if (index1.x <= index2.x)
			return false;
		else
			return true;
	}
	else
	{
		if (index1.y <= index2.y)
			return false;
		else
			return true;
	}
	return false;
}
CIndex::CIndex(int x, int y, int height)
{
	this->x = x;
	this->y = y;
	height = height;
}

int CIndex::GetXPos() const			//인덱스값을 실제 값으로
{
	return TILE_WIDTH * x / 2;
}
int CIndex::GetYPos() const
{
	return TILE_HEIGHT / 2 * (x % 2) + TILE_HEIGHT * y
		- TILE_HEIGHT_HALF * height;
}

CIndex CIndex::GetIndex()			//실제값을 인덱스 값으로
{
	INDEX returnValue;

	returnValue.x = x / TILE_WIDTH_HALF;
	returnValue.y = y + TILE_HEIGHT_HALF * height;
	returnValue.y = (returnValue.y - (returnValue.x % 2) * TILE_HEIGHT_HALF) / TILE_HEIGHT; 
	return returnValue;
}
void CIndex::SetXIndex()
{

}
void CIndex::SetYIndex()
{

}

BOOL CIndex::CheckInRange(int mapSize)
{
	if (mapSize == 1)
	{
		if (x < 0 || x >= 30)
			return FALSE;
		if (y < 0 || y >= 20)
			return FALSE;
	}
	return TRUE;
}
BOOL CIndex::CheckInRange(int row, int column)
{
	if (x < 0 || x >= column)
		return FALSE;
	if (y < 0 || y >= row)
		return FALSE;
	return TRUE;
}