#pragma once
#include "Unit.h"

class CFarm : public CUnit
{
public:
	CFarm(INDEX idx);
	~CFarm();
	
public:
	virtual void PlayAttackEffect();
	virtual void PlayMoveEffect();

	virtual void initializeSprite();	//사용할 이미지에 관한 내용을 설정합니다.
	virtual BOOL CheckPlayAttackEffect();
};