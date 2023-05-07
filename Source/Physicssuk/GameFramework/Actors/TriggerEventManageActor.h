// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TriggerEventManageActor.generated.h"

UENUM()
enum class ETriggerVolumeType : uint8
{
	Box = 0,
	Sphere = 1,
	Capsule = 2,
};

class UBoxComponent;
UCLASS()
class PHYSICSSUK_API ATriggerEventManageActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATriggerEventManageActor();

	UFUNCTION(BlueprintCallable, Category = "TriggerEventManageActor")
	UPrimitiveComponent* GetTriggerVolumeComponent() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnConstruction(const FTransform& Transform) override;

private:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
	USceneComponent* RootSceneComponent;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
	UActorComponent* TriggerVolumeComponent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
	ETriggerVolumeType TriggerVolumeType = ETriggerVolumeType::Box;
};
