#pragma once

#include "../ClientTableRowBase.h"
#include "Engine/StreamableManager.h"
#include "StrToClass.generated.h"


USTRUCT(BlueprintType)
struct FSTR_TO_CLASS_DATA : public FCLIENT_TABLE_ROW_BASE
{
	GENERATED_USTRUCT_BODY()
public:
	//��Ŷ�Ӧ��ͼ��·��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSoftClassPtr<UObject> ClassPath;

	//��̨�첽����(�����ͷ�)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool BackstageAsyncLoad = true;

	UClass* GetTargetClass()
	{
		UClass* targetClass = ClassPath.Get();
		if (targetClass == nullptr )
		{
			FStreamableManager StreamManager;
			return StreamManager.LoadSynchronous(ClassPath);
		}
		return targetClass;
	}

	bool GetIsBackstageAsyncLoad() override
	{
		return BackstageAsyncLoad;
	};
};
