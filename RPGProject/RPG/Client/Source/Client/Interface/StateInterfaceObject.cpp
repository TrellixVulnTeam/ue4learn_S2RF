// Fill out your copyright notice in the Description page of Project Settings.

#include "StateInterfaceObject.h"
#include "Character/ServerCharacter.h"


#pragma optimize("",off)

void UStateInterfaceObject::OnRep_state(const int32& NewState, const int32& OldState)
{
	AServerCharacter* character = Cast<AServerCharacter>(GetActor());
	if (character)
	{
		character->OnStateChange(NewState, OldState);
	}
	else  // character ��û�д�����ɣ����ǲ�����ɣ���
	{

	}
}

void UStateInterfaceObject::OnRep_effectState(const int32& NewEffect, const int32& OldEffect)
{
	AServerCharacter* character = Cast<AServerCharacter>(GetActor());
	if (character)
	{
		character->OnEffectStateChange(NewEffect, OldEffect);
	}
	else  // character ��û�д�����ɣ����ǲ�����ɣ���
	{

	}
}

void UStateInterfaceObject::OnRep_actForbid(const int32& NewActForbid, const int32& OldActForbid)
{

}

void UStateInterfaceObject::GetMethodMap(TArray<FString>& Methods)
{
}

void UStateInterfaceObject::GetPropertyMap(TArray<FString>& Propertys)
{
	Propertys.Add(TEXT("state"));
	Propertys.Add(TEXT("effectState"));
	Propertys.Add(TEXT("actForbid"));
}

#pragma optimize("",on)
