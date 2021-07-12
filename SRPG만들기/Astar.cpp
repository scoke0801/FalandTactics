#include "stdafx.h"
#include "Astar.h"

//CAstar::CAstar(INDEX start, INDEX end)
//{
//	m_listOpen = new FindingPath::List;
//	m_listClose = new FindingPath::List;
//
//	m_idxStart = start;
//	m_idxStart = end;
//}
//CAstar::~CAstar()
//{
//	FreeList();
//}
//
//void CAstar::AddOpneList(FindingPath::Node* parent, CTile* tile)
//{
//	FindingPath::Node* newNode;
//	AddList(parent, tile);
//
//}
//void CAstar::AddCloseList(FindingPath::Node* parent, CTile* tile)
//{
//
//}
//void CAstar::AddList(FindingPath::Node* parent, CTile* tile)
//{
//	FindingPath::Node* newNode;
//	FindingPath::Node* tempNode;
//
//	if (parent == NULL)
//		return;
//
//	newNode = new FindingPath::Node;
//
//	INDEX idx = tile->GetTileIndex();
//	
//	newNode->index = idx;
//	SetNodeValue(newNode);
//	newNode->link = parent; 
//}
//
////검색
//BOOL CAstar::FindOnOpenList(CTile* tile)
//{
//	return FALSE;
//}
//BOOL CAstar::FindOnCloseList(CTile* tile)
//{
//	return FALSE;
//}
//BOOL CAstar::FindOnList(CTile* tile)
//{
//	return FALSE;
//}
//
////삭제
//void CAstar::DeleteOpenList(FindingPath::Node* deleteNode)
//{
//
//}
//void CAstar::DeleteCloseList(FindingPath::Node* deleteNode)
//{
//
//}
//void CAstar::DeleteList(FindingPath::Node* deleteNode)
//{
//
//}
//
////메모리 반환
//void CAstar::FreeList()
//{
//
//}
//
////노드 값 설정
//void CAstar::SetNodeValue(FindingPath::Node* node)
//{
//	node->G;
//	node->H;
//
//	node->F = node->G + node->H;
//}
//
//BOOL FindFath(CTile start, CTile end)
//{
//	using namespace FindingPath;
//	
//	/*List openList;
//	List closeList;*/
//
//	/*AddList(openList, start);
//	while (isEmpty(openList))
//	{
//		if (AddContiguousTile(openList, curTile, end))
//		{
//			break;
//		}
//		AddClosedList(closeList, curTile);
//		DeleteNode(openList, curTIle);
//	}*/
//	return FALSE;
//}