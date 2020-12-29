#pragma once
#include "../ClientTableRowBase.h"
#include "ClientConfigData.generated.h"


///�����ñ������
UENUM()
enum class CLIENT_CONFIG_TYPE_ENUM :uint8
{
	///��
	CLIENT_CONFIG_TYPE_NULL = 0	UMETA(DisplayName = "CLIENT_CONFIG_TYPE_NULL"),
	CLIENT_CONFIG_ENTITY_INTERFACE_DEFINE = 1 UMETA(DisplayName = "CLIENT_CONFIG_ENTITY_INTERFACE_DEFINE"),
	CLIENT_CONFIG_ENTITY_OF_ACTOR_CLASS_ASSET = 2 UMETA(DisplayName = "CLIENT_CONFIG_ENTITY_OF_ACTOR_CLASS_ASSET"),///<entity��ӦActor����ͼ��Դ
	CLIENT_CONFIG_MODEL_PART_CONFIG = 3 UMETA(DisplayName = "CLIENT_CONFIG_MODEL_PART_CONFIG"),
	CLIENT_CONFIG_ANIMATION_CONFIG = 4 UMETA(DisplayName = "CLIENT_CONFIG_ANIMATION_CONFIG"),
	CLIENT_CONFIG_STRTOCLASS = 5 UMETA(DisplayName = "CLIENT_CONFIG_STRTOCLASS"),
	CLIENT_CONFIG_TYPE_PARTICLE = 6 UMETA(DisplayName = "CLIENT_CONFIG_TYPE_PARTICLE"),
	CLIENT_CONFIG_EFFECT_PRELOAD_DATA = 7 UMETA(DisplayName = "CLIENT_CONFIG_EFFECT_PRELOAD_DATA"),
};

USTRUCT(BlueprintType)
struct  FCLIENT_CONFIG_DATA : public FCLIENT_TABLE_ROW_BASE
{
	GENERATED_BODY()
public:
	///������ʾ��Ϣ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "CsvCongData", DisplayName = "HintDesc")
		FString HintDesc;
	///���ü���·��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "CsvCongData", DisplayName = "ConfigPath")
		TSoftObjectPtr<UDataTable> ConfigPath;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "CsvCongData", DisplayName = "PreLoad")
		bool PreLoading = true;
};
