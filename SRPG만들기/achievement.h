#pragma once

/*
������ ���õ� ������ �����մϴ�.

������ ������ �����Ͽ� �����ϵ��� �մϴ�.

�ð��� �����Ͽ� ��ü���� ���� ������ ��������
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
	BOOL m_bNumerousEnemyKill;		//���� ������ ����
	BOOL m_bAllStageClear;			//���� ������ ����
	BOOL m_bNoKillClear;			//���� ������ ����
	BOOL m_bOneShotOneKill;			//���� ����
	BOOL m_bOneUnitAllKill;			//���� ������ ����
	BOOL m_bDefeat3;				//??
	BOOL m_bAccumulation1000;		//���� ������ ����, ����ų
	BOOL m_bBerserk;				//??
	BOOL m_bAchievement10;			//���� ������ ����, 10
	BOOL m_bResurrection4;			//??
	BOOL m_bAllAchievement;			//���� ������ ����, ��� ���� �޼�
	BOOL m_bNewPlayer;				//���� ������ ����, ó�� ���
	BOOL m_bAllSurviveClear;		//���� ������ ����, �������� ����
	BOOL m_bFirstClear;				//���� ������ ����, �������� ó�� Ŭ����
	BOOL m_bFirstDefeat;			//���� ������ ����, �������� ó�� �й�
	BOOL m_bRetry;					//���� ������ ����, �� ����
	BOOL m_bReConnect;				//���� ������ ����, ���� �� ���

public:
	//���޹��� ���ڿ� �ش��ϴ� ������ �޼��Ѱ����� �����մϴ�.
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