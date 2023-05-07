// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonLocalPlayer.h"
#include "PM_LocalPlayer.generated.h"

class UPM_GameSettingLocal;
class UPM_GameSettingShared;
/**
 * 
 */
UCLASS()
class PHYSICSSUK_API UPM_LocalPlayer : public UCommonLocalPlayer
{
	GENERATED_BODY()

public:
	
	virtual void InitOnlineSession() override;
	
	UFUNCTION()
	UPM_GameSettingLocal* GetLocalSettings() const;

	UFUNCTION()
	UPM_GameSettingShared* GetSharedSettings() const;

	
	
};
