#pragma once
#include "Unit.h"

class CUI_UnitDetailInfo : public CUI
{
private:
	CUI_UnitDetailInfo() {}
	CUI_UnitDetailInfo(HWND hWnd, HINSTANCE hInstance);
	~CUI_UnitDetailInfo();

public:
	virtual void RegisterUI();
	virtual void MakeUI();
	virtual	void OnUpdate();
	virtual void DestroyUI();
	void HideUI();

	void DrawUnit(HDC hdc);

	//set
	void SetPhase(UnitInfoPhase phase) { m_phase = phase; }
	void SetUnit(CUnit* unit) { m_pUnit = unit; }
	void SetUserSelect(int userSelect) { m_nUserSelect = userSelect; }
	void SetText(LPCTSTR szText) { m_szText = szText; }
	//get
	UnitInfoPhase GetPhase() const { return m_phase; }
	HWND GetList() const { return m_listSkill; }
	int GetUserSelect() const { return m_nUserSelect; }
	LPCTSTR GetText() const { return m_szText; }

public:
	static CUI_UnitDetailInfo * GetInstance(HWND hWnd, HINSTANCE hInstance);
	static CUI_UnitDetailInfo * GetInstance();

public:
	void CreateButton();
	void CreateSkillList();
private:
	CUnit* m_pUnit;
	UnitInfoPhase m_phase;

	CImage m_unitImage;
	CImage m_backImage;
	CImage m_hpMpImage;
	CImage m_imageBack;
	static CUI_UnitDetailInfo* instance;

	HWND m_buttonStat;
	HWND m_buttonSkill;
	HWND m_listSkill;

	int m_nUserSelect;
	LPCTSTR m_szText;
};
LRESULT CALLBACK UI_UnitDetailInfo_Proc(HWND hWnd, UINT uMsg,
	WPARAM wParam, LPARAM lParam);

