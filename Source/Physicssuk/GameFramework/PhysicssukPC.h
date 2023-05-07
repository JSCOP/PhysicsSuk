// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PhysicssukPC.generated.h"


UCLASS()
class PHYSICSSUK_API APhysicssukPC : public APlayerController
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APhysicssukPC();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void SetupInputComponent() override;

	virtual void OnConstruction(const FTransform& Transform) override;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void MobileInputSetup();

	UFUNCTION(BlueprintImplementableEvent)
	void OnRespawn();
	
private:
	
	float MouseSensitive = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<class UPM_CommonUIManager> CommonUIManager;
};
