// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameCharacter.generated.h"


UCLASS()
class CLIENT_API AGameCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGameCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());///<��ʼ���������Ĵ�����
	
	//--------- Begin Super Interface
	virtual void PostActorCreated()override;
	virtual void OnConstruction(const FTransform& Transform)override;///<���Դ�������ͼ������صĲ���
	virtual void PostRegisterAllComponents() override;///<Actor���ע����ɺ�
	virtual void PostInitializeComponents() override;///<Actor�����ʼ����ɺ�	��������ݵĸ��£�	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Destroyed() override;
	//-------------End Super Interface

	//-----------------Begin InitComponent
	virtual void InitCharacterDefaultComponent();
	virtual void InitCharacterComponentPostActorCreated();///<�����ڹ��캯���д����������ִ��˳�򣬼̳�GameCharacter��Ҫ�������������ڹ��캯���е����Լ���InitBaseComponent()��
	virtual void InitCapsuleComponent();///<��ʼ��������������ݣ�Character���캯���Ѵ�����
	virtual void InitCharacterMovementComponent();///<��ʼ���ƶ�������ݣ�Character���캯���Ѵ�����
	virtual void InitAppearanceComponent();///<����������	

	//-----------------End InitComponent

	//-----------------Begin Appearance
	virtual void CreateAppearance();
	virtual void CreateApperanceOver();
	//-----------------End Appearance

	bool IsDestroyed();///<��Ϸ����߼��ж� ��ǰGameCharacter�Ƿ���Ч

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USkeletalMeshComponent* SKMesh_Heads;///<ͷ��

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USkeletalMeshComponent* SKMesh_Hair;///<ͷ�� 

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USkeletalMeshComponent* SKMesh_Adorn;///<ͷ��

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USkeletalMeshComponent* SKMesh_Hat;///<ñ��

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USkeletalMeshComponent* SKMesh_Coats;///<����

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USkeletalMeshComponent* SKMesh_Wrist;///<����

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USkeletalMeshComponent* SKMesh_Gloves;///<����

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USkeletalMeshComponent* SKMesh_Belt;///<����

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USkeletalMeshComponent* SKMesh_Necklace;///<����

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USkeletalMeshComponent* SKMesh_L_RING;///<���ֽ�ָ

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USkeletalMeshComponent* SKMesh_R_RING;///<���ֽ�ָ

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USkeletalMeshComponent* SKMesh_Pants;///<����

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USkeletalMeshComponent* SKMesh_Shoes;///<Ь��

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USkeletalMeshComponent* SKMesh_Cloak;///<����

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* STMesh_LHweapon;///<��������

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* STMesh_RHweapon;///<��������

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* STMesh_DefaultStatic;///<Ĭ�Ͼ�̬���

protected:
	bool bIsDestroyed = false;///<��ǰGameCharacter�Ƿ�����

	class UEquipComponent* EquipComponent;


};
