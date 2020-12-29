#pragma once
#include "../BaseManager.h"
#include "ClientTypes/GameFrameworkDefines.h"
#include "LoaderManager.generated.h"


UCLASS(Blueprintable)
class ULoaderManager : public UBaseManager
{
	GENERATED_BODY()

public:
	ULoaderManager();	///<���캯��
	~ULoaderManager();	///<��������

	static ULoaderManager *GetInstance();

	void ChangeToNewLoader(ELoadingType LoadingType);
	bool IsLoading() { return CurrLoader != nullptr; };
	
protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "LoaderManager")
		void OnBPProgressNotify(float Progress, bool bIsShow = true);
private:	
	UFUNCTION()
		void OnLoadFinished();
	void OnProgressNotify();
	void OnStartLoadingSpace(ELoadingType LoadingType);
	void CancelLoading();///<ȡ����ǰ���ͼ�����Ҫ�Ǽ����е��ߴ���
private:
	UPROPERTY()
		class UBaseLoader* CurrLoader;		///<��ǰ��ļ�����
	ELoadingType CurrLoaderType = ELoadingType::None;
	FTimerHandle ProgressNotifyTimer;	///<����֪ͨ��ʱ��
};
