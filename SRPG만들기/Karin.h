#pragma once
#include "Unit.h"

class CKarin : public CUnit
{
public:
	CKarin(INDEX idx = { 100, 100,0 });
	~CKarin();
	
public:
	virtual void PlayAttackEffect();
	virtual void PlayMoveEffect();

	virtual void initializeSprite();	//����� �̹����� ���� ������ �����մϴ�.
};