// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/LocalPlayerSubsystem.h"
#include "CommonUI/MainMenu/GameSetting/PM_GameSettingShared.h"
#include "PM_LocalPlayerSubsystem.generated.h"


/**
 * 
 */
UCLASS()
class PHYSICSSUK_API UPM_LocalPlayerSubsystem : public ULocalPlayerSubsystem
{
	GENERATED_BODY()
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	virtual void Deinitialize() override;
	
	static UPM_GameSettingShared* SettingShared;
};
