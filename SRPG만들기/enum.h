#pragma once

#pragma region Sound_Enum


#pragma endregion

#pragma region States_Enum
typedef enum
{
	state_stop	= 0	//정지(행동이 끝난 후)
	, state_idle		//대기
	, state_move		//이동
	, state_attack		//공격
	, state_attacked	//피격
	, state_defense		//방어
	, state_die			//죽음
	, state_skill		//스킬
	, state_count		//상태의 수
}SpriteState;

enum class KeyInput : int
{
	Move = 0
	, Attack
	, Skill
	, Stop
	, Idle
	, Die
	, Attacked
	, Defense
	, Heal
};


#pragma endregion

#pragma region Unit
enum class UnitName : int
{
	Aris = 0
	, Arl
	, Cat
	, Catherine
	, Crab
	, Fairy
	, Farm
	, Ivan
	, Karin
	, YoungKarin
	, BlackKnight
	, Marcia
	, Reon
	, Rian
	, Rucia
	, Ruru
	, Shon
	, Wolf
};
enum class UnitWay : int
{
	LeftDown = 0
	, RightDown
	, LeftUp
	, RightUp
};

enum class UnitTeam : int
{
	East = 0
	, West
	, South
	, North
};
#pragma endregion

/*
주변 타일에 대해서 정의합니다.
*/
#pragma region Contiguous_Tile
typedef enum
{
	LeftUp = 0
	, RightUp
	, LeftDown
	, RightDown
}ContiguousTile;
#pragma endregion 

typedef struct _point
{
	int x;
	int y;
}Line;

/*
UI에서 사용하는 열거형에 대해서 정의합니다.
*/
#pragma region UI
enum class NoticePhase : int
{
	None = 0
	, MoveNotice		//"이동할 타일을 선택해주세요."
	, AttackPhase       //"공격할 유닛을 선택해주세요."
	, UnitWayPhase		//"유닛의 방향을 선택해주세요."
	, OnlyAttackPhase
	, AttackedPhase
	, SkillPhase		//"스킬을 사용할 위치를 지정해주세요."
	, WaitSkillPhase	//"여기에 사용하시겠습니까?"
	, ManaLack			//"마나가 부족합니다."
	, UsingSkillPhase
	, NoActPhase
	, EnemyPhase
	, HealPhase
	, IntervalPhase		//게임 엔딩화면으로 넘어가기전
};

enum class UnitInfoPhase : int
{
	None = 0
	, Skill
};
#pragma endregion

/*
시스템 이미지에서 사용하는 열겨형에 대해서 정의합니다.
*/
#pragma region SystemImage
enum class DamageTeam : int
{
	AllyDagmage
	, EnemyDamage
};
#pragma endregion

#pragma region Skill
enum class SKillName : int
{
	None = -1
	, Explosion 	//십자형 공격		   //Mp 10		
	, FlameBurst	//일자형 공격		   //Mp 20
	, Aid			//체력회복			   //Mp 5
	, Mercy			//십자가 범위힐링	   //Mp 10
	, Resurrection  //부활				   //Mp 15
	, Sacrifice		//부활				   //Mp 30
	, ManaAid		//마나회복			   //Mp 10
	, Curse			//십자형 공격		   //Mp 10
	, Edge			//십자형 공격		   //Mp 10
	, Hurricane	    //십자형 공격		   //Mp 10
	, Thunder       //십자형 공격		   //Mp 10
	, EvillEye		//일자형 공격		   //Mp 20
	, Earthquake	//일자형 공격		   //Mp 20
	, ThunderFlare	//일자형 공격		   //Mp 20
	, WindBlast		//일자형 공격		   //Mp 20
};

/*
스킬의 공격방식을 나타냅니다.
*/
enum class SkillAttackType : int	
{
	Contiguous		//인접 타일을 공격하는 방식
	, Line			//직선 타일을 공격하는 방식	
};
#pragma endregion

#pragma region 업적
typedef enum _Achieve
{
	None = 0
	, NumerousEnemyKill
	, AllStageClear
	, NoKillClear
	, OneShotOneKill
	, OneUnitAllKill
	, Defeat3
	, Accumulation1000
	, Berserk
	, Achievement10
	, Resurrection4
	, AllAchievement
	, NewPlayer
	, AllSurviveClear
	, FirstClear
	, FirstDefeat
	, Retry
	, ReConnect
	, Achievement_Count
}Achievement;

#pragma endregion
