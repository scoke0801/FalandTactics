#include "stdafx.h"
#include "Rhombus.h"

CRhombus::CRhombus(INDEX index,POINT pos, int height)
{
	m_idxIndex = index;

	m_ptLeftTop = pos;
	//m_ptLeftTop.x = TILE_WIDTH * m_idxIndex.x / 2;
	//m_ptLeftTop.y = TILE_HEIGHT / 2 * (m_idxIndex.x % 2) + TILE_HEIGHT * m_idxIndex.y;
	//	//- TILE_HEIGHT_HALF * height;
	
	m_nHeight = height;
	/*
	, TILE_WIDTH * i / 2
					, TILE_HEIGHT / 2 * (i % 2) + TILE_HEIGHT * j
					*/
}

void CRhombus::Draw(HDC hdc, Camera camera)
{
	static CImage image;
	static BOOL first = FALSE;

	if (!first)
	{
		image.Load(_T("resource/tile/system_tile.bmp"));
		first = TRUE;
	}
	image.TransparentBlt(hdc
		, m_ptLeftTop.x + camera.viewPoint.x
		, m_ptLeftTop.y + camera.viewPoint.y 
		, TILE_WIDTH, TILE_HEIGHT
		, 0, 0, TILE_WIDTH, TILE_HEIGHT, RGB(255, 0, 255)
		);
}

Node::Node(INDEX idx, POINT pos, int height,  Node* parent)
	:CRhombus(idx,pos, height)
{
	//rhombus = new CRhombus(idx);
	if (parent != NULL)
	{
		link = parent;
		//CalculateRate();
		return;
	}
	link = NULL;
	//m_nHeight = height;
}

Node::~Node()
{
	//delete(rhombus);
}
//void Node::Draw(HDC hdc)
//{
//	//rhombus->Draw(hdc);
//}
void Node::CalculateRate()
{
	INDEX idx = link->GetIndex();
}