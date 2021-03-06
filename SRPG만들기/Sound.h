#pragma once

#pragma comment (lib, "fmod64_vc.lib")

#include <fmod.hpp>
#include <fmod_errors.h>


/*
사운드 재생 관련된 내용을 정의할 클래스입니다.

기본적으로 BGM, EFFECT를 나눠서 구현하도록 하는데,
BGM은 AddStream을 통해 추가하도록 하며
다른 사운드는 AddSound를 통해 추가하도록 합니다.

CFrameWork의 멤버 변수로 CSoundManager 클래스를 추가하여
필요한 경우에 프레임 워크를 통해서 접근하도록 합니다.

또는
CScene의 멤버 변수로 CSoundManager 클래스를 추가하여
필요한 경우에 각 장면에서 접근하도록 합니다.

추가적인 부분은 나중에...
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
public:		//생성자, 소멸자
	CSoundManager();
	~CSoundManager();

public:		//사운드 추가
	void AddStream(char* szPath, Sound_Name varName);	//배경음악을 추가합니다.
	void AddSound(char* szPath, Sound_Name varName);	//효과음을 추가합니다.

public:		//사운드 재생
	void OnUpdate();					//사운드 재생이 끊기지 않도록 합니다.

	void PlayBgm(Sound_Name varName);		//배경음악을 재생합니다.
	void PlayEffect(Sound_Name varName);	//효과음을 재생합니다.

	void Stop();		//사운드 재생을 중지합니다.
	void SetVolume(float volume);	//사운드의 크기를 조절합니다.
public:		//기타
	FMOD::Sound* FindSound(Sound_Name key);	//해당 키 값이 이미 등록 되어 있는지를 찾습니다.
private:
	float m_fVolume;	//사운드 재생할 때의 크기를 지정합니다.

	FMOD::System* m_pSystem;
	FMOD::Channel* m_pChannel[SoundType::SOUND_COUNT];

	unsigned int    version;
	std::map <Sound_Name, FMOD::Sound* > m_mapSound;
};