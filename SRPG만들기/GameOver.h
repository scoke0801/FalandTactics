#pragma once

class CGameOverScene : public CScene
{
public:
	CGameOverScene(CFrameWork * framework, HWND hWnd, CurrentScene tag);
	~CGameOverScene();

	void LoadImage();

	virtual void OnUpdate(float timeElapsed);
	virtual void OnDraw(HDC hdc);
	virtual void PlaySound();
	
	void DrawWinAnimation(HDC hdc);

	virtual BOOL OnProcessingKeyboardMessage(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
	virtual BOOL OnProcessingMouseMessage(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
	//virtual BOOL OnProcessingWindowMessage(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
	
	void SetTag(CurrentScene tag);
	virtual CurrentScene GetCurretScene() { return CurrentScene::GameWin; }

private:
	CImage m_gameOverImage;		//�� ��쿡 ����� �̹����� ��Ÿ���ϴ�.
	CImage m_imageUnit;			//�̱� ��쿡 ����� ����� �̹����� ��Ÿ���ϴ�.
	CurrentScene m_tag;

	//short m_nAlpha;
	short m_nCount[2];
	bool m_UnitType;		//����� �̹��� �� ����, 0 : ī��, 1 : ���
};
