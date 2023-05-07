// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "JumpTriggerObstacle.generated.h"

UCLASS()
class PHYSICSSUK_API AJumpTriggerObstacle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AJumpTriggerObstacle();

protected:
	UFUNCTION()
	void OnMainCharacterDestroyed(AActor* DestroyedActor);
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
public:
	UFUNCTION()
	void ActivateObstacle();

	
	UFUNCTION(BlueprintImplementableEvent)
	void K2_ActivateObstacle();

private:
	UPROPERTY()
	class APM_MainCharacter* MainCharacter;

	bool bIsMainCharacterIsDestroyed = false;
};
