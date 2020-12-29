#pragma once

#include "CoreMinimal.h"
#include "Client.h"
#include "RoleInfo.generated.h"

/**
 *������entity��ͻ���entity����������Ӧ�����Ķ���
 */

 /**
 *�����Ϣת����
 */
USTRUCT(BlueprintType)
struct FROLEINFO
{
	GENERATED_BODY()
public:
	FROLEINFO(){}
	FROLEINFO(const FVariant& variant)
	{
		//������ʽ{"dbid":...,"playerName":...}
		KBEngine::FVariantMap variantMap = variant.GetValue<KBEngine::FVariantMap>();//������variant��FVariantת����FVariantMap��TMap<FString, FVariant> 
		DBid = UINT64_TO_FSTRING(variantMap[TEXT("dbid")].GetValue<uint64>());
		PlayerName = variantMap[TEXT("playerName")].GetValue<FString>();
		Camp = variantMap[TEXT("camp")].GetValue<int32>();
		Gender = variantMap[TEXT("gender")].GetValue<int32>();
		Profession = variantMap[TEXT("profession")].GetValue<int32>();
	}

	FVariant ToVariant()
	{
		FVariant outVariant = FVariant();
		KBEngine::FVariantMap variantMap = KBEngine::FVariantMap();
		variantMap.Add(TEXT("dbid"), DBid);
		variantMap.Add(TEXT("playerName"), PlayerName);
		variantMap.Add(TEXT("camp"), Camp);
		variantMap.Add(TEXT("gender"), Gender);
		variantMap.Add(TEXT("profession"), Profession);
		outVariant = FVariant(variantMap);
		return outVariant;
	}

	bool operator == (const FROLEINFO &other)
	{
		return this->DBid == other.DBid;
	}

public:
	///<DBID���ݿ�Ψһ��ʶ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString DBid;
	///<�������
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString PlayerName;
	///<�����Ӫ
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Camp;
	///<����Ա�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Gender;
	///<���ְҵ
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Profession;
};


/**
*�����Ϣת��Tmap��
*/
USTRUCT(BlueprintType)
struct FROLEINFO_T
{
	GENERATED_BODY()
public:
	FROLEINFO_T() {}
	FROLEINFO_T(const FVariant& variant)
	{
		//������ʽ{"infos":[{"dbid":...,"playerName":...},...]}
		KBEngine::FVariantMap variantMap = variant.GetValue<KBEngine::FVariantMap>();//������variant��FVariantת����FVariantMap��TMap<FString, FVariant> 
		KBEngine::FVariantArray variantArray_infos = variantMap[TEXT("infos")].GetValue<KBEngine::FVariantArray>();//������variantMap��FVariantת��FVariantArray
		for (FVariant& element : variantArray_infos)
		{
			FROLEINFO tempRoleInfo = FROLEINFO(element);
			infos.Add(tempRoleInfo);
		}
	}

	FVariant ToVariant()
	{
		FVariant outVariant = FVariant();
		KBEngine::FVariantMap variantMap = KBEngine::FVariantMap();
		KBEngine::FVariantArray variantArray_infos = KBEngine::FVariantArray();
		for (auto& tempRoleInfo : infos)
		{
			FVariant element = tempRoleInfo.ToVariant();
			variantArray_infos.Add(element);
		}
		variantMap.Add(TEXT("infos"), variantArray_infos);

		outVariant = FVariant(variantMap);
		return outVariant;
	}

public:
	TArray<FROLEINFO> infos;///<���ת����Ϣ����
};