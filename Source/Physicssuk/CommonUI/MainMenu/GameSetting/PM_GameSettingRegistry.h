// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameSettingRegistry.h"

#include "PM_GameSettingRegistry.generated.h"

/**
 * 
 */
class UPM_LocalPlayer;

#define GET_SHARED_SETTINGS_FUNCTION_PATH(FunctionOrPropertyName)							\
MakeShared<FGameSettingDataSourceDynamic>(TArray<FString>({								\
GET_FUNCTION_NAME_STRING_CHECKED(UPM_LocalPlayer, GetSharedSettings),				\
GET_FUNCTION_NAME_STRING_CHECKED(UPM_GameSettingShared, FunctionOrPropertyName)		\
}))

#define GET_LOCAL_SETTINGS_FUNCTION_PATH(FunctionOrPropertyName)							\
MakeShared<FGameSettingDataSourceDynamic>(TArray<FString>({								\
GET_FUNCTION_NAME_STRING_CHECKED(UPM_LocalPlayer, GetLocalSettings),				\
GET_FUNCTION_NAME_STRING_CHECKED(UPM_GameSettingLocal, FunctionOrPropertyName)		\
}))

UCLASS()
class PHYSICSSUK_API UPM_GameSettingRegistry : public UGameSettingRegistry
{
	GENERATED_BODY()

protected:
	virtual void OnInitialize(ULocalPlayer* InLocalPlayer) override;

	UGameSettingCollection* MouseAndKeyboardSettings(ULocalPlayer* InLocalPlayer);

	UFUNCTION()
	virtual void SaveChanges() override;
};
