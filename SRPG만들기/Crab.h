#pragma once

#include "Unit.h"

class CCrab : public CUnit
{
public:
	CCrab(INDEX idx = { 0, 0, 0});
	~CCrab();

public:
	virtual void PlayAttackEffect();
	virtual void PlayMoveEffect();

	//virtual void initializeSprite();	//사용할 이미지에 관한 내용을 설정합니다.
};