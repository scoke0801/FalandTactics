#pragma once

/*
업적에 관련된 내용을 정의합니다.
*/


class Observer
{
public:
	virtual ~Observer() {}
	virtual void UnitUpdate(const CUnit&, Achievement) = 0;
	virtual void StageUpdate(const CUnit&, Achievement) = 0;
	virtual void ETCUpdate(const CUnit&, Achievement) = 0;
};

class CAchievement : public Observer
{
	BOOL m_bNumerousEnemyKill;		//유저 정보와 연관
	BOOL m_bAllStageClear;			//유저 정보와 연관
	BOOL m_bNoKillClear;			//유저 정보와 연관
	BOOL m_bOneShotOneKill;			//유닛 관련
	BOOL m_bOneUnitAllKill;			//유저 정보와 연관
	BOOL m_bDefeat3;				//??
	BOOL m_bAccumulation1000;		//유저 정보와 연관, 누적킬
	BOOL m_bBerserk;				//??
	BOOL m_bAchievement10;			//유저 정보와 연관, 10
	BOOL m_bResurrection4;			//??
	BOOL m_bAllAchievement;			//유저 정보와 연관, 모든 업적 달성
	BOOL m_bNewPlayer;				//유저 정보와 연관, 처음 등록
	BOOL m_bAllSurviveClear;		//유저 정보와 연관, 스테이지 종료
	BOOL m_bFirstClear;				//유저 정보와 연관, 스테이지 처음 클리어
	BOOL m_bFirstDefeat;			//유저 정보와 연관, 스테이지 처음 패배
	BOOL m_bRetry;					//유저 정보와 연관, 재 시작
	BOOL m_bReConnect;				//유저 정보와 연관, 정보 재 등록

public:
	//전달받은 인자에 해당하는 업적을 달성한것으로 변경합니다.
	void UnLock(Achievement achievement);
	
public:
	void GetAchievement();

	void NumerousEnemyKill(const CUnit&);
	void AllStageClear();
	void NoKillClear();
	void OneShotOneKill(const CUnit&, int);
	void OneUnitAllKill(const CUnit&);
	void Defeat3();
	void Accumulation1000();
	void Berserk(const CUnit&);
	void Achievement10();
	void AllAchievement();
	void Resurrection4(const CUnit&);
	void NewPlayer();
	void AllSurviveClear();
	void FirstClear();
	void FirstDefeat();
	void Retry();
	void ReConnect();
	
	BOOL GetNumerousEnemyKill();
	BOOL GetAllStageClear();
	BOOL GetNoKillClear();
	BOOL GetOneShotOneKill();
	BOOL GetOneUnitAllKill();
	BOOL GetDefeat3();
	BOOL GetAccumulation1000();
	BOOL GetBerserk();
	BOOL GetAchievement10();
	BOOL GetResurrection4();
	BOOL GetAllAchievement();
	BOOL GetNewPlayer();
	BOOL GetAllSurviveClear();
	BOOL GetFirstClear();
	BOOL GetFirstDefeat();
	BOOL GetRetry();
	BOOL GetReConnect();
	virtual void StageUpdate(const CUnit&, Achievement);
	virtual void UnitUpdate(const CUnit&, Achievement);
	virtual void ETCUpdate(const CUnit&, Achievement);
	~CAchievement() {}



};


class Subject
{
private:
	std::vector<Observer*> observers;
public:
	void Subject::addObserver(Observer* observer)
	{
		observers.push_back(observer);
	}
	std::vector<Observer*> Getobsevers()
	{
		return observers;
	}
	void Subject::removeObserver(Observer* observer)
	{
		for (std::vector<Observer*>::iterator to_remove = observers.begin(); to_remove != observers.end(); ++to_remove)
		{
			if (*to_remove == observer)
			{
				observers.erase(to_remove);
				break;
			}
		}
	}
	void Subject::UnitNotify(const CUnit& entity, Achievement achievement)
	{
		for (auto o : observers)
		{
			if (o != nullptr)
				o->UnitUpdate(entity, achievement);
		}
	}
	void Subject::StageNotify(const CUnit& entity, Achievement achievement)
	{
		for (auto o : observers)
		{
			if (o != nullptr)
				o->StageUpdate(entity, achievement);
		}
	}
	void Subject::ETCNotify(const CUnit& entity, Achievement achievement)
	{
		for (auto o : observers)
		{
			if (o != nullptr)
				o->ETCUpdate(entity, achievement);
		}
	}
};