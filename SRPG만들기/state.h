#pragma once

class CUnit;
class CGameCommand;
class CSkillCommand;
/*
��ü�� ������ ���ӹ޾� 
���� ���¿� ���� ���۰� �����͸� Ŭ������ ĸ��ȭ�մϴ�.

���ο� ���°� �ʿ��ϴٸ� 
CState�� �θ�� �ϴ� �ڽ� Ŭ������ ���ǰ� �ʿ��մϴ�.
*/
class CState
{
public:
	CState()	{}
	CState(CUnit* unit);
	virtual ~CState();

	virtual CState* HandleInput(CUnit* unit, KeyInput input);	
	CState* HandleInput(CUnit* unit, SKillName input);

	virtual void Enter(CUnit* unit);		//���ο� ���·� �����մϴ�.
	virtual void Excute(CUnit* unit);		//���¿��� �� ���� �����մϴ�.
											
	virtual CState* Exit(CUnit* unit);		//���� ���¿��� �����մϴ�.

public:
	virtual SpriteState GetState() { return SpriteState::state_count; }		//������ ���¸� ��ȯ�մϴ�.
	CGameCommand* GetCommand()  const { return m_command; }
	CSkillCommand* GetSkillCommand() const { return m_skillCommand; }
protected:
	CGameCommand* m_command;
	CSkillCommand* m_skillCommand;
};

/*
�⺻ ���¿� ���� ���Ǹ� �մϴ�.
*/
class CIdleState : public CState
{
public:
	CIdleState(CUnit* unit);
	virtual CState* HandleInput(CUnit* unit, KeyInput input);
	virtual void Enter(CUnit* unit);
	virtual void Excute(CUnit* unit);
	virtual CState* Exit(CUnit* unit);

public:
	virtual SpriteState GetState() { return SpriteState::state_idle; }
	

};

/*
�̵� ���¿� ���� ���Ǹ� �մϴ�.
*/
class CMoveState : public CState
{
public:
	CMoveState(CUnit* unit);

	virtual CState* HandleInput(CUnit* unit, KeyInput input);
	virtual void Enter(CUnit* unit);
	virtual void Excute(CUnit* unit);
	virtual CState* Exit(CUnit* unit);

public:
	virtual SpriteState GetState() { return SpriteState::state_move; }
};

/*
���� ���¿� ���� ���Ǹ� �մϴ�.
*/
class CAttackState : public CState
{
public:
	CAttackState(CUnit* unit);
	virtual CState* HandleInput(CUnit* unit, KeyInput input);
	virtual void Enter(CUnit* unit);
	virtual void Excute(CUnit* unit);
	virtual CState* Exit(CUnit* unit);

public:
	virtual SpriteState GetState() { return SpriteState::state_attack; }
	bool m_bPlaySonud;
};

/*
��ų ���¿� ���� ���Ǹ� �մϴ�.
*/
class CSkillState : public CState
{
public:
	CSkillState(CUnit* unit, SKillName name);
	virtual CState* HandleInput(CUnit* unit, KeyInput input);
	virtual void Enter(CUnit* unit);
	virtual void Excute(CUnit* unit);
	virtual CState* Exit(CUnit* unit);

public:
	virtual SpriteState GetState() { return SpriteState::state_skill; }
	SKillName name;
	int m_nDelay;
};
/*
���� ���¿� ���� ���Ǹ� �մϴ�.
*/
class CStopState : public CState
{
public:
	CStopState(CUnit* unit);
	virtual CState* HandleInput(CUnit* unit, KeyInput input);
	virtual void Enter(CUnit* unit);
	virtual void Excute(CUnit* unit);
	virtual CState* Exit(CUnit* unit);

public:
	virtual SpriteState GetState() { return SpriteState::state_stop; }

};

/*
���� ���¿� ���� ���Ǹ� �մϴ�.
*/
class CDieState : public CState
{
public:
	CDieState(CUnit* unit);
	virtual CState* HandleInput(CUnit* unit, KeyInput input);
	virtual void Enter(CUnit* unit);
	virtual void Excute(CUnit* unit);
	virtual CState* Exit(CUnit* unit);

public:
	virtual SpriteState GetState() { return SpriteState::state_die; }
};

/*
��� ���¿� ���� ���Ǹ� �մϴ�.
*/
class CDefenseState : public CState
{
public:
	CDefenseState(CUnit* unit);
	virtual CState* HandleInput(CUnit* unit, KeyInput input);
	virtual void Enter(CUnit* unit);
	virtual void Excute(CUnit* unit);
	virtual CState* Exit(CUnit* unit);

public:
	virtual SpriteState GetState() { return SpriteState::state_defense; }
};

/*
�ǰ� ���¿� ���� ���Ǹ� �մϴ�.
*/
class CAttackedState : public CState
{
public:
	CAttackedState(CUnit* unit);
	virtual CState* HandleInput(CUnit* unit, KeyInput input);
	virtual void Enter(CUnit* unit);
	virtual void Excute(CUnit* unit);
	virtual CState* Exit(CUnit* unit);

public:
	virtual SpriteState GetState() { return SpriteState::state_attacked; }

private:
	int m_delay;
};