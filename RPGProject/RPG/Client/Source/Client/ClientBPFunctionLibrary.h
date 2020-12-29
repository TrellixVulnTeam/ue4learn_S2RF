// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KBEngine.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ClientBPFunctionLibrary.generated.h"


class UEntityInterfaceObject;

/**
 * 
 */
UCLASS()
class CLIENT_API UClientBPFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/*----------------��ɫ���-----------------------*/
		///<�õ�����
	UFUNCTION(BlueprintPure, Category = "Golbal")
		static class AServerCharacter* GetPlayerCharacter();

	///<�õ�����entity
	static  KBEngine::Entity* GetPlayer();

	///<��ȡ���ID
	UFUNCTION(BlueprintPure)
		static int GetPlayerID();

	///<��ȡinterface
	UFUNCTION(BlueprintPure)
		static UEntityInterfaceObject* GetInterfaceByName(const FString& Name, int32 id = 0);

	
	UFUNCTION(BluePrintPure)
		static FString GetStringPropertyValue(const int32& EntityID, const FString& PropName);

	UFUNCTION(BluePrintPure)
		static int32 GetIntPropertyValue(const int32& EntityID, const FString& PropName);

	UFUNCTION(BluePrintPure)
		static float GetFloatPropertyValue(const int32& EntityID, const FString& PropName);

	/*----------------UE4 SpawnActor-----------------------*/
	UFUNCTION(BlueprintCallable)
		static class AActor* BeginDeferredActorSpawnFromClass(TSubclassOf<AActor> ActorClass, const FTransform& SpawnTransform, ESpawnActorCollisionHandlingMethod CollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn, AActor* Owner = nullptr);
	
	UFUNCTION(BlueprintCallable)
		static class AActor* FinishSpawningActor(AActor* Actor, const FTransform& SpawnTransform);

	/*----------------�ַ����������-----------------------*/

	/**
	*BlueprintCallable,FString�ַ������
	*
	*@param	InString ��Ҫ����ַ���
	*@param	IsElemUnique �Ƿ񱣳ַָ��������Ԫ��Ψһ
	*@param	SplitChar �ָ�����
	*
	*@return TArray<FString> �����ṩ���Ʒ���ParseIntoArray
	*/
	UFUNCTION(BlueprintCallable, Category = "FSrting|Split")
		static TArray<FString> SplitString(const FString& InString, bool IsElemUnique = false, FString SplitChar = TEXT("|"));

	///<����
	static FString TypeValidation(const FString InString);

	static UClass* GetUClassByStr(const FString InString);
};
