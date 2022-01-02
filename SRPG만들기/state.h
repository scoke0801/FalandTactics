#pragma once

class CUnit;
class CGameCommand;
class CSkillCommand;
/*
객체의 동작을 위임받아 
같은 상태에 대한 동작과 데이터를 클래스에 캡슐화합니다.

새로운 상태가 필요하다면 
CState를 부모로 하는 자식 클래스의 정의가 필요합니다.
*/
class CState
{
public:
	CState()	{}
	CState(CUnit* unit);
	virtual ~CState();

	virtual CState* HandleInput(CUnit* unit, KeyInput input);	
	CState* HandleInput(CUnit* unit, SKillName input);

	virtual void Enter(CUnit* unit);		//새로운 상태로 진입합니다.
	virtual void Excute(CUnit* unit);		//상태에서 할 일을 수행합니다.
											
	virtual CState* Exit(CUnit* unit);		//현재 상태에서 퇴장합니다.

public:
	virtual SpriteState GetState() { return SpriteState::state_count; }		//현재의 상태를 반환합니다.
	CGameCommand* GetCommand()  const { return m_command; }
	CSkillCommand* GetSkillCommand() const { return m_skillCommand; }
protected:
	CGameCommand* m_command;
	CSkillCommand* m_skillCommand;
};

/*
기본 상태에 대한 정의를 합니다.
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
이동 상태에 대한 정의를 합니다.
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
공격 상태에 대한 정의를 합니다.

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
스킬 상태에 대한 정의를 합니다.
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
중지 상태에 대한 정의를 합니다.
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
죽은 상태에 대한 정의를 합니다.
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
방어 상태에 대한 정의를 합니다.
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
피격 상태에 대한 정의를 합니다.
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