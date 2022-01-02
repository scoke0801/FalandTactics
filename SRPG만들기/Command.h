#pragma once

class CUnit;
class Node;
/*
����� ������ �������̽� Ŭ������ �θ� Ŭ�����Դϴ�.
*/
typedef void(*CommandFunc)();

class CGameCommand
{
public:
	CGameCommand() {}
	CGameCommand(CUnit* unit) {}
public:	//�ڽ� Ŭ�������� �����ǰ� �ʿ��� �Լ����� �����մϴ�.
	virtual ~CGameCommand() {}
	virtual BOOL Execute(CUnit* unit) = 0;	//�� ���� ������ TRUE��, �������ʾҴٸ� FALSE�� ��ȯ�մϴ�.

public:	//�ڽ� Ŭ�������� �����ǰ� ���ʿ��� �Լ����� �����մϴ�.
	CUnit* Undo(CUnit* unit);
	void SetUnitInfo(CUnit* unit);

	void SetUnit(CUnit* unit) { m_pUnit = unit; }
	CUnit* GetUnit() const { return m_pUnit; }

protected:
	CUnit*	m_pUnit;
};

/*
�̵� ����� �����մϴ�.
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
���ݸ���� �����մϴ�.
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
�ǰݸ���� �����մϴ�.
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
������� �����մϴ�.
*/
class CDefenseCommand : public CGameCommand
{
public:
	~CDefenseCommand() {}
	virtual BOOL Execute(CUnit* unit);
};

/*
��ų����� �����մϴ�.
�Լ������͸� ���ڷ� ���޹޾� 
���� ������ ��ų�� ȣ���ϵ��� �մϴ�.
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
	POINT m_ptPos;			//�׷��� ��ġ

	int m_nImagePos[2];		//�̹��� ��ġ
	
	int m_nSkillRange;		//��ų�� ���� ����

	int m_nMpConsumption;	//��ų�� ���� �Ҹ�

	SkillAttackType m_attackType;	//��ų�� ���� ���

	std::map<INDEX, CTile*> m_mapAttackableTile;	//��ų�� ���� ���� Ÿ��

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