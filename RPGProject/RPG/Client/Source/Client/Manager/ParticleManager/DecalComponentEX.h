// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/DecalComponent.h"
#include "DecalComponentEX.generated.h"

/*
* �ļ����ƣ�CS3DecalComponent.h
* ����˵����
* �ļ����ߣ�zhangfudong
* Ŀǰά����zhangfudong
* ����ʱ�䣺2018-5-31
*/
UCLASS(BlueprintType, Blueprintable, meta = (ShortTooltip = "CS3DecalComponent ."))
class  UDecalComponentEX : public UDecalComponent
{
	GENERATED_BODY()
	
public:

	///��д��Ⱦ
	virtual void SendRenderTransform_Concurrent() override;

	///��һ֡��Ⱦ
	virtual void CreateRenderState_Concurrent() override;
	
	//ÿһ֡����λ��
	void SetComponentTransform();

	//����ʵ�ʵ�Yawֵ
	void CalculateDecalRealYaw();

private:
	USceneComponent* ParentComponent;
	float RealYaw = 0;
};

