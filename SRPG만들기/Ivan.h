#pragma once

#include "Unit.h"

class CIvan : public CUnit
{
public:
	CIvan(INDEX idx = { 0, 0 , 0});
	~CIvan();

public:
	virtual void PlayAttackEffect();
	virtual void PlayMoveEffect();

	//virtual void initializeSprite();	//사용할 이미지에 관한 내용을 설정합니다.
};