#pragma once
#include <Windows.h>
/*
Unit을 나타내는 클래스의 
부모 클래스입니다.
*/
#include "Animation.h"
#include "Rhombus.h"
#include "Tile.h"

class CUnit
{
public:
	CUnit(INDEX idx = { 100, 100, 100 });					//생성자입니다.
	virtual ~CUnit();			//소멸자입니다.

public:							
//상속받은 클래스에서 공통으로 사용할 기능들입니다.
//그리기 관련 함수
	void DrawGrid(HDC hdc, Camera camera = { 0, });		//캐릭터의 충돌범위를 그립니다.
	
	void DrawMovableTile(HDC hdc, Camera camera = { 0, });
	void DrawMovableTile(HDC hdc, INDEX idx, Camera camera = { 0, });
	
	void DrawCurrentPos(HDC hdc, Camera camera = { 0, }); // 공격 Phase에서  이동가능 타일을 전부 그리지 않고, 현재 위치만 그릴 떄 이용합니다.

	void DrawAttackableTile(HDC hdc, Camera camera = { 0, });
	void DrawAttackableTile(HDC hdc, INDEX idx, Camera camrea = { 0, });

	void DrawWayNotice(HDC hdc, Camera camear = { 0, });
	
	void DrawSkill(HDC hdc, Camera camera = { 0, });

	void DrawInterval(HDC hdc, Camera camera = { 0, });

	void OnDraw(HDC hdc, Camera camera = { 0, });		//출력 작업을 해줍니다.

//계산 및 찾기 함수
	int CalculateDamage(CUnit* enemy);	//적에게 입힐 대미지를 계산합니다.
	
	int CalculateSkillDamage(CUnit* enemy); //적에게 입힐 대미지(스킬)를 계산합니다.
	int CalculateHealAmount(CUnit* subject);	//대상에게 입힐 힐의 양을 계산합니다.
	int CalculateMpHealAmount(CUnit* subject);	//대상에게 입힐 마나 힐의 양을 계산합니다.
	int CalculateResurrectionAmount(CUnit* subject);	//대상을 부활 시킬 떄의 회복량을 계산합니다.
	BOOL CheckDeffense();				//방어확률을 계산해서 방어의 경우 TRUE, 아닌 경우에 FALSE를 반환합니다.
	
	UnitWay CheckUnitWay(INDEX curIndex, INDEX nextIndex);	//현재 타일과 다음 타일을 비교해서 캐릭터가 쳐다볼 방향을 지정합니다.
	
	UnitWay CheckUnitWay(POINT input, Camera camera);	//현재 캐릭터의 위치와 인자로 전달받은 인자를 비교해서 캐릭터가 쳐다볼 방향을 지정합니다.

	BOOL CheckIsMovableTile(INDEX idx);	//인자로 넘겨받은 값이 이동가능한 타일인지 확인합니다.
	
	BOOL CheckIsSkillTile(INDEX idx);
	
	BOOL CheckAnimationEnd() { return m_pCurSprite->CheckAnimationEnd(this); }

	BOOL CheckIsAttackableTile(INDEX idx);		//인자로 넘겨받은 값이 공격 가능한 타일인지 확인합니다.

	BOOL CheckSkillEnd();

	BOOL FindSkill(SKillName skill);		//인자로 넘겨받은 스킬이 유닛이 사용가능한 스킬인지 확인합니다.

	BOOL CheckEnemy(CUnit* unit);
	
	void AddMp();

	BOOL CheckTrueDie() { return m_bTrueDie; }

//AI관련
	INDEX FindNearUnit(std::vector <CUnit*>vecUnits, int divison = 0);	//근처의 유닛을 찾아 위치값을 반환합니다.
	INDEX FIndNearUnit(std::vector <CUnit*>vecUnits, INDEX* moveIdx);
	//체력이 낮은,힐 스킬이 필요한 유닛을 탐색합니다.(스킬범위)
	BOOL FindUrgentUnit(CUnit** saveValue);	
	//체력이 낮은, 힐 스킬이 필요한 유닛을 탐색합니다.(이동범위 + 스킬범위)
	BOOL FindUrgentUnit(CUnit** saveValue, CMap* map);
	//죽은, 부활 스킬이 필요한 유닛을 탐색합니다.
	BOOL FindDeadUnit(CUnit** saveValue);		

	//스킬 공격 대상을 탐색합니다.(스킬범위)
	BOOL FindSkillTargetUnit(CUnit **saveValue);
	//스킬 공격 대상을 탐색합니다.(이동범위 + 스킬범위)
	BOOL FindSkillTargetUnit(CUnit** saveValue, CMap* map);

	//기본 공격 대상을 탐색합니다. (현재위치)
	BOOL FindTargetUnit(CUnit** saveValue);
	//기본 공격 대상을 탐색합니다. (이동 범위)
	BOOL FindTargetUnit(CUnit** saveValue, CMap* map);

	//유닛이 이동할 위치를 탐색합니다. (현재위치)
	INDEX FindNextTile(std::vector <CUnit*> vecUnits, CMap* map);

//초기화 함수
	void ClearMovableTile();	//m_mapMovableTile변수의 초기화

	void ClearAttackableTile();	//m_mapAttackableTile변수의 초기화

	void ClearSkillTile();

	void ClearTargetUnit();

//기타 기능
	void Move(INDEX idx);		//캐릭터를 이동시킵니다.
	void Move(POINT point);
	void Jump();				//캐릭터를 폴짝거리게 합니다.
	
	void ReturnToPrevPos();		//이전 위치로 돌아갑니다.
	
	void AddAttackableTile(CTile* tile, INDEX idx);			//인자로 넘겨받은 값을 추가합니다.

	void EnterNextState();

	void AddSkill(SKillName skill);			//인자로 넘겨받은 스킬을 유닛이 사용가능한 스킬에 추가합니다.
	void AddTarget(CUnit* unit);
	BOOL CheckIsTarget(CUnit* unit);
	void FillSkillList(HWND *list);
    //void ClearTargetUnit() { m_vecTargetUnit.clear(); }
	//void ClearNextCommand() { m_vecNextCommand.clear(); }

public:							
//상속받은 클래스에서 재정의가 필요한 기능들입니다.
	virtual void OnUpdate(float timeElapsed);	//갱신 작업을 해줍니다.
	virtual void initializeSprite() {}	//사용할 이미지에 관한 내용을 설정합니다.
	
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

public:	//명령 및 상태에 관한 내용을 정의합니다.
	void HandleInput(KeyInput input);
	void HandleInput(SKillName input);

public: //유닛 정보에 대한 getter 및 setter
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
	//유닛 업적에 관한 get, set
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
	//효과음 추가 및 재생에 관한 내용을 정의합니다.
	void SetSound(CSoundManager* sound) { m_pSound = sound; }
	void AddEffect(char*  szPath, Sound_Name varName);
	void PlayEffect(Sound_Name varName);
	
	virtual void PlayAttackEffect();
	virtual void PlayMoveEffect();
	void PlaySkillEffect();

protected:
	POINT m_ptCurrentPos;		//unit의 좌표를 나타냅니다.(실제위치)
	INDEX m_idxPreTileIndex;		//unit의 이전 위치를 나타냅니다.(인덱스)
	INDEX m_idxCurretTileIndex;	//unit이 현재 어느 타일에 있는지를 나타냅니다.(인덱스)
	INDEX m_idxNextTileIndex;	//unit이 이동할 타일이 어느 타일인지를 나타냅니다.

	std::map< INDEX, Node* >	m_mapMovableTile;	//unit이 이동가능한 타일을 표시합니다.
	std::map< INDEX, CTile* >   m_mapAttackableTile;//unit이 공격가능한 타일을 표시합니다.
	std::map< INDEX, CTile* >   m_mapSkillTile;		//unit이 스킬 공격가능한 타일을 표시합니다.

	//BOOL  m_bGridOn;			//그리드를 그릴 것인지
	
// 유닛 갱신 단위(millisec)
	float				m_fFrequency = 1.0f / 60.0f;	//60분의 1초, 화면 갱신 단위
	float				m_fTick = 0.f;			
	
//그리기 관련 변수
	std::map  <SpriteState, CAnimation* > m_mapSprite;	//그리기 작업을 할 객체를 멤버 변수로 갖도록 합니다.
	CAnimation* m_pCurSprite;
	Camera* m_pCamera;
	int m_nLastDamage;			//마지막에 입은 대미지를 나타냅니다.
	int m_nDeathAngelCount[2];		//죽은 상태에서 머리 위의 천사를 그리기 위한 이미지 위치를 저장합니다.

//유닛 상태에 대한 변수
	CState*			m_pState;	//unit의 상태를 나타냅니다.

//유닛 정보에 대한 변수
	UnitName m_name;			//이미지 출력을 위한 순서를 나타낼 변수
	LPCTSTR m_szName;			//실제 이름을 나타낼 변수

	//float m_fSpeed;				//unit의 이동속도를 나타냅니다.
	int m_nMoveRange;			//unit의 이동거리를 나타냅니다.

	int m_nMaxHp;				//unit의 최대 체력을 나타냅니다.
	int m_nMaxMp;				//unit의 최대 마나를 나타냅니다.

	int m_nHp;				//unit의 현재 체력을 나타냅니다.
	int m_nMp;				//unit의 현재 마나를 나타냅니다.

	int m_nDefense;			//unit의 방어력을 나타냅니다.
	int m_nMagicDefense;	//unit의 마법 방어력을 나타냅니다.

	int m_nStrength;		//unit의 물리 공격력(힘)을 나타냅니다.
	int m_nIntelligence;	//unit의 마법 공격력(지능)을 나타냅니다.

	int m_nAgility;			//unit의 방어 확률(민첩성)을 나타냅니다. 

	LPCTSTR m_szDescription;	//unit에 대한 설명을 나타냅니다.
	UnitTeam m_team;			//unit의 팀을 나타냅니다.

	UnitWay m_way;				//유닛의 방향을 나타냅니다.

	std::vector <SKillName> m_vecSkill;		//유닛이 사용 가능한 스킬을 나타냅니다.
	SKillName m_curSkill;					//유닛이 현재 사용할 스킬을 나타냅니다.

//유닛 행동 가능여부에 대한 변수
	BOOL m_bCanAct;				//공격 or 스킬 사용이 가능한 지를 나타낼 변수
	BOOL m_bCanMove;			//이동이 가능한 지를 나타낼 변수
	CScene* m_pStage;			//유닛이 현재 있는 스테이지를 나타냅니다.

//유닛 행동 관련 변수
	std::vector <CUnit*> m_vecTargetUnit;
	KeyInput m_curCommand;
	KeyInput m_nextCommand;
	CState* m_nextState;
	UnitWay m_nextWay;

//유닛 죽음 관련, 적군 유닛 한정
	BOOL m_bTrueDie;
	short m_chAlpha;

//유닛 업적 관련
	BOOL m_bHit;				//유닛이 이전에 맞은 적이 있는가
	BOOL m_bDie;				//유닛이 이전에 죽은 적이 있는가
	short m_nKillNum;			//유닛이 처치한 적 수
	short m_nResurrectionNum;	//유닛이 부활시킨 수

//사운드
	CSoundManager* m_pSound;
};