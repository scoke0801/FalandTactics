#pragma once

class CUI_Notice : public CUI
{
private:
	CUI_Notice() {}
	CUI_Notice(HWND hWnd, HINSTANCE hInstance, NoticePhase phase);
	~CUI_Notice();

public:
	virtual void RegisterUI();
	virtual void MakeUI();
	//virtual	void OnUpdate();
	virtual void DestroyUI();
	void HideUI();

	void Update(NoticePhase phase);
	void DrawUI(HDC);
	void DrawUI(HDC hdc, NoticePhase phase);
	//set
	void SetPhase(NoticePhase phase) { m_nPhase = phase; }
	void SetPos(POINT mousePoint) { m_ptPos = mousePoint; }
	//get

public:
	static CUI_Notice * GetInstance(HWND hWnd, HINSTANCE hInstance, NoticePhase phase);
	static CUI_Notice * GetInstance();

private:
	CImage m_imageNoticeBox;

	static CUI_Notice* instance;

	POINT m_ptPos;							//UI가 생성될 위치를 나타냅니다.

	NoticePhase m_nPhase;							//어떤 알림말을 전달할 것인지를 나타냅니다.
};
LRESULT CALLBACK UI_Notice_Proc(HWND hWnd, UINT uMsg,
	WPARAM wParam, LPARAM lParam);
