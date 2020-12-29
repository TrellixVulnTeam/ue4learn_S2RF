#pragma once
#include "ClientObject.h"
#include "BaseLoader.generated.h"



DECLARE_DELEGATE(FOnLoadFinished);
class UBaseDetect;
/**
*���ػ���
*/
UCLASS(BlueprintType)
class UBaseLoader : public UClientObject
{
	GENERATED_BODY()

public:
	virtual void StartLoading();		///<��ʼ����
	virtual void CancelLoading();				///<ȡ����ǰ����
	virtual float GetCurProgress();	   ///<��ȡ��ǰ����
protected:
	virtual void InitData();	
	virtual void Loading();				///<�����ؽ���	
	virtual void FinishLoaded();		///<��ɼ��
	virtual void OnAssetFinishDetect(); ///<������Դ�������	
public:	
	FOnLoadFinished OnLoadFinished;				///<���ػص�
protected:
	UPROPERTY()
		TArray<UBaseDetect*> LoadDetector;
	float TotalProgress = 0.0f;						///<�����ܽ���
	int32  DetectorIndex = -1;						///<
	TArray<float> LoadProgressList;					///<���ؽ����б�
	TArray<FString>LoadParamList;
};