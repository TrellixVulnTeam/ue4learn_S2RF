// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "ClientObject.h"
#include "ClientTableRowBase.h"
#include "ConfigTable.h"
#include "ConfigData/ClientConfigData.h"
#include "CfgManager.generated.h"



/**
 * ���ñ������
 */

UCLASS(BlueprintType)
class UCfgManager : public UClientObject
{
	GENERATED_BODY()

public:
	UCfgManager();
	~UCfgManager();

	static UCfgManager* GetInstance();///<��ȡCfgManagerʵ��������static UCfgManager*  CfgManagerʵ������

	/**
	 *��ȡ�����б�����
	 *
	 *@param TableType �б�����
	 *
	 *@return  const UConfigTable
	 */
	const UConfigTable* GetTableByType(CLIENT_CONFIG_TYPE_ENUM TableType);

	/*
	*��ȡ�����б�����
	*
	*@param ConfigPath ���ñ�·��
	*
	*@return  const UConfigTable* �����б�����
	*/
	const UConfigTable* GetTableByPath(TSoftObjectPtr<UDataTable> ConfigPath);

private:
	void LoadMainCfg(FString path, bool preload = true);///<�������ñ�
private:
	UPROPERTY()
		UConfigTable* ClientConfigTable;///���ñ������ݱ�
	UPROPERTY()
		TMap<CLIENT_CONFIG_TYPE_ENUM, UConfigTable*> TableMap;///���ñ�
	UPROPERTY()
		TMap<TSoftObjectPtr<UDataTable>, UConfigTable*> TablePathMap;///���ñ�·����
};
