#pragma once

class CUnit;
class CMap;

class CStageUser : public CScene
{
public:
	CStageUser(CFrameWork * framework, HWND hWnd, CurrentScene tag, LPCTSTR szMap, LPCTSTR szUnit);
	~CStageUser();

	virtual void OnUpdate(float timeElapsed);
	virtual void OnDraw(HDC hdc);

	virtual void PlaySound();
	void DrawIntervalScene(HDC hdc);
	//�޽��� ó���� �մϴ�.
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