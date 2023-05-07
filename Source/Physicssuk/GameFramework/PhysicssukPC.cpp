// Fill out your copyright notice in the Description page of Project Settings.


#include "PhysicssukPC.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "PM_LocalPlayer.h"
#include "CommonUI/Miscellaneous/PM_CommonUIManager.h"
#include "SubSystems/PM_LocalPlayerSubsystem.h"


// Sets default values
APhysicssukPC::APhysicssukPC()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APhysicssukPC::BeginPlay()
{
	Super::BeginPlay();
	
	
}

// Called every frame
void APhysicssukPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APhysicssukPC::SetupInputComponent()
{
	Super::SetupInputComponent();

}

void APhysicssukPC::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	//If there's exist component that is inherited from UPM_CommonUIManager, then set it to CommonUIManager
	if (UPM_CommonUIManager* CommonUIManagerComponent = Cast<UPM_CommonUIManager>(GetComponentByClass(UPM_CommonUIManager::StaticClass())))
	{
		CommonUIManager = CommonUIManagerComponent;
	}
	
}
