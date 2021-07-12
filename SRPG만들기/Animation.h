#pragma once
#include "Sprite.h"
#include "state.h"

/*
	class CAnimation
	-4방향(↖,↗,↙,↘) 기준 애니메이션 클래스
	- ↙ : 첫번째 줄
	- ↘ : 두번째 줄
	- ↖ : 세번째 줄
	- ↗ : 네번째 줄 순으로 오도록 스프라이트를 배치해야합니다.

*/
class CAnimation : public CSpriteImage
{
public:
	CAnimation(LPCTSTR szPath, int w, int h, int start, int end, int reuseSpot = 0, int delay = 8);
	virtual ~CAnimation();
	
	//상태 초기화 이후에 호출하여, 유닛 방향에 따라 출력위치를 조절하도록 합니다.
	void EndSetState(CUnit* unit);
	void EndSetState(CUnit* unit, BOOL bStop);	//정지 상태의 경우에만 호출하여 스프라이트 상태,위치를 조절합니다. 

	//상태를 설정(초기화)합니다.
	void Init();				//애니메이션의 출력위치를 0으로 돌립니다.
	void SetState(SpriteState state, int start, int end);	
	void SetDelay(int delay) { m_nDelay[1] = delay; }
	//재출력할 부분을 설정합니다.
	void SetReusePoint(SpriteState state, int point) ;

	//인자로 넘겨받은 상태로 전이합니다.
	void Update(CUnit* unit, SpriteState state);	

	virtual void OnUpdate(CUnit* unit);

	//애니메이션이 끝났는지를 체크합니다.
	BOOL CheckAnimationEnd(CUnit* unit);

	//Get
	int GetImagePos() const { return m_ptCurrentSpritePos.x; }
private:
	SpriteState   m_currentState;
	
	//각 상태에 따른 상태의 시작과 끝 이미지 번호
	int m_iStateArray[2];
	//이미지 증가를 지연시켜 애니메이션이 자연스럽게 보이도록 합니다.
	int m_nDelay[2];

	//한번 출력이 끝난 이후 재 출력이 필요할 때 
	//어디에서부터 출력할 것인지에 대한 정의를 합니다.
	//기본값은 0이며, 더 자연스러운 애니메이션을 원한다면 따로 설정이 필요합니다.
	int m_nReusePoint;
};