#pragma once

#include "Unit.h"

class CFairy : public CUnit
{
public:
	CFairy(INDEX idx = { 0, 0 , 0});
	~CFairy();

public:
	virtual void PlayAttackEffect();
	virtual void PlayMoveEffect();

	//virtual void initializeSprite();	//����� �̹����� ���� ������ �����մϴ�.
};