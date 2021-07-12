#pragma once

class CFrameWork;

class CConsoleManager
{
public:
	CConsoleManager(CFrameWork * pFramework);		//持失切
	~CConsoleManager();		//社瑚切

	void OnUpdate();
private:
	CFrameWork* m_pFramework;
};