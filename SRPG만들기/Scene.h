#pragma once
#include "FrameWork.h"
#include "enum.h"
#include "Camera.h"

class CMap;
class CUnit;
class CScene
{
public:
	// ��� ���� ����
	enum class CurrentScene : int {
		None = 0
		, Select
		, Stage1
		, Stage2
		, Stage3
		, Stage4
		, Stage5
		, Stage6
		, Title
		, UserStage
		, StageClear
		, GameWin
		, GameLose
		, ScoreTable	
	};
public:
	CScene();
	CScene(CFrameWork* framework, HWND hWnd);
	virtual ~CScene();

	virtual void OnUpdate(float timeElapsed) = 0;
	virtual void OnDraw(HDC hdc) = 0;

	virtual void PlaySound();

	//�޽��� ó���� �մϴ�.
	virtual BOOL OnProcessingKeyboardMessage(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
	virtual BOOL OnProcessingMouseMessage(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
	virtual BOOL OnProcessingWindowMessage(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

	virtual CurrentScene GetCurrentScene() { return CurrentScene::None; }
	 
public: 
//getter setter
	void SetPhase(NoticePhase phase);
	NoticePhase GetPhase() const { return m_phase; }

	void SetCommandSelecting(BOOL value) { m_bCommandSelecting = value; }
	BOOL GetCommandSelecting() const { return m_bCommandSelecting; }

	CMap* GetMap() const { return m_map; }

	void SetCurrentUnit(CUnit* unit) { m_pCurUnit = unit; }
	CUnit* GetCurrentUnit() const { return m_pCurUnit; }

public:
	void NewTurn();				// �� ���Ӱ� ����, ���� ��ü���� �� �Ͽ� ���� �ൿ�� �� �ֵ��� �� ����

	void SortUnitArrayUp();		//unit�迭�� ��ġ���� ���� ���� ������ �����մϴ�.

	void SortUnitArrayDown();	//unit�迭�� ��ġ���� �Ʒ��� ���� ������ �����մϴ�.

	BOOL ExecuteEnemyAct();		// ���� �ൿ

	int CalculateEnemyNum();	// �����ִ� ������ �� ���
	int CalculateAllyNum();		// �����ִ� �Ʊ��� �� ���

public:
// �¸� / �й����� ó���� ���� �Լ�
	virtual BOOL CheckGameLose();	//�⺻������ ��� �Ʊ� ������ ������ ������ �� ������ �մϴ�.
									//�ٸ� ���� �й� ������ �ִ� �ʿ����� ���Ӱ� ���ǰ� �ʿ��մϴ�.

	virtual BOOL CheckGameWin();	//�⺻������ ��� ���� ������ ������ ������ �̱� ������ �մϴ�.
									//�ٸ� ���� �¸� ������ �ִ� �ʿ����� ���Ӱ� ���ǰ� �ʿ��մϴ�.
	virtual void CreateButton() {}

public: //�������� ��ȯ �� �޼��� ������ �ִ��� Ȯ���մϴ�.
	void CheckAchievement();

protected:			
//CSceneŬ������ �� Ŭ������ ��ӹ޴� Ŭ���������� ���ٰ����մϴ�.
	CFrameWork* m_pFrameWork;	//��� ������ ����, framework�� ��� ������ �����մϴ�.
	
	HWND m_hWnd;				//����� ����� ��� ȭ�� ���Ž�Ű�� ���� �����Դϴ�.

	RECT m_rcApp;				//���� ���α׷��� ũ�⸦ ��Ÿ�� �����Դϴ�.

protected:
//����
	std::vector <CUnit*> m_vecUnits;
	std::vector <CUnit*>::iterator m_iterUnit;
	CUnit* m_pCurUnit;
	short m_nUnitNum;		//�� �������� ���� ��

//��Ÿ
	int m_nTurnCount;

	Camera camera;			//ȭ�鿡 ����� �κ��� ������ �κ��� �����մϴ�.

	BOOL m_bLeftClick;		//LBUTTONCLICK message�� �߻��ߴ����� ��Ÿ���ϴ�.
	POINT m_ptMouseStart;	//���콺�� Ŭ���� ù ������ ��ǥ�� ��Ÿ���ϴ�.
	POINT m_ptMouseEnd;		//���콺�� Ŭ���� �� ������ ��ǥ�� ��Ÿ���ϴ�.

	BOOL m_bCommandSelecting;	//UI�� ���� �ൿ ������ ������������ ��Ÿ�� �����Դϴ�
	NoticePhase m_phase;		//������ �������� �ൿ�� ���� ������ ���� �����Դϴ�.

	char m_chCount;				//		
	short m_nAlpha;

//��
	CMap* m_map;
	CurrentScene m_tag;
};