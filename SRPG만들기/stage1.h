#pragma once

class CUnit;
class CMap;

class CStage1 : public CScene
{	
public:
	CStage1(CFrameWork * framework, HWND hWnd, CurrentScene tag);
	~CStage1();

	virtual void OnUpdate(float timeElapsed);
	virtual void OnDraw(HDC hdc);

	virtual void PlaySound();

	// 장면 전환 시, 점차 투명하게 변경하기 위하여 사용한 함수
	void DrawIntervalScene(HDC hdc);

	//메시지 처리를 합니다.
	virtual BOOL OnProcessingKeyboardMessage(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
	virtual BOOL OnProcessingMouseMessage(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
	//virtual BOOL OnProcessingWindowMessage(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

	virtual CurrentScene GetCurrentScene() { return CurrentScene::Stage1; }

private: 
//UI
	CUI_UnitInfo* UI_UnitInfo;
	CUI_CommandSelect* UI_CommandSelect;
	CUI_Notice* UI_Notice;
};