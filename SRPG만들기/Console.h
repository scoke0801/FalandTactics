#pragma once

class CFrameWork;

class CConsoleManager
{
public:
	CConsoleManager(CFrameWork * pFramework);		//������
	~CConsoleManager();		//�Ҹ���

	void OnUpdate();
private:
	CFrameWork* m_pFramework;
};