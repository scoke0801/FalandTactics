#pragma once

#include "Unit.h"

class CCatherine : public CUnit
{
public:
	CCatherine(INDEX idx = { 0, 0 , 0});
	~CCatherine();
public:
	virtual void PlayAttackEffect();
	virtual void PlayMoveEffect();

	//virtual void initializeSprite();	//����� �̹����� ���� ������ �����մϴ�.
};