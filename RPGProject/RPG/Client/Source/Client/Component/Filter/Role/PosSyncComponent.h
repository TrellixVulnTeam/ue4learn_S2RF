// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "KBEngine.h"
#include "../../ClientActorComponent.h"
#include "PosSyncComponent.generated.h"

/*
* ����˵������ɫͬ���ƶ�λ���������Ҫ�����������ͬ�����ǵ�ǰ�ƶ�λ�ã�
*/

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class  UPosSyncComponent : public UClientActorComponent
{
	GENERATED_BODY()

public:	
	UPosSyncComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
