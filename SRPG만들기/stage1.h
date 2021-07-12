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

	// ��� ��ȯ ��, ���� �����ϰ� �����ϱ� ���Ͽ� ����� �Լ�
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