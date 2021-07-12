#pragma once

/*
���ӿ��� ����ϴ� �ֿ� �����͵��� enum class�� ���Ͽ� 
���� / ���� �صα� ���� ��������Դϴ�.
*/
#pragma region States_Enum
typedef enum
{
	state_stop	= 0	//����(�ൿ�� ���� ��)
	, state_idle		//���
	, state_move		//�̵�
	, state_attack		//����
	, state_attacked	//�ǰ�
	, state_defense		//���
	, state_die			//����
	, state_skill		//��ų
	, state_count		//������ ��
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
�ֺ� Ÿ�Ͽ� ���ؼ� �����մϴ�.
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
UI���� ����ϴ� �������� ���ؼ� �����մϴ�.
*/
#pragma region UI
enum class NoticePhase : int
{
	None = 0
	, MoveNotice		//"�̵��� Ÿ���� �������ּ���."
	, AttackPhase       //"������ ������ �������ּ���."
	, UnitWayPhase		//"������ ������ �������ּ���."
	, OnlyAttackPhase
	, AttackedPhase
	, SkillPhase		//"��ų�� ����� ��ġ�� �������ּ���."
	, WaitSkillPhase	//"���⿡ ����Ͻðڽ��ϱ�?"
	, ManaLack			//"������ �����մϴ�."
	, UsingSkillPhase
	, NoActPhase
	, EnemyPhase
	, HealPhase
	, IntervalPhase		//���� ����ȭ������ �Ѿ����
};

enum class UnitInfoPhase : int
{
	None = 0
	, Skill
};
#pragma endregion

/*
�ý��� �̹������� ����ϴ� �������� ���ؼ� �����մϴ�.
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
	, Explosion 	//������ ����		   //Mp 10		
	, FlameBurst	//������ ����		   //Mp 20
	, Aid			//ü��ȸ��			   //Mp 5
	, Mercy			//���ڰ� ��������	   //Mp 10
	, Resurrection  //��Ȱ				   //Mp 15
	, Sacrifice		//��Ȱ				   //Mp 30
	, ManaAid		//����ȸ��			   //Mp 10
	, Curse			//������ ����		   //Mp 10
	, Edge			//������ ����		   //Mp 10
	, Hurricane	    //������ ����		   //Mp 10
	, Thunder       //������ ����		   //Mp 10
	, EvillEye		//������ ����		   //Mp 20
	, Earthquake	//������ ����		   //Mp 20
	, ThunderFlare	//������ ����		   //Mp 20
	, WindBlast		//������ ����		   //Mp 20
};

/*
��ų�� ���ݹ���� ��Ÿ���ϴ�.
*/
enum class SkillAttackType : int	
{
	Contiguous		//���� Ÿ���� �����ϴ� ���
	, Line			//���� Ÿ���� �����ϴ� ���	
};
#pragma endregion

#pragma region ����
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
