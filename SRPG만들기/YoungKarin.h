#pragma once
#include "Unit.h"

class CYoungKarin : public CUnit
{
public:
	CYoungKarin(INDEX idx = { 100, 100,0 });
	~CYoungKarin();
public:
	virtual void PlayAttackEffect();
	virtual void PlayMoveEffect();

	virtual void initializeSprite();	//����� �̹����� ���� ������ �����մϴ�.
};