#pragma once

#include "Unit.h"

class CMarcia : public CUnit
{
public:
	CMarcia(INDEX idx = { 0, 0 , 0});
	~CMarcia();

public:
	virtual void PlayAttackEffect();
	virtual void PlayMoveEffect();

	//virtual void initializeSprite();	//����� �̹����� ���� ������ �����մϴ�.
}; 
