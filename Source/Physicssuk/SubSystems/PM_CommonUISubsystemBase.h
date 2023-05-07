// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameUIManagerSubsystem.h"
#include "PM_CommonUISubsystemBase.generated.h"

/**
 * 
 */
UCLASS()
class PHYSICSSUK_API UPM_CommonUISubsystemBase : public UGameUIManagerSubsystem
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void ActivateBaseUI(ULocalPlayer* Player);
	
};
