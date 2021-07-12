#pragma once
class CUnit;
class CMap;

class CStage4 : public CScene
{
public:
	CStage4(CFrameWork * framework, HWND hWnd, CurrentScene tag);
	~CStage4();

	virtual void OnUpdate(float timeElapsed);
	virtual void OnDraw(HDC hdc);

	virtual void PlaySound();
	virtual BOOL CheckGameWin();
	void DrawIntervalScene(HDC hdc);
	//�޽��� ó���� �մϴ�.
	virtual BOOL OnProcessingKeyboardMessage(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
	virtual BOOL OnProcessingMouseMessage(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
	//virtual BOOL OnProcessingWindowMessage(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

	virtual CurrentScene GetCurrentScene() { return CurrentScene::Stage4; }
private:
	BOOL m_bFirst;
	//UI
	CUI_UnitInfo* UI_UnitInfo;
	CUI_CommandSelect* UI_CommandSelect;
	CUI_Notice* UI_Notice;
};