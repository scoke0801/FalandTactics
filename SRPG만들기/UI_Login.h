#pragma once

class CUI_Login : public CUI
{
private:
	CUI_Login() {}
	CUI_Login(HWND hWnd, HINSTANCE hInstance);
	~CUI_Login();

public:
	virtual void RegisterUI();
	virtual void MakeUI();
	//virtual	void OnUpdate();
	virtual void DestroyUI();
	void HideUI();

	void CreateButton();
	void DrawUI(HDC);
	//set
	void SetPos(POINT mousePoint) { m_ptPos = mousePoint; }
	//get
	void SetProfile();
public:
	static CUI_Login * GetInstance(HWND hWnd, HINSTANCE hInstance);
	static CUI_Login * GetInstance();

private:
	CImage m_imageBack;

	static CUI_Login* instance;

	POINT m_ptPos;							//UI가 생성될 위치를 나타냅니다

	HWND m_buttonInput;
	HWND m_editName;
	HWND m_buttonDefault;
};
LRESULT CALLBACK UI_Login_Proc(HWND hWnd, UINT uMsg,
	WPARAM wParam, LPARAM lParam);
