// Fill out your copyright notice in the Description page of Project Settings.


#include "GameFramework/Actors/TriggerEventManageActor.h"
#include "Components/ActorComponent.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
ATriggerEventManageActor::ATriggerEventManageActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootSceneComponent"));
	SetRootComponent(RootSceneComponent);	
}

UPrimitiveComponent* ATriggerEventManageActor::GetTriggerVolumeComponent() const
{
	if(IsValid(TriggerVolumeComponent))
	{
		return Cast<UPrimitiveComponent>(TriggerVolumeComponent);
	}
	return nullptr;
}

// Called when the game starts or when spawned
void ATriggerEventManageActor::BeginPlay()
{
	Super::BeginPlay();

	
}

// Called every frame
void ATriggerEventManageActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATriggerEventManageActor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	switch (TriggerVolumeType)
	{
	case ETriggerVolumeType::Box:
		{
			TriggerVolumeComponent = NewObject<UBoxComponent>(this, TEXT("TriggerVolumeComponent"));
			break;
		}
	case ETriggerVolumeType::Capsule:
		{
			TriggerVolumeComponent = NewObject<UCapsuleComponent>(this, TEXT("TriggerVolumeComponent"));	
			break;
		}
	case ETriggerVolumeType::Sphere:
		{
			TriggerVolumeComponent = NewObject<USphereComponent>(this, TEXT("TriggerVolumeComponent"));
			break;
		}
	}
}