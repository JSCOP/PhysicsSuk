// Fill out your copyright notice in the Description page of Project Settings.


#include "SubSystems/PM_LocalPlayerSubsystem.h"
#include "GameFramework/PM_LocalPlayer.h"
#include "CommonUI/MainMenu/GameSetting/PM_GameSettingShared.h"

UPM_GameSettingShared* UPM_LocalPlayerSubsystem::SettingShared = nullptr;

void UPM_LocalPlayerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	SettingShared = UPM_GameSettingShared::LoadOrCreateSettings(GetLocalPlayer<UPM_LocalPlayer>());
}

void UPM_LocalPlayerSubsystem::Deinitialize()
{
	Super::Deinitialize();
	if(IsValid(SettingShared))
	{
		//SettingShared->MarkAsGarbage();
	}
}
 