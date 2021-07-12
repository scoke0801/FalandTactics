#pragma once

class CUI
{
public:
	CUI();
	CUI(HWND hWnd, HINSTANCE hInstance);
	virtual ~CUI();

	virtual void RegisterUI(); 		//UI�� �����츦 ����մϴ�.
	virtual void MakeUI(); 			//UI�� �����츦 �����մϴ�.
	virtual void ShowUI();			//UI�� �����츦 ���̵����մϴ�.
	virtual void DestroyUI();		//UI�� �����츦 �����մϴ�.
	virtual void OnUpdate();
	
	CScene* GetParent() const { return m_pParent; }
	void SetParent(CScene* scene) { m_pParent = scene; }
	void SetRect(RECT rect) { m_rcRect = rect; }
	RECT GetRect() const { return m_rcRect; }
protected:
	HWND hWnd;
	HINSTANCE hInstance;
	HWND hUi;							//������ �����츦 ����Ű�� �ڵ麯���Դϴ�.

//������ ��� �� ���� ���� ����
	LPCTSTR szWindowClass;				//����� ������ Ŭ������ �̸��Դϴ�.
	LPCTSTR szWindowTitle;				//����� ������ Ÿ��Ʋ�� �̸��Դϴ�.
	BOOL m_bRegistration;				//������� �� ���� ����ϵ���,
										//�̹� ����ߴ� ���� ���� ������ �����մϴ�.
	RECT m_rcRect;	

	CScene* m_pParent;					//UI�� ������� ���������� ���� ������ �����ϴ�.
};