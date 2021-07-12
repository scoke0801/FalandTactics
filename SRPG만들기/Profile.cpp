#include "stdafx.h"
#include "profile.h"


CProfile* CProfile::instance = NULL;

CProfile::CProfile(LPCTSTR szName)
{
	m_szName = szName;
	if (Load())
	{
		m_bFirst = FALSE;
	}
	else
	{

		m_nAccumulationDamage = 0;
		m_nAccumulationKill = 0;;
		m_nStageClear = 0;
		m_nStageDefeat = 0;
	}
}

CProfile::~CProfile()
{

}

CProfile* CProfile::GetInstance(LPCTSTR szName)
{
	if (instance == NULL)
	{
		instance = new CProfile(szName);
	}
	return instance;
}
CProfile* CProfile::GetInstance()
{
	return instance;
}

void CProfile::Save()
{
	std::ofstream fout;
	fout.open(m_szName);

	fout << m_nStageClear << std::endl;
	fout << m_nStageDefeat << std::endl;
	fout << m_nAccumulationKill << std::endl;
	fout << m_nAccumulationDamage << std::endl;

	m_achievement.GetAchievement();
	fout.close();
}

BOOL CProfile::Load()
{
	std::ifstream ifile;
	char line[150];		// 한 줄씩 읽어서 임시로 저장할 공간
	short space = 0;	//다음 문자를 읽을 공간
	int i = 0;
	bool find = FALSE;
	CString temp;

	ifile.open(_T("resource/User/UserInfo.txt"));
	if (ifile.is_open())
	{
		while (ifile.getline(line, sizeof(line)))
		{
			temp = line;
			if (lstrcmp(m_szName, temp) == 0)
			{
				space += temp.GetLength();
				find = true;
			}
		}
	}

	return true;
}

#pragma region getter
LPCTSTR CProfile::GetNickname()
{
	return m_szName;
}
int CProfile::GetStageClear()
{
	return m_nStageClear;
}
int CProfile::GetStageDefeat()
{
	return m_nStageDefeat;
}
int CProfile::GetAccumulationKill()
{
	return m_nAccumulationKill;
}
int CProfile::GetAccumulationDamage()
{
	return m_nAccumulationDamage;
}
#pragma endregion
#pragma region setter
void CProfile::SetNickname(LPCTSTR name)
{
	m_szName = name;
}
void CProfile::SetStageClear(int StageClear)
{
	m_nStageClear = StageClear;
}
void CProfile::SetStageDefeat(int StageDefeat)
{
	m_nStageDefeat = StageDefeat;
}
void CProfile::SetAccumulationKill(int AccumulationKill)
{
	m_nAccumulationKill = AccumulationKill;
}
void CProfile::SetAccumulationDamage(int AccumulationDamage)
{
	m_nAccumulationDamage = AccumulationDamage;
}

void CProfile::AddAccumulationKill()
{
	++m_nAccumulationKill;
}
void CProfile::AddAccumulationDamage(int damage)
{
	m_nAccumulationDamage += damage;
}
void CProfile::AddStageClear()
{
	++m_nStageClear;
}
void CProfile::AddStageDefeat()
{
	++m_nStageDefeat;
}
void CProfile::AddStageClear(short stageNum)	//클리어한 스테이지
{
	if (stageNum < 0 || stageNum > 6)
		return;
	m_bClearList[stageNum] = TRUE;
	
	for (int i = 0; i < 6; ++i)
	{
		if (!m_bClearList[i])
		{
			return;	//클리어하지 않은 스테이지가 있는 경우
		}
	}
	
	static bool bFirst = FALSE;
	if (!bFirst)
	{
		bFirst = TRUE;
		m_achievement.AllStageClear();	//올 스테이지 클리어 업적 달성
	}
}
void CProfile::AddAchieveNum()		//클리어 횟수
{
	++m_nAchieveNum;

	if (m_nAchieveNum == Achievement::Achievement_Count)
	{
		m_achievement.AllAchievement();
	}
}
#pragma endregion
