// Fill out your copyright notice in the Description page of Project Settings.


#include "PhysicsSukGameInstance.h"

#include "GameSettingRegistry.h"
#include "PM_LocalPlayer.h"

void UPhysicsSukGameInstance::Init()
{
	Super::Init();
}

ULocalPlayer* UPhysicsSukGameInstance::CreateInitialPlayer(FString& OutError)
{
	return Cast<UPM_LocalPlayer>(Super::CreateInitialPlayer(OutError));
	
}
