#pragma once
#include <Windows.h>
/*
Unit�� ��Ÿ���� Ŭ������ 
�θ� Ŭ�����Դϴ�.
*/
#include "Animation.h"
#include "Rhombus.h"
#include "Tile.h"

class CUnit
{
public:
	CUnit(INDEX idx = { 100, 100, 100 });					//�������Դϴ�.
	virtual ~CUnit();			//�Ҹ����Դϴ�.

public:							
//��ӹ��� Ŭ�������� �������� ����� ��ɵ��Դϴ�.
//�׸��� ���� �Լ�
	void DrawGrid(HDC hdc, Camera camera = { 0, });		//ĳ������ �浹������ �׸��ϴ�.
	
	void DrawMovableTile(HDC hdc, Camera camera = { 0, });
	void DrawMovableTile(HDC hdc, INDEX idx, Camera camera = { 0, });
	
	void DrawCurrentPos(HDC hdc, Camera camera = { 0, }); // ���� Phase����  �̵����� Ÿ���� ���� �׸��� �ʰ�, ���� ��ġ�� �׸� �� �̿��մϴ�.

	void DrawAttackableTile(HDC hdc, Camera camera = { 0, });
	void DrawAttackableTile(HDC hdc, INDEX idx, Camera camrea = { 0, });

	void DrawWayNotice(HDC hdc, Camera camear = { 0, });
	
	void DrawSkill(HDC hdc, Camera camera = { 0, });

	void DrawInterval(HDC hdc, Camera camera = { 0, });

	void OnDraw(HDC hdc, Camera camera = { 0, });		//��� �۾��� ���ݴϴ�.

//��� �� ã�� �Լ�
	int CalculateDamage(CUnit* enemy);	//������ ���� ������� ����մϴ�.
	
	int CalculateSkillDamage(CUnit* enemy); //������ ���� �����(��ų)�� ����մϴ�.
	int CalculateHealAmount(CUnit* subject);	//��󿡰� ���� ���� ���� ����մϴ�.
	int CalculateMpHealAmount(CUnit* subject);	//��󿡰� ���� ���� ���� ���� ����մϴ�.
	int CalculateResurrectionAmount(CUnit* subject);	//����� ��Ȱ ��ų ���� ȸ������ ����մϴ�.
	BOOL CheckDeffense();				//���Ȯ���� ����ؼ� ����� ��� TRUE, �ƴ� ��쿡 FALSE�� ��ȯ�մϴ�.
	
	UnitWay CheckUnitWay(INDEX curIndex, INDEX nextIndex);	//���� Ÿ�ϰ� ���� Ÿ���� ���ؼ� ĳ���Ͱ� �Ĵٺ� ������ �����մϴ�.
	
	UnitWay CheckUnitWay(POINT input, Camera camera);	//���� ĳ������ ��ġ�� ���ڷ� ���޹��� ���ڸ� ���ؼ� ĳ���Ͱ� �Ĵٺ� ������ �����մϴ�.

	BOOL CheckIsMovableTile(INDEX idx);	//���ڷ� �Ѱܹ��� ���� �̵������� Ÿ������ Ȯ���մϴ�.
	
	BOOL CheckIsSkillTile(INDEX idx);
	
	BOOL CheckAnimationEnd() { return m_pCurSprite->CheckAnimationEnd(this); }

	BOOL CheckIsAttackableTile(INDEX idx);		//���ڷ� �Ѱܹ��� ���� ���� ������ Ÿ������ Ȯ���մϴ�.

	BOOL CheckSkillEnd();

	BOOL FindSkill(SKillName skill);		//���ڷ� �Ѱܹ��� ��ų�� ������ ��밡���� ��ų���� Ȯ���մϴ�.

	BOOL CheckEnemy(CUnit* unit);
	
	void AddMp();

	BOOL CheckTrueDie() { return m_bTrueDie; }

//AI����
	INDEX FindNearUnit(std::vector <CUnit*>vecUnits, int divison = 0);	//��ó�� ������ ã�� ��ġ���� ��ȯ�մϴ�.
	INDEX FIndNearUnit(std::vector <CUnit*>vecUnits, INDEX* moveIdx);
	//ü���� ����,�� ��ų�� �ʿ��� ������ Ž���մϴ�.(��ų����)
	BOOL FindUrgentUnit(CUnit** saveValue);	
	//ü���� ����, �� ��ų�� �ʿ��� ������ Ž���մϴ�.(�̵����� + ��ų����)
	BOOL FindUrgentUnit(CUnit** saveValue, CMap* map);
	//����, ��Ȱ ��ų�� �ʿ��� ������ Ž���մϴ�.
	BOOL FindDeadUnit(CUnit** saveValue);		

	//��ų ���� ����� Ž���մϴ�.(��ų����)
	BOOL FindSkillTargetUnit(CUnit **saveValue);
	//��ų ���� ����� Ž���մϴ�.(�̵����� + ��ų����)
	BOOL FindSkillTargetUnit(CUnit** saveValue, CMap* map);

	//�⺻ ���� ����� Ž���մϴ�. (������ġ)
	BOOL FindTargetUnit(CUnit** saveValue);
	//�⺻ ���� ����� Ž���մϴ�. (�̵� ����)
	BOOL FindTargetUnit(CUnit** saveValue, CMap* map);

	//������ �̵��� ��ġ�� Ž���մϴ�. (������ġ)
	INDEX FindNextTile(std::vector <CUnit*> vecUnits, CMap* map);

//�ʱ�ȭ �Լ�
	void ClearMovableTile();	//m_mapMovableTile������ �ʱ�ȭ

	void ClearAttackableTile();	//m_mapAttackableTile������ �ʱ�ȭ

	void ClearSkillTile();

	void ClearTargetUnit();

//��Ÿ ���
	void Move(INDEX idx);		//ĳ���͸� �̵���ŵ�ϴ�.
	void Move(POINT point);
	void Jump();				//ĳ���͸� ��¦�Ÿ��� �մϴ�.
	
	void ReturnToPrevPos();		//���� ��ġ�� ���ư��ϴ�.
	
	void AddAttackableTile(CTile* tile, INDEX idx);			//���ڷ� �Ѱܹ��� ���� �߰��մϴ�.

	void EnterNextState();

	void AddSkill(SKillName skill);			//���ڷ� �Ѱܹ��� ��ų�� ������ ��밡���� ��ų�� �߰��մϴ�.
	void AddTarget(CUnit* unit);
	BOOL CheckIsTarget(CUnit* unit);
	void FillSkillList(HWND *list);
    //void ClearTargetUnit() { m_vecTargetUnit.clear(); }
	//void ClearNextCommand() { m_vecNextCommand.clear(); }

public:							
//��ӹ��� Ŭ�������� �����ǰ� �ʿ��� ��ɵ��Դϴ�.
	virtual void OnUpdate(float timeElapsed);	//���� �۾��� ���ݴϴ�.
	virtual void initializeSprite() {}	//����� �̹����� ���� ������ �����մϴ�.
	
	virtual BOOL CheckPlaySkillEffect(); 
	virtual BOOL CheckPlayAttackEffect(); 

	void SkillSpriteUpdate(float timeElapsed);

public:	//get, set
	UnitWay GetUnitWay() const { return m_way; }
	
	CState*	GetState() const { return m_pState; }
	
	INDEX GetCurrentIndex() const { return m_idxCurretTileIndex; }
	INDEX GetNextTileIndex() const { return m_idxNextTileIndex; }
	INDEX GetPrevTileIndex() const { return m_idxPreTileIndex; }
	
	POINT GetUnitPos() const { return m_ptCurrentPos; }
	
	UnitName GetUnitName() const { return m_name; }
	UnitTeam GetUnitTeam() const { return m_team; }
	
	std::map< INDEX, Node* > GetMovableTile() const { return m_mapMovableTile; }
	
	KeyInput GetNextCommand() const;
	KeyInput GetCurrentCommand() const { return m_curCommand; }
	
	CUnit* GetTargetUnit(int index) const;
	std::vector<CUnit*> GetTargetUnit() const { return m_vecTargetUnit; }
	UnitWay GetNextUnitWay() const { return m_nextWay; }

	BOOL GetCanAttack() const { return m_bCanAct; }
	BOOL GetCanMove() const { return m_bCanMove; }

	Camera* GetCamera() const { return m_pCamera; }

	CScene* GetStage() const { return m_pStage; }

	int GetLastDamage() const { return m_nLastDamage; }

	int GetDeathAngelCount() const { return m_nDeathAngelCount[1]; }
	
	SKillName GetCurrentSkill() const { return m_curSkill; }
	CState* GetNextState() const { return m_nextState; }
	void SetState(CState* state) { m_pState = state; }
	void SetState(SpriteState state);

	void SetCurrentPos(POINT pos) { m_ptCurrentPos = pos; }
	void SetCurrentTile(INDEX index) { m_idxCurretTileIndex = index; }
	void SetPrevTile(INDEX index) { m_idxPreTileIndex = index; }
	void SetNextTile(INDEX index) { m_idxNextTileIndex = index; }
	
	void SetUnitWay(UnitWay way); 
	//void SetGrid(BOOL value) { m_bGridOn = value; }

	void SetMovableTile(std::map < INDEX, Node* > map);
	
	void SetSkillTile(std::map < INDEX, CTile* > map);
	void SetSkillPos(POINT pos);
	void SetCurrentSkill(SKillName name) { m_curSkill = name; }

	void SetCanAct(BOOL canAct) { m_bCanAct = canAct; }
	void SetCanMove(BOOL canMove) { m_bCanMove = canMove; }

	void SetTargetUnit(CUnit* target);
	void SetSkillTarget();

	void SetCurrentCommand(KeyInput command) { m_curCommand = command; }
	void SetNextCommand(KeyInput command) { m_nextCommand = command; }

	void SetNextUnitWay(UnitWay way) { m_nextWay = way; }

	void SetCamera(Camera* camera) { m_pCamera = camera; }

	void SetStage(CScene* stage) { m_pStage = stage; }

	void SetLastDamage(int damage) { m_nLastDamage = damage; }

public:	//��� �� ���¿� ���� ������ �����մϴ�.
	void HandleInput(KeyInput input);
	void HandleInput(SKillName input);

public: //���� ������ ���� getter �� setter
	LPCTSTR GetName() const { return m_szName; }

	int GetStrength() const { return m_nStrength; }
	
	int GetIntelligence() const { return m_nIntelligence; }
	
	int GetDefense() const { return m_nDefense; }
	
	int GetMagicDefense() const { return m_nMagicDefense; }
	
	int GetAgility() const { return m_nAgility; }
	
	int GetMaxHp() const { return m_nMaxHp; }
	int GetMaxMp() const { return m_nMaxMp; }
	
	int GetHp() const { return m_nHp; }
	int GetMp() const { return m_nMp; }

	int GetMoveRange() const { return m_nMoveRange; }

	int GetSkillNum() const { return (int)m_vecSkill.size(); }

	LPCTSTR GetUnitDescription() { return m_szDescription; }

	void SetStrength(int strength) { m_nStrength = strength; }

	void SetIntelligence(int intelligence) { m_nIntelligence = intelligence; }

	void SetDefense(int defense) { m_nDefense = defense; }

	void SetMagicDefense(int magicDefense) { m_nMagicDefense = magicDefense; }

	void SetAgility(int agility) { m_nAgility = agility; }

	void SetMaxHp(int maxHp) { m_nMaxHp = maxHp; }
	void SetMaxMp(int maxMp) { m_nMaxMp = maxMp; }
	void SetHp(int hp) { m_nHp = hp; }
	void SetMp(int mp) { m_nMp = mp; }

	void SetMoveRange(int moveRange) { m_nMoveRange = moveRange; }

	void SetDeathAngelCount(int count) { m_nDeathAngelCount[1] = count; }

	void SetTeam(UnitTeam team) { m_team = team; }

	void ClearSkillList();

public:
	//���� ������ ���� get, set
	void SetHitted(BOOL value) { m_bHit = value; }
	BOOL GetHitted() const { return m_bHit; }

	void SetDied(BOOL value) { m_bDie = value; }	
	BOOL GetDied() const { return m_bDie; }

	void IncreaseKillNum(short num) { m_nKillNum += num; }
	void IncreaseKillNum() { ++m_nKillNum; }
	short GetKillNum() const { return m_nKillNum; }

	void IncreaseResurrectionNum(short num) { m_nResurrectionNum += num; }
	void IncreaseResurrectionNum() { ++m_nResurrectionNum; }
	short GetResurrectionNum() const { return m_nResurrectionNum; }

public:
	//ȿ���� �߰� �� ����� ���� ������ �����մϴ�.
	void SetSound(CSoundManager* sound) { m_pSound = sound; }
	void AddEffect(char*  szPath, Sound_Name varName);
	void PlayEffect(Sound_Name varName);
	
	virtual void PlayAttackEffect();
	virtual void PlayMoveEffect();
	void PlaySkillEffect();

protected:
	POINT m_ptCurrentPos;		//unit�� ��ǥ�� ��Ÿ���ϴ�.(������ġ)
	INDEX m_idxPreTileIndex;		//unit�� ���� ��ġ�� ��Ÿ���ϴ�.(�ε���)
	INDEX m_idxCurretTileIndex;	//unit�� ���� ��� Ÿ�Ͽ� �ִ����� ��Ÿ���ϴ�.(�ε���)
	INDEX m_idxNextTileIndex;	//unit�� �̵��� Ÿ���� ��� Ÿ�������� ��Ÿ���ϴ�.

	std::map< INDEX, Node* >	m_mapMovableTile;	//unit�� �̵������� Ÿ���� ǥ���մϴ�.
	std::map< INDEX, CTile* >   m_mapAttackableTile;//unit�� ���ݰ����� Ÿ���� ǥ���մϴ�.
	std::map< INDEX, CTile* >   m_mapSkillTile;		//unit�� ��ų ���ݰ����� Ÿ���� ǥ���մϴ�.

	//BOOL  m_bGridOn;			//�׸��带 �׸� ������
	
// ���� ���� ����(millisec)
	float				m_fFrequency = 1.0f / 60.0f;	//60���� 1��, ȭ�� ���� ����
	float				m_fTick = 0.f;			
	
//�׸��� ���� ����
	std::map  <SpriteState, CAnimation* > m_mapSprite;	//�׸��� �۾��� �� ��ü�� ��� ������ ������ �մϴ�.
	CAnimation* m_pCurSprite;
	Camera* m_pCamera;
	int m_nLastDamage;			//�������� ���� ������� ��Ÿ���ϴ�.
	int m_nDeathAngelCount[2];		//���� ���¿��� �Ӹ� ���� õ�縦 �׸��� ���� �̹��� ��ġ�� �����մϴ�.

//���� ���¿� ���� ����
	CState*			m_pState;	//unit�� ���¸� ��Ÿ���ϴ�.

//���� ������ ���� ����
	UnitName m_name;			//�̹��� ����� ���� ������ ��Ÿ�� ����
	LPCTSTR m_szName;			//���� �̸��� ��Ÿ�� ����

	//float m_fSpeed;				//unit�� �̵��ӵ��� ��Ÿ���ϴ�.
	int m_nMoveRange;			//unit�� �̵��Ÿ��� ��Ÿ���ϴ�.

	int m_nMaxHp;				//unit�� �ִ� ü���� ��Ÿ���ϴ�.
	int m_nMaxMp;				//unit�� �ִ� ������ ��Ÿ���ϴ�.

	int m_nHp;				//unit�� ���� ü���� ��Ÿ���ϴ�.
	int m_nMp;				//unit�� ���� ������ ��Ÿ���ϴ�.

	int m_nDefense;			//unit�� ������ ��Ÿ���ϴ�.
	int m_nMagicDefense;	//unit�� ���� ������ ��Ÿ���ϴ�.

	int m_nStrength;		//unit�� ���� ���ݷ�(��)�� ��Ÿ���ϴ�.
	int m_nIntelligence;	//unit�� ���� ���ݷ�(����)�� ��Ÿ���ϴ�.

	int m_nAgility;			//unit�� ��� Ȯ��(��ø��)�� ��Ÿ���ϴ�. 

	LPCTSTR m_szDescription;	//unit�� ���� ������ ��Ÿ���ϴ�.
	UnitTeam m_team;			//unit�� ���� ��Ÿ���ϴ�.

	UnitWay m_way;				//������ ������ ��Ÿ���ϴ�.

	std::vector <SKillName> m_vecSkill;		//������ ��� ������ ��ų�� ��Ÿ���ϴ�.
	SKillName m_curSkill;					//������ ���� ����� ��ų�� ��Ÿ���ϴ�.

//���� �ൿ ���ɿ��ο� ���� ����
	BOOL m_bCanAct;				//���� or ��ų ����� ������ ���� ��Ÿ�� ����
	BOOL m_bCanMove;			//�̵��� ������ ���� ��Ÿ�� ����
	CScene* m_pStage;			//������ ���� �ִ� ���������� ��Ÿ���ϴ�.

//���� �ൿ ���� ����
	std::vector <CUnit*> m_vecTargetUnit;
	KeyInput m_curCommand;
	KeyInput m_nextCommand;
	CState* m_nextState;
	UnitWay m_nextWay;

//���� ���� ����, ���� ���� ����
	BOOL m_bTrueDie;
	short m_chAlpha;

//���� ���� ����
	BOOL m_bHit;				//������ ������ ���� ���� �ִ°�
	BOOL m_bDie;				//������ ������ ���� ���� �ִ°�
	short m_nKillNum;			//������ óġ�� �� ��
	short m_nResurrectionNum;	//������ ��Ȱ��Ų ��

//����
	CSoundManager* m_pSound;
};