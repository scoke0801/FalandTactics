#pragma once

#include "Unit.h"

class CUI_StageSelect : public CUI
{
private:
	CUI_StageSelect() {}
	CUI_StageSelect(HWND hWnd, HINSTANCE hInstance);
	~CUI_StageSelect();

public:
	virtual void RegisterUI();
	virtual void MakeUI();
	virtual void DestroyUI();

	BOOL UpdateUI();
	void MakeButtonUI();
public:
	//void SetRect(RECT rect) { m_rcApp = rect; }
	//get
	HINSTANCE GetHINSTANCE() { return hInstance; }
	CFrameWork* GetFrameWork() const { return m_pFrameWork; }
	CScene::CurrentScene GetCurrentStage() const { return m_tag; }
	//set
	void SetHUI(HWND* hWnd) { hUi = *hWnd; }
	void SetButton(HWND* hButtonSelectStage, HWND* hButtonLoadStage, HWND* hButtonEndGame);
	void SetFraemWork(CFrameWork* frameWork) { m_pFrameWork = frameWork; }
	void SetCurrentStage(CScene::CurrentScene tag) { m_tag = tag; }
public:
	static CUI_StageSelect * GetInstance(HWND hWnd, HINSTANCE hInstance);
	static CUI_StageSelect * GetInstance();

private:
	static CUI_StageSelect* instance;
	HWND m_edit;
	HWND m_list;
	HWND* m_buttonSelectStage;
	HWND* m_buttonLoadStage;
	HWND* m_buttonEndGame;
	HFONT m_font;

	CFrameWork* m_pFrameWork;

	CScene::CurrentScene m_tag;
	
	bool m_bTitie;	//현재 장면이 타이틀 화면인지 확인합니다.
};

LRESULT CALLBACK UI_StageSelect_Proc(HWND hWnd, UINT uMsg,
	WPARAM wParam, LPARAM lParam);

