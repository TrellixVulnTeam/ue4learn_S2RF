#pragma once

#include "ModelDefine.h"

const TMap<MODEL_PART_TYPE, FName> ModelPartType_To_SockName = {
	{MODEL_PART_TYPE::MODEL_PART_LWEAPON, TEXT("Socket_Weapon_L")},
	{MODEL_PART_TYPE::MODEL_PART_RWEAPON, TEXT("Socket_Weapon_R")},
};

const int ONE_JUMP_HEIGHT = 300;	// һ�����߶�
const int TWO_JUMP_HEIGHT = 200;	// �������߶�

// effectState Ч��״̬
const int EFFECT_STATE_DIZZY = 1;		// 2 ^ 0	ѣ��Ч��
const int EFFECT_STATE_FIX = 2;			// 2 ^ 1	����Ч��
const int EFFECT_STATE_SLEEP = 4;		// 2 ^ 2	˯��Ч��

// Ч��״̬���ȼ�
const TArray<int> EFFECT_STATE_PRIORITY = { EFFECT_STATE_SLEEP, EFFECT_STATE_DIZZY, EFFECT_STATE_FIX };

const int32 RESOURCE_LOAD_DISTANCE[3] = { 1000, 3000, 5000 };