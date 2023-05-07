// Fill out your copyright notice in the Description page of Project Settings.


#include "PhysicsSukGameInstance.h"

#include "GameSettingRegistry.h"
#include "PM_LocalPlayer.h"
#include "CommonUI/Miscellaneous/PM_CommonGameViewportClient.h"

void UPhysicsSukGameInstance::Init()
{
	Super::Init();
}


UPM_CommonGameViewportClient* UPhysicsSukGameInstance::GetGameViewportClient() const
{
	return Cast<UPM_CommonGameViewportClient>(UGameInstance::GetGameViewportClient());
}
