#pragma once

#include "ModelDefine.generated.h"

/**
* ģ������
*/
UENUM(BlueprintType)
enum class MODEL_PART_TYPE : uint8
{
	///ͷ��ģ��
	MODEL_PART_HEAD = 1,
	///����ģ��
	MODEL_PART_FACE = 2,
	///����ģ��
	MODEL_PART_CLOAK = 3,
	///����ģ��
	MODEL_PART_BODY = 4,
	///ͷ��ģ��
	MODEL_PART_HAIR = 5,
	///ͷ��ģ��
	MODEL_PART_ADORN = 6,
	///ñ��ģ��
	MODEL_PART_HAT = 7,
	///����ģ��
	MODEL_PART_COAT = 8,
	///����ģ��
	MODEL_PART_WRIST = 9,
	///����ģ��
	MODEL_PART_HAND = 10,
	///����ģ��
	MODEL_PART_WAIST = 11,
	///����ģ��
	MODEL_PART_PANTS = 12,
	///Ь��ģ��
	MODEL_PART_SHOES = 13,
	///����ģ��
	MODEL_PART_NECKLACE = 14,
	///���ֽ�ָģ��
	MODEL_PART_LRING = 15,
	///���ֽ�ָģ��
	MODEL_PART_RRING = 16,
	///������ģ��
	MODEL_PART_LWEAPON = 17,
	///������ģ��
	MODEL_PART_RWEAPON = 18,
	/// Ĭ�Ͼ�̬ģ��
	MODEL_TYPE_STATIC = 19,
};
