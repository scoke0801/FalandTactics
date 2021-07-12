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
			//return index1.x < index2.x;
			return false;
		else
			//return index1.x > index2.x;
			return true;
	}
	else
	{
		if (y <= index.y)
			//return index1.y < index2.y;
			return false;
		else
			//return index1.y > index2.y;
			return true;
	}
	return false;
}
bool operator<(CIndex index1, CIndex index2)
{
	if (index1.y == index2.y)
	{
		if (index1.x <= index2.x)
			//return index1.x < index2.x;
			return false;
		else
			//return index1.x > index2.x;
			return true;
	}
	else
	{
		if (index1.y <= index2.y)
			//return index1.y < index2.y;
			return false;
		else
			//return index1.y > index2.y;
			return true;
	}
	return false;
}
//bool CIndex::operator=(CIndex index)
//{
//	x = index.x;
//	y = index.y;
//	height = index.height;
//
//	return true;
//}
CIndex::CIndex(int x, int y, int height)
{
	this->x = x;
	this->y = y;
	height = height;
}

int CIndex::GetXPos() const			//�ε������� ���� ������
{
	return TILE_WIDTH * x / 2;
}
int CIndex::GetYPos() const
{
	return TILE_HEIGHT / 2 * (x % 2) + TILE_HEIGHT * y
		- TILE_HEIGHT_HALF * height;
}

CIndex CIndex::GetIndex()			//�������� �ε��� ������
{
	INDEX returnValue;

	returnValue.x = x / TILE_WIDTH_HALF;
	returnValue.y = y + TILE_HEIGHT_HALF * height;
	returnValue.y = (returnValue.y - (returnValue.x % 2) * TILE_HEIGHT_HALF) / TILE_HEIGHT;
	//TILE_HEIGHT / 2 * (i % 2) + TILE_HEIGHT * j
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