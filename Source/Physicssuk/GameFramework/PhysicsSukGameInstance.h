// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonGameInstance.h"
#include "Engine/GameInstance.h"
#include "PhysicsSukGameInstance.generated.h"

class UPM_CommonGameViewportClient;
class UGameSetting;
/**
 * 
 */
UCLASS()
class PHYSICSSUK_API UPhysicsSukGameInstance : public UCommonGameInstance
{
	GENERATED_BODY()

public:
	virtual void Init() override;
	
	UFUNCTION(BlueprintCallable)
	UPM_CommonGameViewportClient* GetGameViewportClient() const;
};
