#pragma once
#include "Unit.h"

class CFarm : public CUnit
{
public:
	CFarm(INDEX idx);
	~CFarm();
	
public:
	virtual void PlayAttackEffect();
	virtual void PlayMoveEffect();

	virtual void initializeSprite();	//����� �̹����� ���� ������ �����մϴ�.
	virtual BOOL CheckPlayAttackEffect();
};