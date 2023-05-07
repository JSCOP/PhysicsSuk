// Fill out your copyright notice in the Description page of Project Settings.


#include "TestActor.h"

#include "Physicssuk.h"
#include "Components/BoxComponent.h"


// Sets default values
ATestActor::ATestActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATestActor::BeginPlay()
{
	Super::BeginPlay();

	if(!IsValid(StaticMeshRef))
	{
		return;
	}

	FVector StaticMeshSize = FVector(StaticMeshRef->GetBounds().BoxExtent.X,StaticMeshRef->GetBounds().BoxExtent.Y, StaticMeshRef->GetBounds().BoxExtent.Z); 
	
	//Spawn Actor way
	for(int x = 0; x<10; x++)
	{
		for(int y = 0; y<10; y++)
		{
			for(int z = 0; z<10; z++)
			{
				FTransform SpawnTransform = FTransform::Identity;
				SpawnTransform.SetLocation(GetActorLocation() + FVector(x * SpawnOffset + x * StaticMeshSize.X, y * SpawnOffset + y * StaticMeshSize.Y, z * SpawnOffset + z * StaticMeshSize.Z));
				SpawnTransform.SetRotation(GetActorRotation().Quaternion());
				UStaticMeshComponent* AddedComponent = Cast<UStaticMeshComponent>(AddComponentByClass(UStaticMeshComponent::StaticClass(), true, SpawnTransform, false));

				AddedComponent->SetupAttachment(RootComponent);
				AddedComponent->SetStaticMesh(StaticMeshRef);
				AddedComponent->SetSimulatePhysics(true);
			}
		}
	}
}

// Called every frame
void ATestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}