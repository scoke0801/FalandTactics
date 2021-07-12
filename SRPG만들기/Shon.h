#pragma once

#include "Unit.h"

class CShon : public CUnit
{
public:
	CShon(INDEX idx = { 0, 0 , 0});
	~CShon();

public:
	virtual void PlayAttackEffect();
	virtual void PlayMoveEffect();

	//virtual void initializeSprite();	//사용할 이미지에 관한 내용을 설정합니다.
};
