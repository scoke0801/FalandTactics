#pragma once

#include "UI_DetailSelect.h"

class CUI_CommandSelect : public CUI
{
private:
	CUI_CommandSelect() {}
	CUI_CommandSelect(HWND hWnd, HINSTANCE hInstance, CUnit* unit);
	~CUI_CommandSelect();

public:
	virtual void RegisterUI();
	virtual void MakeUI();
	virtual	void OnUpdate();
	virtual void DestroyUI();
	void HideUI();

	void OnDraw(HDC hdc);
	void CreateButton(int division = 0);
	void ArrangeUiSize();
	
	//set
	void SetPos(POINT mousePoint) { m_ptPos = mousePoint; }
	void SetUnit(CUnit* unit);
	//get
	POINT GetCreatePoint() const { return m_ptPos; }
	POINT GetPos() const { return m_ptPos; }
	CUnit* GetUnit() const { return m_pUnit; }
	HWND GetThis() { return hUi; }

public:
	static CUI_CommandSelect * GetInstance(HWND hWnd, HINSTANCE hInstance, CUnit* unit);
	static CUI_CommandSelect * GetInstance();

private:
	CUnit* m_pUnit;

	static CUI_CommandSelect* instance;

	POINT m_ptPos;							//UI가 생성될 위치를 나타냅니다.

	CUI_DetailSelect* UI_DetailSelect;

	RECT m_rcUI;
//버튼
	HWND m_buttonShow;
	HWND m_buttonTurnEnd;
	HWND m_buttonSystem;
	HWND m_buttonUseSkill;

};
LRESULT CALLBACK UI_CommandSelect_Proc(HWND hWnd, UINT uMsg,
	WPARAM wParam, LPARAM lParam);
