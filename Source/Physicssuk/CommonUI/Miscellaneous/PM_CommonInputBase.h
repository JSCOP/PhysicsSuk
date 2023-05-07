// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonInputBaseTypes.h"
#include "Engine/DataTable.h"
#include "PM_CommonInputBase.generated.h"

/**
 * 
 */
UCLASS()
class PHYSICSSUK_API UPM_CommonInputBase : public UCommonUIInputData
{
	GENERATED_BODY()


private:
	UPROPERTY(EditDefaultsOnly, Category = "Properties", meta = (RowType = "/Script/CommonUI.CommonInputActionDataBase"))
	FDataTableRowHandle DefaultAnykeyAction;
};
