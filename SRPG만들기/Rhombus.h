#pragma once

/*
������ �� ������ �����Ͽ� ��üȭ�մϴ�.

Tile���� ���� ������ ���� CRhombus��ü�� ����
ĳ������ �̵� ���� ������ ǥ���մϴ�.
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