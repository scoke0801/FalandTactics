#pragma once

#include "Unit.h"

class CCat : public CUnit
{
public:
	CCat(INDEX idx = { 0, 0, 0 });
	~CCat();

public:
	virtual void PlayAttackEffect();
	virtual void PlayMoveEffect();
	virtual BOOL CheckPlayAttackEffect();
	//virtual void initializeSprite();	//����� �̹����� ���� ������ �����մϴ�.
};