#pragma once

#include "Unit.h"

class CRian : public CUnit
{
public:
	CRian(INDEX idx = { 0, 0 , 0});
	~CRian();

public:
	virtual void PlayAttackEffect();
	virtual void PlayMoveEffect();

	virtual void initializeSprite();	//����� �̹����� ���� ������ �����մϴ�.
};