#pragma once
#include "achievement.h"


/*
사용자에 대해서 필요한 정보를 정의합니다.
기록 정리, 업적 처리를 위한 내용들을 정의합니다.
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
	BOOL Load();		//같은 이름을 찾으면 TRUE, 못 찾으면 FALSE

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

	void AddAccumulationKill();		//누적킬 + 1;
	
	void AddAccumulationDamage(int damage);	//누적 대미지 + damage
	
	void AddStageClear();			//스테이지 클리어 횟수 + 1;
	
	void AddStageDefeat();			//스테이지 패배 횟수 + 1;

	void AddStageClear(short stageNum);	//클리어한 스테이지 등록

	void AddAchieveNum();			//클리어 횟수

private:
	LPCTSTR m_szName;						//유저 이름
	CAchievement m_achievement;				//업적
	short m_nStageClear, m_nStageDefeat;	//누적 클리어, 누적 패배
	short m_nAccumulationKill;				//누적 킬 수
	short m_nAccumulationDamage;			//누적 대미지

	BOOL m_bFirst;						    //정보 첫 등록

	BOOL m_bClearList[6];			//클리어한 스테이지 목록

	short m_nAchieveNum;			//달성한 업적 수
private:	
	static CProfile* instance;
};