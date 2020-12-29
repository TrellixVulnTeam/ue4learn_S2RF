#pragma once

#include "ClientObject.h"
#include "BaseDetect.generated.h"

DECLARE_DELEGATE(FOnDetectFinished);


/**
*���ػ���
*/
UCLASS(BlueprintType)
class  UBaseDetect : public UClientObject
{
	GENERATED_BODY()
public:
	virtual void InitData(const FString& Params);
	virtual void StartDetect(const FString& Params = TEXT(""));
	virtual void Detect();	///<�����ؽ���
	virtual void FinishDetect();	///<��ɼ���
	virtual void OnTimeoutDetect();///<��ʱ���
	virtual void CancelDetect();  ///<ȡ������
public:
	FOnDetectFinished OnDetectFinished;
	FTimerHandle TimeoutTimer;					///<��ʱTimer
	FTimerHandle DetectTimer;					///<���Timer
	float CProgress = 0.0f;
	float TimeoutTime = 0.0f;					///<��ʱʱ��
};



