#pragma once

/*
마름모 꼴 도형과 관련하여 객체화합니다.

Tile에서 받은 정보를 토대로 CRhombus객체를 만들어서
캐릭터의 이동 가능 범위를 표시합니다.
*/

class CRhombus
{
public:
	CRhombus(INDEX index, POINT pos, int height = 0);
	
	virtual void Draw(HDC hdc, Camera camera = { 0, });
	INDEX GetIndex() { return m_idxIndex; }
	POINT GetLeftTop() { return m_ptLeftTop; }

	void SetHeight(int height) { m_nHeight; }
protected:
	POINT m_ptLeftTop;
	INDEX m_idxIndex;
	
	int m_nHeight;
};

class Node : public CRhombus
{
public:
	Node(INDEX idx, POINT pos,int height = 0, Node* parent = NULL);
	~Node();

	void CalculateRate();
	//void Draw(HDC hdc);
public:
	//CRhombus* rhombus;
	//cint rate;
	Node* link;
};