#pragma once

#include "UIDefine.generated.h"

/**
* ��������
*/
UENUM(BlueprintType)
enum class WINDOW_TYPE_ENUM : uint8
{
	///û�н�������
	WINDOW_TYPE_NO = 0,
	///��¼����
	WINDOW_TYPE_LOGIN,
	///��ɫ��������
	WINDOW_TYPE_CREATE_ROLE,
	///��ɫѡ�����
	WINDOW_TYPE_SELECT_ROLE,
	///����ת������
	WINDOW_TYPE_SWITCH_SCENE,
	///������
	WINDOW_TYPE_MAIN
};
