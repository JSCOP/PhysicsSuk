// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NiagaraSystem.h"
#include "GameFramework/Actor.h"
#include "PhysicsAxisLockActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FRotationStateChanged);

UCLASS()
class PHYSICSSUK_API APhysicsAxisLockActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APhysicsAxisLockActor();

	UFUNCTION()
	void RotationValueChanged();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess="true"))
	class UStaticMeshComponent* RootPhysicsMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=PhysicsSettings ,meta=(AllowPrivateAccess="true"))
	int32 MassKG = 125 ;

	int32 RotationState = -1;

	UPROPERTY(BlueprintAssignable, BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess="true"))
	FRotationStateChanged RotationStateChanged;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=VFX, meta=(AllowPrivateAccess="true"))
	UNiagaraSystem* RotationChangedParticle;
};

