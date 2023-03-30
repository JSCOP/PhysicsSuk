// Fill out your copyright notice in the Description page of Project Settings.


#include "PM_FrontEnd.h"

#include "GameUIManagerSubsystem.h"
#include "PrimaryGameLayout.h"


// Sets default values for this component's properties
UPM_FrontEnd::UPM_FrontEnd()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPM_FrontEnd::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UPM_FrontEnd::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

