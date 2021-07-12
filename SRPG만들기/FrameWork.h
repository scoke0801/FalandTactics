#pragma once

#include <iostream>
#include "Scene.h"
#include "Sound.h"
class CFrameWork
{
public:
	CFrameWork();	//�������Դϴ�.
	~CFrameWork();	//�Ҹ����Դϴ�.

public:
	BOOL OnCreate(HWND hWnd, HINSTANCE hInstance);	//���� �������� ���� �ʱ�ȭ���ݴϴ�.
	BOOL OnDestroy(); //�Ҵ�Ǿ� �ִ� �޸𸮸� �����մϴ�.

	void CreateBuffer();//������۸��� ���� ���۸� �����մϴ�.

	void OnDraw(HDC hdc);	 //ȭ���� ����մϴ�.
	
	BOOL LoadScene();
	void RegistScene();								//������Ʈ���� ����� Scene�� ����մϴ�.
	void ChangeScene(CScene::CurrentScene tag);		//������ Scene�� �����մϴ�.
	void ChangeScene(TCHAR szMap[100], TCHAR szUnit[100]);
	void PreUpdate();//�����ð��� ���� ��쿡 ������Ʈ �۾��� �ϵ��� �մϴ�.	
	void OnUpdate(float timeElapsed); //�������� �۾��� �����մϴ�.
	
	void OnProcessingKeyboardMessage(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);	//Ű�Է¿� ���õ� �޽����� ó���մϴ�.
	void OnProcessingMouseMessage(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);//���콺 �Է¿� ���õ� �޽����� ó���մϴ�.
	LRESULT OnProcessingWindowMessae(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);//�޽����� ��� ������ �մϴ�.

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
//	CUnit	*		m_unit;	//Ȯ���� ���� �ӽ� �����Դϴ�.							
///----------------------------------------------------------------
	std::chrono::system_clock::time_point m_currentTime;
	std::chrono::duration<double> m_timeElapsed; // �ð��� �󸶳� ������
	double m_dLag;
	double m_fps;
	
	TCHAR m_captionTitle[50];
	int m_titleLength;
	std::chrono::system_clock::time_point m_lastUpdateTime;
	std::chrono::duration<double> m_updateElapsed; // �ð��� �󸶳� ������

};