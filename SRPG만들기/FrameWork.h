#pragma once

#include <iostream>
#include "Scene.h"
#include "Sound.h"
class CFrameWork
{
public:
	CFrameWork();	//생성자입니다.
	~CFrameWork();	//소멸자입니다.

public:
	BOOL OnCreate(HWND hWnd, HINSTANCE hInstance);	//사용될 변수들의 값을 초기화해줍니다.
	BOOL OnDestroy(); //할당되어 있는 메모리를 해제합니다.

	void CreateBuffer();//더블버퍼링을 위한 버퍼를 생성합니다.

	void OnDraw(HDC hdc);	 //화면을 출력합니다.
	
	BOOL LoadScene();
	void RegistScene();								//프로젝트에서 사용할 Scene을 등록합니다.
	void ChangeScene(CScene::CurrentScene tag);		//현재의 Scene을 변경합니다.
	void ChangeScene(TCHAR szMap[100], TCHAR szUnit[100]);
	void PreUpdate();//일정시간이 지난 경우에 업데이트 작업을 하도록 합니다.	
	void OnUpdate(float timeElapsed); //진행중인 작업을 갱신합니다.
	
	void OnProcessingKeyboardMessage(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);	//키입력에 관련된 메시지를 처리합니다.
	void OnProcessingMouseMessage(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);//마우스 입력에 관련된 메시지를 처리합니다.
	LRESULT OnProcessingWindowMessae(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);//메시지의 통로 역할을 합니다.

//get
	HWND GetHWND() { return m_hWnd; }
	HINSTANCE GetHINSTANCE() { return m_hInstance; }
	CSoundManager* GetSound() { return m_pSound; }
private:
	CSoundManager*		m_pSound;

private:
	HWND				m_hWnd;
	HINSTANCE			m_hInstance;
	
	HDC					m_hDC;
	HBITMAP				m_bufferBmp;
	HBRUSH				m_hBrush;
	HPEN				m_hPen;

	RECT				m_rcClient;

	CScene				*m_pCurScene;
	std::map<CScene::CurrentScene, CScene*> m_mapScene;
	std::map<CScene::CurrentScene, CScene*>::iterator m_iter;

	TCHAR				m_szCurrentDirectory[256];
///----------------------------------------------------------------
//	CUnit	*		m_unit;	//확인을 위한 임시 변수입니다.							
///----------------------------------------------------------------
	std::chrono::system_clock::time_point m_currentTime;
	std::chrono::duration<double> m_timeElapsed; // 시간이 얼마나 지났나
	double m_dLag;
	double m_fps;
	
	TCHAR m_captionTitle[50];
	int m_titleLength;
	std::chrono::system_clock::time_point m_lastUpdateTime;
	std::chrono::duration<double> m_updateElapsed; // 시간이 얼마나 지났나

};