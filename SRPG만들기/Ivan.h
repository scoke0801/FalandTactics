#pragma once

#include "Unit.h"

class CIvan : public CUnit
{
public:
	CIvan(INDEX idx = { 0, 0 , 0});
	~CIvan();

public:
	virtual void PlayAttackEffect();
	virtual void PlayMoveEffect();

	//virtual void initializeSprite();	//����� �̹����� ���� ������ �����մϴ�.
};