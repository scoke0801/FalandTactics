#pragma once

/*
길찾기 알고리즘(A*)와 
관련된 내용들을 객체화 합니다.

map 자료구조를 통한 별도의 로직으로 길 찾기를 수행하도록 구현되어있고
이에 따라 현재 사용하지 않는 코드 입니다.
*/
#include "Tile.h"

//namespace FindingPath
//{
//	typedef struct _node
//	{
//		INDEX index;//배열에 저장된 타일의 인덱스를 나타냅니다.
//		int G;	//시작점 (A)으로 부터 새로운 사각형까지의 이동비용입니다.
//		int F;	//비용 (F = G + H)
//		int H;	//얻어진 사각형으로부터 최종목적지점 (B)까지의 이동비용입니다.
//
//		_node* link;		//이전 노드를 가르키기 위한 포인터입니다.
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
//	//추가
//	void AddOpneList(FindingPath::Node* parent, CTile* tile);	//OpenList에 node를 추가합니다.
//
//	void AddCloseList(FindingPath::Node* parent, CTile* tile);	//CloseList에 node를 추가합니다.
//												
//	void AddList(FindingPath::Node* parent, CTile* tile);
//	
//	//검색
//	BOOL FindOnOpenList(CTile* tile);
//
//	BOOL FindOnCloseList(CTile* tile);
//
//	BOOL FindOnList(CTile* tile);
//
//	//삭제
//	void DeleteOpenList(FindingPath::Node* deleteNode);
//
//	void DeleteCloseList(FindingPath::Node* deleteNode);
//
//	void DeleteList(FindingPath::Node* deleteNode);
//
//	//메모리 반환
//	void FreeList();
//
//	//노드 값 설정
//	void SetNodeValue(FindingPath::Node* node);
//
//	//정렬
//	void SortList();
//
//	//길찾기
//	BOOL FindFath(CTile start, CTile end);
//private:
//	FindingPath::List* m_listOpen;
//	FindingPath::List* m_listClose;
//
//	INDEX m_idxStart;
//	INDEX m_idxEnd;
//};