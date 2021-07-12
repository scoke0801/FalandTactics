#pragma once


class CTitleScene : public CScene
{
public:
	CTitleScene(CFrameWork * framework, HWND hWnd);
	~CTitleScene();

	void LoadBackground(LPTSTR szPath);

	virtual void OnUpdate(float timeElapsed);
	virtual void OnDraw(HDC hdc);

	virtual void PlaySound();

	//CTitleScene������ ó�� ���Ŀ��� ó���� �ʿ��� ���� �ִٸ� FALSE�� ��ȯ�մϴ�.
	virtual BOOL OnProcessingKeyboardMessage(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
	virtual BOOL OnProcessingMouseMessage(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
	virtual BOOL OnProcessingWindowMessage(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

	virtual CurrentScene GetCurretScene() { return CurrentScene::Title; }

	void CreateButton();
private:
	CImage m_background;

	HWND m_buttonSelectStage;
	HWND m_buttonLoadStage;
	HWND m_buttonEndGame;
	HFONT m_font;

	CUI_StageSelect* UI_stageSelect;
	CUI_Login* UI_Login;
};