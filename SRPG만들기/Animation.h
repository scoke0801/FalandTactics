#pragma once
#include "Sprite.h"
#include "state.h"

/*
	class CAnimation
	-4����(��,��,��,��) ���� �ִϸ��̼� Ŭ����
	- �� : ù��° ��
	- �� : �ι�° ��
	- �� : ����° ��
	- �� : �׹�° �� ������ ������ ��������Ʈ�� ��ġ�ؾ��մϴ�.

*/
class CAnimation : public CSpriteImage
{
public:
	CAnimation(LPCTSTR szPath, int w, int h, int start, int end, int reuseSpot = 0, int delay = 8);
	virtual ~CAnimation();
	
	//���� �ʱ�ȭ ���Ŀ� ȣ���Ͽ�, ���� ���⿡ ���� �����ġ�� �����ϵ��� �մϴ�.
	void EndSetState(CUnit* unit);
	void EndSetState(CUnit* unit, BOOL bStop);	//���� ������ ��쿡�� ȣ���Ͽ� ��������Ʈ ����,��ġ�� �����մϴ�. 

	//���¸� ����(�ʱ�ȭ)�մϴ�.
	void Init();				//�ִϸ��̼��� �����ġ�� 0���� �����ϴ�.
	void SetState(SpriteState state, int start, int end);	
	void SetDelay(int delay) { m_nDelay[1] = delay; }
	//������� �κ��� �����մϴ�.
	void SetReusePoint(SpriteState state, int point) ;

	//���ڷ� �Ѱܹ��� ���·� �����մϴ�.
	void Update(CUnit* unit, SpriteState state);	

	virtual void OnUpdate(CUnit* unit);

	//�ִϸ��̼��� ���������� üũ�մϴ�.
	BOOL CheckAnimationEnd(CUnit* unit);

	//Get
	int GetImagePos() const { return m_ptCurrentSpritePos.x; }
private:
	SpriteState   m_currentState;
	
	//�� ���¿� ���� ������ ���۰� �� �̹��� ��ȣ
	int m_iStateArray[2];
	//�̹��� ������ �������� �ִϸ��̼��� �ڿ������� ���̵��� �մϴ�.
	int m_nDelay[2];

	//�ѹ� ����� ���� ���� �� ����� �ʿ��� �� 
	//��𿡼����� ����� �������� ���� ���Ǹ� �մϴ�.
	//�⺻���� 0�̸�, �� �ڿ������� �ִϸ��̼��� ���Ѵٸ� ���� ������ �ʿ��մϴ�.
	int m_nReusePoint;
};