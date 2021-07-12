#pragma once

#include "Unit.h"

class CCat : public CUnit
{
public:
	CCat(INDEX idx = { 0, 0, 0 });
	~CCat();

public:
	virtual void PlayAttackEffect();
	virtual void PlayMoveEffect();
	virtual BOOL CheckPlayAttackEffect();
	//virtual void initializeSprite();	//사용할 이미지에 관한 내용을 설정합니다.
};