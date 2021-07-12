/*
맵에 그려지는 각각의 타일 클래스,
타일의 집합을 관리하는 맵 클래스를 정의한 클래스입니다.
*/

#pragma once
#include "Unit.h"

class CTile
{
public:
	enum class TileType : int
	{
		PLAIN = 0
		, HILL
	};
	
public:
	CTile(TileType tag, int cx = 0, int cy = 0 , int xPos = 0, int yPos = 0);
	CTile(LPCTSTR szPath);	////파일의 위치를 받아와 맵의 내용을 불러오도록 합니다.
	
	virtual ~CTile();
	
	void MakeUptile(int yPos = 0);
	
	void DrawSystemTile(HDC hdc, int kind, Camera camera = { 0, });
//get
	int GetX() const { return m_iCx; }
	int GetY() const { return m_iCy; }
	INDEX GetTilePos();
	INDEX GetTileIndex();

	int GetImageX() const { return m_nImageCx; }
	int GetImageY() const { return m_nImageCy; }
	
	int GetHeight()	const { return m_iHeight; }
	
	CTile* GetUpTile() const { return m_upTile; }

	BOOL GetIsUsable() const; 
	BOOL GetIsObstacle() const { return m_bIsObstacle; }
	INDEX GetContiguousTile(int xIndex, int yIndex, ContiguousTile contiguous_tile);
	TileType GetTileType() const { return m_tag; }
	CUnit* GetUnit() const { return m_pUnit; }

	BOOL CheckEnemy(CUnit* unit) const;
	
//set
	void SetX(int cx) { m_iCx = cx; }
	void SetY(int cy)  { m_iCy = cy; }
	void SetUnit(CUnit* unit);
	void SetIsUsalbe(BOOL isUsable) { m_bIsUsable = isUsable; }
	void SetIsObstacle(BOOL isOb) { m_bIsObstacle = isOb; }
	void SetHeight(int height) { m_iHeight = height; }
	void SetImagePos(int xPos, int yPos);		//이미지에서 사용할 위치를 지정합니다.

private:
	int m_iCx;				//클라이언트에서 타일의 위치를 표시합니다.
	int m_iCy;

	int m_nImageCx;			//이미지 파일에서의 타일의 위치를 표시합니다.
	int m_nImageCy;				

	int m_iHeight;			//타일의 높이 값을 나타냅니다.

	TileType m_tag;			//현재 타일이 어떤 타입인지 표시합니다.
	BOOL m_bIsObstacle;		//현재 타일이 장애물인지를 표시합니다.
	BOOL m_bIsUsable;		//현재 타일이 사용가능한 타일인지를 표시합니다.
	CTile* m_upTile;		//언덕 타일을 위한 변수입니다.
	//CSystemImage* SystemTile;
	
	CUnit* m_pUnit;			//타일에 위치한 유닛을 가르킵니다.
};

class CMap
{
public:
	CMap(int mapSize);
	CMap(LPCTSTR szPath);	//파일의 위치를 받아와 맵의 내용을 불러오도록 합니다.
	~CMap();

//맵 생성 관련
	void LoadTileImage(LPCTSTR szPath);	//타일의 이미지 파일을 불러옵니다.
	void MakeMap();						//전달받은 정보로 맵을 생성합니다., 랜덤 맵
	void MakeMap(LPCTSTR szPath);		//전달받은 정보로 맵을 생성합니다.
	void LoadUnit(LPCTSTR szPath, std::vector <CUnit*> *vecUnits);		//전달받은 정보로 유닛정보를 불러옵니다.

//그리기 관련
	void DrawMap(HDC hdc, int division = 1, Camera camera = { 0, });				//생성한 맵을 그립니다.
										//void DrawMapByHeight(HDC hdc, int height);  
	void OnDraw(HDC hdc, std::vector <CUnit*>unit, int divison, Camera camera = { 0, });

	void DrawTile(HDC hdc, CTile* tile, int cy, Camera camera =  {0,});
	void DrawTile(HDC hdc, CTile* tile, Camera camera = { 0, });

	void DrawHill(HDC hdc, CTile* tile, Camera camera = { 0, });

//인접 타일 생성 관련
	void AddContiguousTile(std::map <INDEX, Node*> *map, INDEX idx, Node* parent);	
	//주변 타일을 추가합니다(이전 타일과의 연결을 통해 이동가능 타일을 생성합니다.)
	void AddContiguousTile(CUnit* unit,std::map <INDEX, CTile*> *map, INDEX idx);
	//주변 타일을 추가합니다(4방향의 타일을 모두 추가합니다.)
	void AddLineTile(CUnit* unit, std::map <INDEX, CTile* > *map, INDEX idx, UnitWay way, int range);
	//주변 타일을 추가합니다.(인자로 전달받은 방향의 타일을 추가합니다.

	BOOL CheckContiguousEnemy(INDEX idx);
	//인접한 적 유닛을 탐색합니다.
	BOOL CheckContiguousEnemy(CUnit* unit,INDEX idx);
	//인접한 적 유닛을 탐색합니다.

	std::vector< std::vector<CTile*> > GetTileArray();
	//클래스 멤버변수 m_vecTile을 반환합니다.

	INDEX CheckPath(CUnit* unit,INDEX start, INDEX end, int moveRange);			
	//인자로 받은 값까지의 경로를 탐색합니다.
	void CheckPath(std::map <INDEX, Node*> *map, INDEX idx, Node* Parent);
	//인자로 받은 값까지의 경로를 탐색합니다.

//Get
	INDEX GetTilePos(int index_i, int index_j);	//인덱스를 입력받으면 해당 인덱스의 배열 값을 반환
	
	POINT GetTilePos(POINT mouseValue, CIndex *idx, Camera camera = { 0, });
	//값을 입력받으면 해당값이 배열에 존재하는 지를 판단
	//존재하는 경우 : 해당 배열의 위치 값을 반환, 인자로 전달받은 index의 값을 할당
	//존재하지 않는 경우 : 음수값을 반환									

	CUnit* GetUnitOnTile(INDEX idx); // 해당 위치에 유닛이 있다면 반환합니다.

	int GetHeight(INDEX idx);

	int GetColumn() const { return m_nColumn; }

	int GetRow() const { return m_nRow; }

//Set
	void SetTileIsUsable(INDEX idx, BOOL inputValue);
	void SetUnitOnTile(INDEX idx, CUnit* unit);

public:
//탐색 및 계산 기능
	// 이동가능한 타일인지 확인합니다.
	void CheckMovableTile(CUnit* unit);

	// 스킬 범위 안의 타일인지 확인합니다.
	void CheckSkillTile(CUnit* unit, INDEX idx, int skillRange, SkillAttackType type);
	void CheckSkillTile(CUnit* unit, INDEX idx, SKillName skill);

	// 두 타일 사이의 높이 차이를 계산합니다.
	BOOL CheckHeightDifference(INDEX idx1, INDEX idx2);
	
	// 객체가 위치해 있지 않은 타일인지 확인합니다.
	BOOL CheckIsUsableTile(INDEX idx);
	
	// 장애물이 있는 타일인지 확인합니다.
	BOOL CheckIsObstacle(INDEX idx);
	
	// 마우스로 클릭한 좌표가 정상 좌표의 타일인지 확인합니다.
	BOOL IsInTile(CTile* tile, POINT inputPos, Camera camera = { 0, });

	// 거리 계산함수
	double CalculateDistance(double gradient, POINT pointA, POINT inputPos);
	
	BOOL CalculateEnemyAct(CUnit* unit, std::vector <CUnit*> vecUnits);

private:	
	std::vector< std::vector<CTile*> > m_vecTiles;	//vector를 이용해 2차원 동적 배열을 만듭니다.
	int m_nColumn;		//가로 행의 크기를 나타냅니다.
	int m_nRow;			//세로 행의 크기를 나타냅니다.

private:
	CImage m_tileImage;
};
