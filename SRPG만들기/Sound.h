#pragma once

#pragma comment (lib, "fmod64_vc.lib")

#include <fmod.hpp>
#include <fmod_errors.h>


/*
���� ��� ���õ� ������ ������ Ŭ�����Դϴ�.

�⺻������ BGM, EFFECT�� ������ �����ϵ��� �ϴµ�,
BGM�� AddStream�� ���� �߰��ϵ��� �ϸ�
�ٸ� ����� AddSound�� ���� �߰��ϵ��� �մϴ�.

CFrameWork�� ��� ������ CSoundManager Ŭ������ �߰��Ͽ�
�ʿ��� ��쿡 ������ ��ũ�� ���ؼ� �����ϵ��� �մϴ�.

�Ǵ�
CScene�� ��� ������ CSoundManager Ŭ������ �߰��Ͽ�
�ʿ��� ��쿡 �� ��鿡�� �����ϵ��� �մϴ�.

�߰����� �κ��� ���߿�...
*/

typedef enum
{
	SOUND_BGM = 0
	, SOUND_EFFECT
	, SOUND_COUNT
}SoundType;

enum class Sound_Name : int
{
	BGM_TITLE = 0
	, BGM_STAGE1
	, BGM_STAGE2
	, BGM_STAGE3
	, BGM_STAGE4
	, BGM_STAGE5
	, BGM_STAGE6
	, BGM_STAGE_USER
	, BGM_GAME_LOSE
	, BGM_GAME_WIN
	, EFFECT_MOVE_GROUND
	, EFFECT_MOVE_FLY
	, EFFECT_STICK_ATTACK
	, EFFECT_STICK_SWING
	, EFFECT_SWORD_ATTACK
	, EFFECT_HAND_ATTACK
	, EFFECT_NEW_TURN
	, EFFECT_BURST
	, EFFECT_AID
	, EFFECT_RESURRECTION
	, EFFECT_THUNDER
	, EFFECT_HURRICANE
	, EFFECT_EDGE
	, EFFECT_CURSE
};

class CSoundManager
{
public:		//������, �Ҹ���
	CSoundManager();
	~CSoundManager();

public:		//���� �߰�
	void AddStream(char* szPath, Sound_Name varName);	//��������� �߰��մϴ�.
	void AddSound(char* szPath, Sound_Name varName);	//ȿ������ �߰��մϴ�.

public:		//���� ���
	void OnUpdate();					//���� ����� ������ �ʵ��� �մϴ�.

	void PlayBgm(Sound_Name varName);		//��������� ����մϴ�.
	void PlayEffect(Sound_Name varName);	//ȿ������ ����մϴ�.

	void Stop();		//���� ����� �����մϴ�.
	void SetVolume(float volume);	//������ ũ�⸦ �����մϴ�.
public:		//��Ÿ
	FMOD::Sound* FindSound(Sound_Name key);	//�ش� Ű ���� �̹� ��� �Ǿ� �ִ����� ã���ϴ�.
private:
	float m_fVolume;	//���� ����� ���� ũ�⸦ �����մϴ�.

	FMOD::System* m_pSystem;
	FMOD::Channel* m_pChannel[SoundType::SOUND_COUNT];

	unsigned int    version;
	std::map <Sound_Name, FMOD::Sound* > m_mapSound;
};