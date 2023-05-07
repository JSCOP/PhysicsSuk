// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PhysicssukGameMode.generated.h"

class APlayerStart;
UCLASS(minimalapi)
class APhysicssukGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	APhysicssukGameMode();

	virtual void BeginPlay() override;
public:

	UFUNCTION(BlueprintCallable)
	void RespawnPlayer();

	void SetSavePoint(class ASaveTrigger* SaveTrigger);

	virtual void StartPlay() override;

	UFUNCTION(BlueprintCallable)
	void MobileInputSetup();

private:
	UPROPERTY()
	class ASaveTrigger* CurrentSaveTrigger;
};



