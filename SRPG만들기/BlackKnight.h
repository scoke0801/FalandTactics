#pragma once

#include "Unit.h"

class CBlackKnight : public CUnit
{
public:
	CBlackKnight(INDEX idx = { 0, 0 , 0});
	~CBlackKnight();

public:
	virtual void PlayAttackEffect();
	virtual void PlayMoveEffect();
	//virtual void initializeSprite();	//����� �̹����� ���� ������ �����մϴ�.
};