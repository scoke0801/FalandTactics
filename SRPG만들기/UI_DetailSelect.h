#pragma once

typedef enum
{
	Show = 0
	, System
	, Skill
}DetailSelectPhase;
class CUI_DetailSelect : public CUI
{
private:
	CUI_DetailSelect() {}
	CUI_DetailSelect(HWND hWnd, HINSTANCE hInstance);
	~CUI_DetailSelect();

public:
	virtual void RegisterUI();
	virtual void MakeUI();
	virtual	void OnUpdate();
	virtual void DestroyUI();
	void HideUI();
	
	void ArrangeUiSize();
	void CreateButton();
	//set
	void SetPos(POINT mousePoint) { m_ptPos = mousePoint; }
	void SetPhase(DetailSelectPhase phase) { m_phase = phase; }
	void SetUnit(CUnit* unit) { m_pUnit = unit; }
	//get
	POINT GetPos() const { return m_ptPos; }
	CUnit* GetUnit() const { return m_pUnit; }

public:
	static CUI_DetailSelect * GetInstance(HWND hWnd, HINSTANCE hInstance);
	static CUI_DetailSelect * GetInstance();

private:
	static CUI_DetailSelect* instance;

	DetailSelectPhase m_phase;

	POINT m_ptPos;							//UI가 생성될 위치를 나타냅니다.

	HWND m_buttonUnitList;
	HWND m_buttonClearCondition;
	HWND m_buttonGameEnd;
	HWND m_buttonStageChange;
	std::vector <HWND> m_buttonSkill;

	CUnit* m_pUnit;
};
LRESULT CALLBACK UI_DetailSelect_Proc(HWND hWnd, UINT uMsg,
	WPARAM wParam, LPARAM lParam);
