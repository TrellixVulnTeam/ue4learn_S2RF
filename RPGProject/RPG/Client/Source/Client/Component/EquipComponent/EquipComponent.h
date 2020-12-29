// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ClientTypes/ModelDefine.h"
#include "Components/MeshComponent.h"
#include "EquipComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CLIENT_API UEquipComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEquipComponent();

	///  ����ģ��
	void CreateModel(const TMap<MODEL_PART_TYPE, FString>& ModelMap);

	/// �ı�ģ�Ͳ���
	void ChangeModelPart(const MODEL_PART_TYPE& ModelPart, const FString& ModelID);

	void OnSetMeshFinish(const MODEL_PART_TYPE& ModelPart);

private:
	/// �Ƴ�û�����õ�ģ��
	void RemoveOtherMesh(const TArray<MODEL_PART_TYPE>& ModelPartTypes);

	/// ����mesh���
	void CreateActorMeshComponents(const TArray<MODEL_PART_TYPE>& ModelPartTypes);

	FORCEINLINE UStaticMeshComponent* CreateStaticMeshComponent(USkeletalMeshComponent* ParentMesh, const MODEL_PART_TYPE& ModelType, const FName& Name);
	FORCEINLINE USkeletalMeshComponent* CreateSKeletalMeshComponent(USkeletalMeshComponent* ParentMesh, const MODEL_PART_TYPE& ModelType, const FName& Name);

	void GetModelDataFromCfg(const TMap<MODEL_PART_TYPE, FString>& ModelMap, TMap<MODEL_PART_TYPE, const struct FMODEL_CONFIG_DATA*>& ModelData);

	/// ˢ�����е�mesh��۵㡣��Ϊ����û����ϣ���ӵ���Ӧ�Ĳ�۵��ʧ��
	void RefreshMeshSockName();		

	

private:
	TMap<MODEL_PART_TYPE, UMeshComponent*> OwnerMeshComponent;
};

