#pragma once

#include "Unit.h"

class CRuru : public CUnit
{
public:
	CRuru(INDEX idx = { 0, 0 , 0});
	~CRuru();

public:
	virtual void PlayAttackEffect();
	virtual void PlayMoveEffect();


	//virtual void initializeSprite();	//����� �̹����� ���� ������ �����մϴ�.
};