#pragma once

#include "Unit.h"

class CArl : public CUnit
{
public:
	CArl(INDEX idx = { 0, 0 , 0});
	~CArl();

public:
	virtual void PlayAttackEffect();
	virtual void PlayMoveEffect();

	//virtual void initializeSprite();	//사용할 이미지에 관한 내용을 설정합니다.
};