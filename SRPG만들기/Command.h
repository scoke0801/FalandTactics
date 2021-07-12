#pragma once

class CUnit;
class Node;
/*
명령을 지시할 인터페이스 클래스의 부모 클래스입니다.
*/
typedef void(*CommandFunc)();

class CGameCommand
{
public:
	CGameCommand() {}
	CGameCommand(CUnit* unit) {}
public:	//자식 클래스에서 재정의가 필요한 함수들을 정의합니다.
	virtual ~CGameCommand() {}
	virtual BOOL Execute(CUnit* unit) = 0;	//할 일이 끝나면 TRUE를, 끝나지않았다면 FALSE를 반환합니다.

public:	//자식 클래스에서 재정의가 불필요한 함수들을 정의합니다.
	CUnit* Undo(CUnit* unit);
	void SetUnitInfo(CUnit* unit);

	void SetUnit(CUnit* unit) { m_pUnit = unit; }
	CUnit* GetUnit() const { return m_pUnit; }

protected:
	CUnit*	m_pUnit;
};

/*
이동 명령을 지시합니다.
*/
class CMoveCommand : public CGameCommand
{
public:
	CMoveCommand(CUnit* unit);
	~CMoveCommand() {}

	virtual BOOL Execute(CUnit* unit);

private:
	std::vector < Node* > m_vecMoveTile;
	int m_nCurrentIndex;
};

/*
공격명령을 지시합니다.
*/
class CAttackCommand : public CGameCommand
{
public:
	CAttackCommand(CUnit* unit);
	~CAttackCommand() {}
	virtual BOOL Execute(CUnit* unit);

private:
	CUnit* m_pTarget;
};

/*
피격명령을 지시합니다.
*/
class CAttackedCommand : public CGameCommand
{
public:
	CAttackedCommand();
	~CAttackedCommand() {}
	virtual BOOL Execute(CUnit* unit);
private:
	int m_delay;
};

/*
방어명령을 지시합니다.
*/
class CDefenseCommand : public CGameCommand
{
public:
	~CDefenseCommand() {}
	virtual BOOL Execute(CUnit* unit);
};

/*
스킬사용을 지시합니다.
함수포인터를 인자로 전달받아 
같은 형식의 스킬을 호출하도록 합니다.
*/
class CSkillCommand : public CGameCommand
{
public:
	CSkillCommand() {}
	CSkillCommand(CUnit* unit);
	~CSkillCommand();

	virtual BOOL Execute(CUnit* unit);
	
	virtual void DrawSkill(HDC hdc, Camera camera = { 0, }) {}
	virtual void PlayEffect() {}

	virtual void Enter();

	void SetImagePos(int pos) { m_nImagePos[1] = pos; }
	int GetImagePos() const { return m_nImagePos[1]; }

	void SetSkillRange(int range) { m_nSkillRange = range; }
	int GetSkillRange() const { return m_nSkillRange; }
	
	void SetPos(POINT pos) { m_ptPos = pos; }
	POINT GetPos() const { return m_ptPos; }

	void UpdateSprite();
	virtual BOOL CheckSkillEnd();

protected:
	POINT m_ptPos;			//그려질 위치

	int m_nImagePos[2];		//이미지 위치
	
	int m_nSkillRange;		//스킬의 공격 범위

	int m_nMpConsumption;	//스킬의 마나 소모량

	SkillAttackType m_attackType;	//스킬의 공격 방식

	std::map<INDEX, CTile*> m_mapAttackableTile;	//스킬의 공격 가능 타일

	CUnit* m_pTarget;
};

class CBurstSkill : public CSkillCommand
{
public:
	CBurstSkill(int skillRange, SkillAttackType type, CUnit* unit, int mpConsumption);
	~CBurstSkill();

	virtual void DrawSkill(HDC hdc, Camera camera = { 0, });

	virtual BOOL CheckSkillEnd();

	virtual void PlayEffect();
};

class CAidSkill : public CSkillCommand
{
public:
	CAidSkill(int skillRange, SkillAttackType type, CUnit* unit, int mpConsumption, int kind = 0);
	~CAidSkill();

	virtual void Enter();
	virtual BOOL Execute(CUnit* unit);

	virtual void DrawSkill(HDC hdc, Camera camera = { 0, });

	virtual BOOL CheckSkillEnd();

	virtual void PlayEffect();

private:
	int m_nKind;
};

class CResurrectionSkill : public CSkillCommand
{
public:
	CResurrectionSkill(int skillRange, SkillAttackType type, CUnit* unit, int mpConsumption);
	~CResurrectionSkill();

	virtual void Enter();
	virtual BOOL Execute(CUnit* unit);

	virtual void DrawSkill(HDC hdc, Camera camera = { 0, });

	virtual BOOL CheckSkillEnd();

	virtual void PlayEffect();
};

class CEdgeSkill : public CSkillCommand
{
public:
	CEdgeSkill(int skillRange, SkillAttackType type, CUnit* unit, int mpConsumption);
	~CEdgeSkill();
	
	virtual void DrawSkill(HDC hdc, Camera camera = { 0, });

	virtual BOOL CheckSkillEnd();

	virtual void PlayEffect();
};

class CThunderSkill : public CSkillCommand
{
public:
	CThunderSkill(int skillRange, SkillAttackType type, CUnit* unit, int mpConsumption);
	~CThunderSkill();

	virtual void DrawSkill(HDC hdc, Camera camera = { 0, });

	virtual BOOL CheckSkillEnd();

	virtual void PlayEffect();
};

class CDarkSkill : public CSkillCommand
{
public:
	CDarkSkill(int skillRange, SkillAttackType type, CUnit* unit, int mpConsumption);
	~CDarkSkill();

	virtual void DrawSkill(HDC hdc, Camera camera = { 0, });

	virtual BOOL CheckSkillEnd();

	virtual void PlayEffect();
};

class CWindSKill : public CSkillCommand
{
public:
	CWindSKill(int skillRange, SkillAttackType type, CUnit* unit, int mpConsumption);
	~CWindSKill();

	virtual void DrawSkill(HDC hdc, Camera camera = { 0, });

	virtual BOOL CheckSkillEnd();

	virtual void PlayEffect();
};