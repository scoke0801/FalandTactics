// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <stdio.h>

// C++ 런타임 헤더 파일입니다.
#include <iostream>
#include <fstream>
#include <chrono>
#include <cassert>
#include <vector>
#include <map>

// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.

#include <atlimage.h>
#include <commdlg.h>
#include "Resource.h"
#include "Console.h"
#include "FrameWork.h"

#include "Index.h"
#include "systemImage.h"
#include "enum.h"
#include "Camera.h"

#include "UI.h"
#include "UI_UnitInfo.h"
#include "UI_StageSelect.h"
#include "UI_CommandSelect.h"
#include "UI_Notice.h"
#include "UI_Login.h"
#include "UI_ClearCondition.h"
#include "UI_UnitDeatilInfo.h"
#include "UI_Achievement.h"

#include "profile.h"
#include "achievement.h"

#define CLIENT_WIDTH 1200	//클라이언트 넓이를 지정합니다.
#define CLIENT_HEIGHT 720	//클라이언트 높이를 지정합니다.

#define TILE_WIDTH 64		//타일 한 칸의 넓이를 지정합니다.
#define TILE_HEIGHT 32		//타일 한 칸의 높이를 지정합니다.
#define TILE_WIDTH_HALF 32  //타일 한 칸 넓이의 반을 지정합니다.
#define TILE_HEIGHT_HALF 16 //타일 한 칸 높이의 반을 지정합니다.
#define TITLE_LENGTH	50
#define TILE_GRADIENT   0.5f	//타일에서 두 꼭지점사이의 기울기를 지정합니다.

#define MAX_STAT		255	//유닛의 최대 스텟을 지정합니다.


// 캡션 FPS 출력 여부 -------------------
// 항상 캡션에 FPS를 출력		(0 : 비활성 | 1 : 활성)
#define USE_CAPTIONFPS_ALWAYS	 1

#if USE_CAPTIONFPS_ALWAYS
#define SHOW_CAPTIONFPS 
#elif _DEBUG	// Debug에서는 항상 실행
#define SHOW_CAPTIONFPS 
#endif

#if defined(SHOW_CAPTIONFPS)
#define MAX_UPDATE_FPS 1.0 / 3.0
#endif

 //최대 FPS
#define MAX_FPS 1.0 / 80.0
//#if _DEBUG
//#define MAX_FPS 0.0
//#else
//#define MAX_FPS 1.0 / 60.0
//#endif
//프레임을 따라잡기까지 최대 몇번 루프를 돌 것인지를 지정합니다.
#define MAX_LOOP_TIME 50

//UI_UnitInfo
#define IDC_BUTTON_SelectStage 100
#define IDC_BUTTON_LoadStage   101
#define IDC_BUTTON_EndGame	   102

//UI_StangeSelect
#define IDC_BUTTON_Select	   103
#define IDC_BUTTON_Cancel	   104
#define ID_LISTBOX_Stage	   105

//UI_CommandSelect
#define IDC_BUTTON_Show		   106
#define IDC_BUTTON_TurnEnd	   107
#define IDC_BUTTON_System	   108
#define IDC_BUTTON_UnitInfo    109
#define IDC_BUTTON_UseSkill   110

//UI_DetailSelect
#define IDC_BUTTON_UnitList    111
#define IDC_BUTTON_ClearCondition 112
#define IDC_BUTTON_StageChange 113
#define IDC_BUTTON_GameEnd     114

#define IDC_BUTTON_Explosion   115
#define IDC_BUTTON_FlameBurst  116
#define IDC_BUTTON_Aid		   117
#define IDC_BUTTON_ManaAid     118
#define IDC_BUTTON_Mercy	   119
#define IDC_BUTTON_Resurrection 120
#define IDC_BUTTON_Sacrifice   121
#define IDC_BUTTON_Curse	   122
#define IDC_BUTTON_Hurricane   123
#define IDC_BUTTON_Edge		   124
#define IDC_BUTTON_Thunder     125
#define IDC_BUTTON_EvillEye	   126
#define IDC_BUTTON_ThunderFlare 127
#define IDC_BUTTON_EarthQuake  128
#define IDC_BUTTON_WindBlast   129
//UI_UnitDetailSelect
#define IDC_BUTTON_UnitStat	   201
#define IDC_BUTTON_UnitSkill   202
#define ID_LISTBOX_UnitSkillList 203

//UI_Login
#define IDC_BUTTON_Input		401
#define IDC_BUTTON_Default		402
#define IDE_EDIT_UserName		403