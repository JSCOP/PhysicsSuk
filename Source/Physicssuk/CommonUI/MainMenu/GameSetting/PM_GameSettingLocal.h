// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameUserSettings.h"
#include "PM_GameSettingLocal.generated.h"

/**
 * 
 */
UCLASS()
class PHYSICSSUK_API UPM_GameSettingLocal : public UGameUserSettings
{
	GENERATED_BODY()
public:
	UFUNCTION()
	static UPM_GameSettingLocal* Get();
};
