#pragma once
class CUI_ClearCondition : public CUI
{
private:
	CUI_ClearCondition() {}
	CUI_ClearCondition(HWND hWnd, HINSTANCE hInstance, CScene::CurrentScene phase);
	~CUI_ClearCondition();

public:
	virtual void RegisterUI();
	virtual void MakeUI();
	//virtual	void OnUpdate();
	virtual void DestroyUI();
	void HideUI();

	void Update(CScene::CurrentScene phase);
	void DrawUI(HDC);
	
	//set
	void SetPhase(CScene::CurrentScene phase) { m_phase = phase; }
	void SetPos(POINT mousePoint) { m_ptPos = mousePoint; }
	//get

public:
	static CUI_ClearCondition * GetInstance(HWND hWnd, HINSTANCE hInstance, CScene::CurrentScene phase);
	static CUI_ClearCondition * GetInstance();

private:
	CImage m_imageCondition;

	static CUI_ClearCondition* instance;

	POINT m_ptPos;							//UI가 생성될 위치를 나타냅니다.

	CScene::CurrentScene m_phase;							//어떤 알림말을 전달할 것인지를 나타냅니다.
};
LRESULT CALLBACK UI_ClearCondition_Proc(HWND hWnd, UINT uMsg,
	WPARAM wParam, LPARAM lParam);
