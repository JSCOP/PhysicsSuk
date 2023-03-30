// Fill out your copyright notice in the Description page of Project Settings.


#include "PhysicsAxisLockActor.h"

#include "NiagaraFunctionLibrary.h"
#include "Physicssuk.h"

// Sets default values
APhysicsAxisLockActor::APhysicsAxisLockActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootPhysicsMesh = CreateDefaultSubobject<UStaticMeshComponent>("PhysicsMesh");
	RootPhysicsMesh->SetSimulatePhysics(true);
}

void APhysicsAxisLockActor::RotationValueChanged()
{
	// Declare two FVector variables to store the min and max points of the local space bounding box
	FVector OutMin;
	FVector OutMax;

	// Get the local space bounding box of the static mesh component
	RootPhysicsMesh->GetLocalBounds(OutMin, OutMax);

	DrawDebugPoint(GetWorld(), GetActorLocation() + OutMin, 10.f, FColor::Red, true);
	DrawDebugPoint(GetWorld(), GetActorLocation() + OutMax, 10.f, FColor::Red, true);

	// Get the bottom location of the actor
	FVector BottomLocation = GetActorLocation() - FVector(0.f, 0.f, ( OutMax.Z - OutMin.Z)/2.f) * GetActorScale();

	DrawDebugPoint(GetWorld(), BottomLocation, 5.f, FColor::Red, true);
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), RotationChangedParticle, BottomLocation);
}

// Called when the game starts or when spawned
void APhysicsAxisLockActor::BeginPlay()
{
	Super::BeginPlay();

	RotationStateChanged.AddDynamic(this, &APhysicsAxisLockActor::RotationValueChanged);
}

// Called every frame
void APhysicsAxisLockActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	int32 RotationValue = FMath::RoundToInt(GetActorRotation().Roll / 90.f * 90.f);
	LOG_M(1, "%d", RotationValue);
	switch (RotationValue)
	{
	case 90:
		if(RotationState != 90)
		{
			RotationState = 90;
			RotationStateChanged.Broadcast();
			RootPhysicsMesh->SetPhysicsLinearVelocity(FVector::ZeroVector);
		}
		break;
	case 180:
		if(RotationState != 180)
		{
			RotationState = 180;
			RotationStateChanged.Broadcast();
			RootPhysicsMesh->SetPhysicsLinearVelocity(FVector::ZeroVector);
		}
		break;
	case -90:
		if(RotationState != -90)
		{
			RotationState = -90;
			RotationStateChanged.Broadcast();
			RootPhysicsMesh->SetPhysicsLinearVelocity(FVector::ZeroVector);
		}
		break;
	case 0:
		if(RotationState != 0)
		{
			RotationState = 0;
			RotationStateChanged.Broadcast();
			RootPhysicsMesh->SetPhysicsLinearVelocity(FVector::ZeroVector);
		}
		break;
	default:
		break;
	}

	
	
}

