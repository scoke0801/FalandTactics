#pragma once

#include "Unit.h"

class CReon : public CUnit
{
public:
	CReon(INDEX idx = { 0, 0, 0 });
	~CReon();

public:
	virtual void PlayMoveEffect();
	virtual void PlayAttackEffect();
	//virtual void initializeSprite();	//사용할 이미지에 관한 내용을 설정합니다.
};