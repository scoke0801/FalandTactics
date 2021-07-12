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

	POINT m_ptPos;							//UI�� ������ ��ġ�� ��Ÿ���ϴ�.

	NoticePhase m_nPhase;							//� �˸����� ������ �������� ��Ÿ���ϴ�.
};
LRESULT CALLBACK UI_Notice_Proc(HWND hWnd, UINT uMsg,
	WPARAM wParam, LPARAM lParam);
