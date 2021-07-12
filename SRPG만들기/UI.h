#pragma once

class CUI
{
public:
	CUI();
	CUI(HWND hWnd, HINSTANCE hInstance);
	virtual ~CUI();

	virtual void RegisterUI(); 		//UI용 윈도우를 등록합니다.
	virtual void MakeUI(); 			//UI용 윈도우를 생성합니다.
	virtual void ShowUI();			//UI용 윈도우를 보이도록합니다.
	virtual void DestroyUI();		//UI용 윈도우를 제거합니다.
	virtual void OnUpdate();
	
	CScene* GetParent() const { return m_pParent; }
	void SetParent(CScene* scene) { m_pParent = scene; }
	void SetRect(RECT rect) { m_rcRect = rect; }
	RECT GetRect() const { return m_rcRect; }
protected:
	HWND hWnd;
	HINSTANCE hInstance;
	HWND hUi;							//생성된 윈도우를 가리키는 핸들변수입니다.

//윈도우 등록 및 생성 관련 변수
	LPCTSTR szWindowClass;				//등록할 윈도우 클래스의 이름입니다.
	LPCTSTR szWindowTitle;				//등록할 윈도우 타이틀의 이름입니다.
	BOOL m_bRegistration;				//윈도우는 한 번만 등록하도록,
										//이미 등록했는 지에 대한 정보를 저장합니다.
	RECT m_rcRect;	

	CScene* m_pParent;					//UI를 사용중인 스테이지에 대한 정보를 가집니다.
};