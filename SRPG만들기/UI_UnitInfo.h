#pragma once

#include "Unit.h"

class CUI_UnitInfo : public CUI
{
private:
	CUI_UnitInfo() {}
	CUI_UnitInfo(HWND hWnd, HINSTANCE hInstance, CUnit* unit);
	~CUI_UnitInfo();

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
	static CUI_UnitInfo * GetInstance(HWND hWnd, HINSTANCE hInstance, CUnit* unit);
	static CUI_UnitInfo * GetInstance();

private:
	CUnit* m_pUnit;

	CImage m_unitImage;
	CImage m_backImage;
	CImage m_hpMpImage;

	static CUI_UnitInfo* instance;
};
LRESULT CALLBACK UI_UnitInfo_Proc(HWND hWnd, UINT uMsg,
	WPARAM wParam, LPARAM lParam);

