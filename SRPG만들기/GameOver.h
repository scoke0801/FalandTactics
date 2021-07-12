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
	CImage m_gameOverImage;		//진 경우에 사용할 이미지를 나타냅니다.
	CImage m_imageUnit;			//이긴 경우에 사용할 도우미 이미지를 나타냅니다.
	CurrentScene m_tag;

	//short m_nAlpha;
	short m_nCount[2];
	bool m_UnitType;		//도우미 이미지 값 저장, 0 : 카린, 1 : 루루
};
