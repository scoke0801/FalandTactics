#pragma once

#include "Unit.h"

class CAris : public CUnit
{
public:
	CAris(INDEX idx = { 0, 0 , 0});
	~CAris();

public:
	virtual void PlayAttackEffect();
	virtual void PlayMoveEffect();

	//virtual void initializeSprite();	//����� �̹����� ���� ������ �����մϴ�.
};