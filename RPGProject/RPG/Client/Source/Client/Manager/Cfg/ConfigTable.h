#pragma once
#include "ClientObject.h"
#include "Engine/DataTable.h"
#include "ClientTableRowBase.h"
#include "ConfigTable.generated.h"


UCLASS(BlueprintType)
class UConfigTable :public UClientObject
{
	GENERATED_BODY()
private:
	UPROPERTY()
		UDataTable* Table;

	enum CheckState
	{
		NotCheck,
		Ok,
		Error,
	};

	//������¼���Ƿ��Ѿ�������(��ֹÿ�ζ����һ��)
	mutable TMap<FName, CheckState> AllRowCheckState;

	//���������
	bool CheckRow(const FCLIENT_TABLE_ROW_BASE* Row, const FName& RowName) const;

public:
	static UConfigTable* CreateCfgTable(UDataTable* Table);

	const UDataTable* GetBaseTable() const;

	TArray<FName> GetRowNames() const;

	template < class T = FCLIENT_TABLE_ROW_BASE>
	const T* GetRow(FString RowName) const
	{
		FName CurRowName = FName(*RowName);
		T* RowTable = (T*)Table->FindRowUnchecked(CurRowName);
		if (CheckRow(RowTable, CurRowName))
		{
			RowTable->RowName = CurRowName;
			return RowTable;
		}
		else
		{
			return nullptr;
		}
	}

	template < class T = FCLIENT_TABLE_ROW_BASE>
	const T* GetRow(FName RowName) const
	{
		T* RowTable = (T*)Table->FindRowUnchecked(RowName);
		if (CheckRow(RowTable, RowName))
		{
			RowTable->RowName = RowName;
			return RowTable;
		}
		else
		{
			return nullptr;
		}
	}

	template <class T>
	void GetAllRows(OUT TArray<T*>& OutRowArray) const
	{
		Table->GetAllRows(TEXT(""), OutRowArray);
	}
};
