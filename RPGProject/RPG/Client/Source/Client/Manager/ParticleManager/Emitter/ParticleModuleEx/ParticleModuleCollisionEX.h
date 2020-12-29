// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ParticleModuleBaseEX.h"
#include "ParticleModuleCollisionEX.generated.h"

/*
* �ļ����ƣ�ParticleModuleCollisionEX.h
* ����˵����
* �ļ����ߣ�zhangfudong
* Ŀǰά����zhangfudong
* ����ʱ�䣺2018-09-11
*/

struct FParticleEmitterInstance;

UCLASS(editinlinenew, hidecategories = Object, meta = (DisplayName = "BeginForceUpdate"))
class  UBeginParticleModuleCollisionEX : public UParticleModuleBaseEX
{
	GENERATED_UCLASS_BODY()

	// ǿ��������ײ���¿�ʼ
	virtual void Update(FParticleEmitterInstance* Owner, int32 Offset, float DeltaTime) override;

	virtual bool CanTickInAnyThread()
	{
		return false;
	}
	
public:
	uint32 bCurrentDropDetail;
};

UCLASS(editinlinenew, hidecategories = Object, meta = (DisplayName = "EndForceUpdate"))
class  UEndParticleModuleCollisionEX : public UParticleModuleBaseEX
{
	GENERATED_UCLASS_BODY()
	
	// ǿ��������ײ�������
	virtual void Update(FParticleEmitterInstance* Owner, int32 Offset, float DeltaTime) override;

	virtual bool CanTickInAnyThread()
	{
		return false;
	}

};

