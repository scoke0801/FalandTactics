/*
�ʿ� �׷����� ������ Ÿ�� Ŭ����,
Ÿ���� ������ �����ϴ� �� Ŭ������ ������ Ŭ�����Դϴ�.
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
	CTile(LPCTSTR szPath);	////������ ��ġ�� �޾ƿ� ���� ������ �ҷ������� �մϴ�.
	
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
	void SetImagePos(int xPos, int yPos);		//�̹������� ����� ��ġ�� �����մϴ�.

private:
	int m_iCx;				//Ŭ���̾�Ʈ���� Ÿ���� ��ġ�� ǥ���մϴ�.
	int m_iCy;

	int m_nImageCx;			//�̹��� ���Ͽ����� Ÿ���� ��ġ�� ǥ���մϴ�.
	int m_nImageCy;				

	int m_iHeight;			//Ÿ���� ���� ���� ��Ÿ���ϴ�.

	TileType m_tag;			//���� Ÿ���� � Ÿ������ ǥ���մϴ�.
	BOOL m_bIsObstacle;		//���� Ÿ���� ��ֹ������� ǥ���մϴ�.
	BOOL m_bIsUsable;		//���� Ÿ���� ��밡���� Ÿ�������� ǥ���մϴ�.
	CTile* m_upTile;		//��� Ÿ���� ���� �����Դϴ�.
	//CSystemImage* SystemTile;
	
	CUnit* m_pUnit;			//Ÿ�Ͽ� ��ġ�� ������ ����ŵ�ϴ�.
};

class CMap
{
public:
	CMap(int mapSize);
	CMap(LPCTSTR szPath);	//������ ��ġ�� �޾ƿ� ���� ������ �ҷ������� �մϴ�.
	~CMap();

//�� ���� ����
	void LoadTileImage(LPCTSTR szPath);	//Ÿ���� �̹��� ������ �ҷ��ɴϴ�.
	void MakeMap();						//���޹��� ������ ���� �����մϴ�., ���� ��
	void MakeMap(LPCTSTR szPath);		//���޹��� ������ ���� �����մϴ�.
	void LoadUnit(LPCTSTR szPath, std::vector <CUnit*> *vecUnits);		//���޹��� ������ ���������� �ҷ��ɴϴ�.

//�׸��� ����
	void DrawMap(HDC hdc, int division = 1, Camera camera = { 0, });				//������ ���� �׸��ϴ�.
										//void DrawMapByHeight(HDC hdc, int height);  
	void OnDraw(HDC hdc, std::vector <CUnit*>unit, int divison, Camera camera = { 0, });

	void DrawTile(HDC hdc, CTile* tile, int cy, Camera camera =  {0,});
	void DrawTile(HDC hdc, CTile* tile, Camera camera = { 0, });

	void DrawHill(HDC hdc, CTile* tile, Camera camera = { 0, });

//���� Ÿ�� ���� ����
	void AddContiguousTile(std::map <INDEX, Node*> *map, INDEX idx, Node* parent);	
	//�ֺ� Ÿ���� �߰��մϴ�(���� Ÿ�ϰ��� ������ ���� �̵����� Ÿ���� �����մϴ�.)
	void AddContiguousTile(CUnit* unit,std::map <INDEX, CTile*> *map, INDEX idx);
	//�ֺ� Ÿ���� �߰��մϴ�(4������ Ÿ���� ��� �߰��մϴ�.)
	void AddLineTile(CUnit* unit, std::map <INDEX, CTile* > *map, INDEX idx, UnitWay way, int range);
	//�ֺ� Ÿ���� �߰��մϴ�.(���ڷ� ���޹��� ������ Ÿ���� �߰��մϴ�.

	BOOL CheckContiguousEnemy(INDEX idx);
	//������ �� ������ Ž���մϴ�.
	BOOL CheckContiguousEnemy(CUnit* unit,INDEX idx);
	//������ �� ������ Ž���մϴ�.

	std::vector< std::vector<CTile*> > GetTileArray();
	//Ŭ���� ������� m_vecTile�� ��ȯ�մϴ�.

	INDEX CheckPath(CUnit* unit,INDEX start, INDEX end, int moveRange);			
	//���ڷ� ���� �������� ��θ� Ž���մϴ�.
	void CheckPath(std::map <INDEX, Node*> *map, INDEX idx, Node* Parent);
	//���ڷ� ���� �������� ��θ� Ž���մϴ�.

//Get
	INDEX GetTilePos(int index_i, int index_j);	//�ε����� �Է¹����� �ش� �ε����� �迭 ���� ��ȯ
	
	POINT GetTilePos(POINT mouseValue, CIndex *idx, Camera camera = { 0, });
	//���� �Է¹����� �ش簪�� �迭�� �����ϴ� ���� �Ǵ�
	//�����ϴ� ��� : �ش� �迭�� ��ġ ���� ��ȯ, ���ڷ� ���޹��� index�� ���� �Ҵ�
	//�������� �ʴ� ��� : �������� ��ȯ									

	CUnit* GetUnitOnTile(INDEX idx); // �ش� ��ġ�� ������ �ִٸ� ��ȯ�մϴ�.

	int GetHeight(INDEX idx);

	int GetColumn() const { return m_nColumn; }

	int GetRow() const { return m_nRow; }

//Set
	void SetTileIsUsable(INDEX idx, BOOL inputValue);
	void SetUnitOnTile(INDEX idx, CUnit* unit);

public:
//Ž�� �� ��� ���
	// �̵������� Ÿ������ Ȯ���մϴ�.
	void CheckMovableTile(CUnit* unit);

	// ��ų ���� ���� Ÿ������ Ȯ���մϴ�.
	void CheckSkillTile(CUnit* unit, INDEX idx, int skillRange, SkillAttackType type);
	void CheckSkillTile(CUnit* unit, INDEX idx, SKillName skill);

	// �� Ÿ�� ������ ���� ���̸� ����մϴ�.
	BOOL CheckHeightDifference(INDEX idx1, INDEX idx2);
	
	// ��ü�� ��ġ�� ���� ���� Ÿ������ Ȯ���մϴ�.
	BOOL CheckIsUsableTile(INDEX idx);
	
	// ��ֹ��� �ִ� Ÿ������ Ȯ���մϴ�.
	BOOL CheckIsObstacle(INDEX idx);
	
	// ���콺�� Ŭ���� ��ǥ�� ���� ��ǥ�� Ÿ������ Ȯ���մϴ�.
	BOOL IsInTile(CTile* tile, POINT inputPos, Camera camera = { 0, });

	// �Ÿ� ����Լ�
	double CalculateDistance(double gradient, POINT pointA, POINT inputPos);
	
	BOOL CalculateEnemyAct(CUnit* unit, std::vector <CUnit*> vecUnits);

private:	
	std::vector< std::vector<CTile*> > m_vecTiles;	//vector�� �̿��� 2���� ���� �迭�� ����ϴ�.
	int m_nColumn;		//���� ���� ũ�⸦ ��Ÿ���ϴ�.
	int m_nRow;			//���� ���� ũ�⸦ ��Ÿ���ϴ�.

private:
	CImage m_tileImage;
};
