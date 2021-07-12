#pragma once
#include "achievement.h"


/*
����ڿ� ���ؼ� �ʿ��� ������ �����մϴ�.
*/


class CProfile {
private:
	CProfile(LPCTSTR szName);
	~CProfile();

public:
	static CProfile* GetInstance(LPCTSTR szName);
	static CProfile* GetInstance();

public:
	void Save();
	BOOL Load();		//���� �̸��� ã���� TRUE, �� ã���� FALSE

	//getter
	CAchievement GetAchievement() const { return m_achievement; }

	LPCTSTR GetNickname();
	int GetStageClear();
	int GetStageDefeat();
	int GetAccumulationKill();
	int GetAccumulationDamage();

	//setter
	void SetNickname(LPCTSTR);
	void SetStageClear(int);
	void SetStageDefeat(int);
	void SetAccumulationKill(int);
	void SetAccumulationDamage(int);

	void AddAccumulationKill();		//����ų + 1;
	
	void AddAccumulationDamage(int damage);	//���� ����� + damage
	
	void AddStageClear();			//�������� Ŭ���� Ƚ�� + 1;
	
	void AddStageDefeat();			//�������� �й� Ƚ�� + 1;

	void AddStageClear(short stageNum);	//Ŭ������ �������� ���

	void AddAchieveNum();			//Ŭ���� Ƚ��
private:
	LPCTSTR m_szName;						//���� �̸�
	CAchievement m_achievement;				//����
	short m_nStageClear, m_nStageDefeat;	//���� Ŭ����, ���� �й�
	short m_nAccumulationKill;				//���� ų ��
	short m_nAccumulationDamage;			//���� �����

	BOOL m_bFirst;						    //���� ù ���

	BOOL m_bClearList[6];			//Ŭ������ �������� ���

	short m_nAchieveNum;			//�޼��� ���� ��
private:	
	static CProfile* instance;
};