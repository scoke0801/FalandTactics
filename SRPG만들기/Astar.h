#pragma once

/*
��ã�� �˰���(A*)�� 
���õ� ������� ��üȭ �մϴ�.
*/
#include "Tile.h"

//namespace FindingPath
//{
//	typedef struct _node
//	{
//		INDEX index;//�迭�� ����� Ÿ���� �ε����� ��Ÿ���ϴ�.
//		int G;	//������ (A)���� ���� ���ο� �簢�������� �̵�����Դϴ�.
//		int F;	//��� (F = G + H)
//		int H;	//����� �簢�����κ��� ������������ (B)������ �̵�����Դϴ�.
//
//		_node* link;		//���� ��带 ����Ű�� ���� �������Դϴ�.
//	}Node;
//
//	typedef struct _list
//	{
//		Node* head;
//	}List;
//}
//class CAstar
//{
//	
//public:
//	CAstar(INDEX start, INDEX end);
//	~CAstar();
//public:
//	//�߰�
//	void AddOpneList(FindingPath::Node* parent, CTile* tile);	//OpenList�� node�� �߰��մϴ�.
//
//	void AddCloseList(FindingPath::Node* parent, CTile* tile);	//CloseList�� node�� �߰��մϴ�.
//												
//	void AddList(FindingPath::Node* parent, CTile* tile);
//	
//	//�˻�
//	BOOL FindOnOpenList(CTile* tile);
//
//	BOOL FindOnCloseList(CTile* tile);
//
//	BOOL FindOnList(CTile* tile);
//
//	//����
//	void DeleteOpenList(FindingPath::Node* deleteNode);
//
//	void DeleteCloseList(FindingPath::Node* deleteNode);
//
//	void DeleteList(FindingPath::Node* deleteNode);
//
//	//�޸� ��ȯ
//	void FreeList();
//
//	//��� �� ����
//	void SetNodeValue(FindingPath::Node* node);
//
//	//����
//	void SortList();
//
//	//��ã��
//	BOOL FindFath(CTile start, CTile end);
//private:
//	FindingPath::List* m_listOpen;
//	FindingPath::List* m_listClose;
//
//	INDEX m_idxStart;
//	INDEX m_idxEnd;
//};