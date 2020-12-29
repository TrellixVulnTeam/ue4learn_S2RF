// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "../ClientTableRowBase.h"
#include "Engine/StreamableManager.h"
#include "EntityInterfaceDefine.generated.h"


/**
* 
*/
USTRUCT(BlueprintType)
struct FInterfaceInfos
{
	GENERATED_BODY()

public:
	//�ӿڵ�UClass������
	UPROPERTY(EditAnywhere)
		TSoftClassPtr<class UEntityInterfaceObject> ClassEntity;

	//��Ӧ�ӿڵ�����
	UPROPERTY(EditAnywhere)
		FString ActorPropertyName;

};

/**
*entity�Ľӿ����ýṹ��
*���ܣ��������ø���entity������Ľӿ�
*/
USTRUCT(BlueprintType)
struct FINTERFACE_DEFINE : public FCLIENT_TABLE_ROW_BASE
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
		TArray<FInterfaceInfos> InterfaceList;

	UClass* GetInterfaceInfosClass(FInterfaceInfos InterfaceInfo)
	{
		UClass* targetClass = InterfaceInfo.ClassEntity.Get();
		if (targetClass == nullptr)
		{
			FStreamableManager StreamManager;
			return StreamManager.LoadSynchronous(InterfaceInfo.ClassEntity);
			
		}
		return targetClass;
	}
};
