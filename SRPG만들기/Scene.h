#pragma once
#include "FrameWork.h"
#include "enum.h"
#include "Camera.h"

class CMap;
class CUnit;
class CScene
{
public:
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

	//메시지 처리를 합니다.
	virtual BOOL OnProcessingKeyboardMessage(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
	virtual BOOL OnProcessingMouseMessage(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
	virtual BOOL OnProcessingWindowMessage(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

	virtual CurrentScene GetCurrentScene() { return CurrentScene::None; }


public: //getter setter
	void SetPhase(NoticePhase phase);
	NoticePhase GetPhase() const { return m_phase; }

	void SetCommandSelecting(BOOL value) { m_bCommandSelecting = value; }
	BOOL GetCommandSelecting() const { return m_bCommandSelecting; }

	CMap* GetMap() const { return m_map; }

	void SetCurrentUnit(CUnit* unit) { m_pCurUnit = unit; }
	CUnit* GetCurrentUnit() const { return m_pCurUnit; }

public:
	void NewTurn();

	void SortUnitArrayUp();		//unit배열을 위치값이 위인 유닛 순으로 정렬합니다.

	void SortUnitArrayDown();	//unit배열을 위치값이 아래인 유닛 순으로 정렬합니다.

	BOOL ExecuteEnemyAct();

	int CalculateEnemyNum();
	int CalculateAllyNum();

public:
	virtual BOOL CheckGameLose();	//기본적으로 모든 아군 유닛이 죽으면 게임을 진 것으로 합니다.
									//다른 게임 패배 조건이 있는 맵에서는 새롭게 정의가 필요합니다.
	virtual BOOL CheckGameWin();	//기본적으로 모든 적군 유닛이 죽으면 게임을 이긴 것으로 합니다.
									//다른 게임 승리 조건이 있는 맵에서는 새롭게 정의가 필요합니다.
	virtual void CreateButton() {}

public: //스테이지 전환 시 달성한 업적이 있는지 확인합니다.
	void CheckAchievement();
protected:			//CScene클래스와 이 클래스를 상속받는 클래스에서만 접근가능합니다.
	CFrameWork* m_pFrameWork;	//장면 변경을 위해, framework를 멤버 변수로 포함합니다.
	
	HWND m_hWnd;				//장면이 변경된 경우 화면 갱신시키기 위한 변수입니다.

	RECT m_rcApp;				//응용 프로그램의 크기를 나타낼 변수입니다.

protected:
//유닛
	std::vector <CUnit*> m_vecUnits;
	std::vector <CUnit*>::iterator m_iterUnit;
	CUnit* m_pCurUnit;
	short m_nUnitNum;		//맵 생성시의 유닛 수
//기타
	int m_nTurnCount;

	Camera camera;			//화면에 출력할 부분을 결정할 부분을 지정합니다.

	BOOL m_bLeftClick;		//LBUTTONCLICK message가 발생했는지를 나타냅니다.
	POINT m_ptMouseStart;	//마우스로 클릭한 첫 지점의 좌표를 나타냅니다.
	POINT m_ptMouseEnd;		//마우스로 클릭한 끝 지점의 좌표를 나타냅니다.

	BOOL m_bCommandSelecting;	//UI를 통한 행동 선택이 진행중인지를 나타낼 변수입니다
	NoticePhase m_phase;		//유닛이 진행중인 행동에 대한 정보를 가질 변수입니다.

	char m_chCount;				//		
	short m_nAlpha;
//맵
	CMap* m_map;
	CurrentScene m_tag;
	CImage m_backgoundImg;
};