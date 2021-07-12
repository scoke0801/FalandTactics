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

	POINT m_ptPos;							//UI�� ������ ��ġ�� ��Ÿ���ϴ�.

	CScene::CurrentScene m_phase;							//� �˸����� ������ �������� ��Ÿ���ϴ�.
};
LRESULT CALLBACK UI_ClearCondition_Proc(HWND hWnd, UINT uMsg,
	WPARAM wParam, LPARAM lParam);
