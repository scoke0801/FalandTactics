#pragma once
#include "Unit.h"

class CUI_Achievement : public CUI
{
private:
	CUI_Achievement() {}
	CUI_Achievement(HWND hWnd, HINSTANCE hInstance, CUnit* unit);
	~CUI_Achievement();

public:
	virtual void RegisterUI();
	virtual void MakeUI();
	virtual	void OnUpdate();
	virtual void DestroyUI();
	void HideUI();

	BOOL CompareUnit(CUnit* unit);	//현재 유닛과 인자로 전달받은 유닛이 같은 유닛인지 확인합니다.
	void DrawUnit(HDC hdc);
	void ReDraw();
	//set
	void SetUnit(CUnit* unit) { m_pUnit = unit; }
	//get

public:
	static CUI_Achievement * GetInstance(HWND hWnd, HINSTANCE hInstance, CUnit* unit);
	static CUI_Achievement * GetInstance();

private:
	CUnit* m_pUnit;

	CImage m_unitImage;
	CImage m_backImage;
	CImage m_hpMpImage;

	static CUI_Achievement* instance;
};
LRESULT CALLBACK UI_Achievement_Proc(HWND hWnd, UINT uMsg,
	WPARAM wParam, LPARAM lParam);

