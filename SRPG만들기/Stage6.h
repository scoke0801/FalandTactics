#pragma once


class CUnit;
class CMap;

class CStage6 : public CScene
{
public:
	CStage6(CFrameWork * framework, HWND hWnd, CurrentScene tag);
	~CStage6();

	virtual void OnUpdate(float timeElapsed);
	virtual void OnDraw(HDC hdc);

	virtual void PlaySound();
	void DrawIntervalScene(HDC hdc);
	//메시지 처리를 합니다.
	virtual BOOL OnProcessingKeyboardMessage(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
	virtual BOOL OnProcessingMouseMessage(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
	//virtual BOOL OnProcessingWindowMessage(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

	virtual CurrentScene GetCurrentScene() { return CurrentScene::Stage6; }
private:

	//UI
	CUI_UnitInfo* UI_UnitInfo;
	CUI_CommandSelect* UI_CommandSelect;
	CUI_Notice* UI_Notice;
};