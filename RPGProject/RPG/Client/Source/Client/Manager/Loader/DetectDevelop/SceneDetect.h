#pragma once
#include "../BaseDetect.h"
#include "SceneDetect.generated.h"



UCLASS(BlueprintType)
class USceneDetect : public UBaseDetect
{
	GENERATED_BODY()

public:
	virtual void InitData(const FString& Params) override;
	virtual void StartDetect(const FString& Params)override;
	virtual void Detect() override;		   ///<�����ؽ���	
	virtual void CancelDetect()override;  ///<ȡ������
private:
	UFUNCTION()
		void OnLevelLoadFinished();

private:
	bool bIsLoadFinished = false;
};

