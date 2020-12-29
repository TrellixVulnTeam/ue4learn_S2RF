// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interface/EntityInterfaceObject.h"
#include "RoleSpaceInterfaceObject.generated.h"

/**
 *
 */
UCLASS()
class CLIENT_API URoleSpaceInterfaceObject : public UEntityInterfaceObject
{
	GENERATED_BODY()

		typedef UEntityInterfaceObject Super;

public:
	/**
	*Define method
	* BlueprintNativeEvent����������ҽ���ռ�ص�֪ͨ
	*
	*@param SpaceScriptID �ռ�ű�ID
	*@param SpaceType �ռ�����
	*
	*@return ��
	*/
	UFUNCTION(BlueprintNativeEvent, Category = "RoleSpaceInterfaceObject")
		void CLIENT_OnEnterSpaceNotify(const FString& SpaceScriptID, const INT32 SpaceType);

	/**
	*Define method
	* BlueprintNativeEvent������������뿪�ռ�ص�֪ͨ
	*
	*@return ��
	*/
	UFUNCTION(BlueprintNativeEvent, Category = "RoleSpaceInterfaceObject")
		void CLIENT_OnLeaveSpaceNotify();

	/**
	*Exposed method
	*BlueprintCallable������������ĳ���ռ�
	*
	*@param SpaceScriptID �ռ�ű�ID
	*@param Position λ��
	*@param Direction ����
	*
	*@return ��
	*/
	UFUNCTION(BlueprintCallable)
		void CELL_GoToSpace(FString SpaceScriptID, FVector Position, FVector Direction);

	virtual void GetMethodMap(TArray<FString>& Methods) override;
	virtual void GetPropertyMap(TArray<FString>& Propertys) override;

};
