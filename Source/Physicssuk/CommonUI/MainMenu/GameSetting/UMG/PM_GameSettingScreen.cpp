// Fill out your copyright notice in the Description page of Project Settings.


#include "PM_GameSettingScreen.h"

#include "Physicssuk.h"
#include "GameFramework/PM_LocalPlayer.h"
#include "CommonUI/MainMenu/GameSetting/PM_GameSettingRegistry.h"
#include "CommonUI/MainMenu/GameSetting/PM_GameSettingShared.h"


#define LOCTEXT_NAMESPACE "PM_GameSettingRegistry"

void UPM_GameSettingScreen::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	//NavigateToSetting(FName("MouseAndKeyboardCollection"));
}

UGameSettingRegistry* UPM_GameSettingScreen::CreateRegistry()
{
	UPM_GameSettingRegistry* NewRegistry = NewObject<UPM_GameSettingRegistry>();

	if (ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(GetOwningLocalPlayer()))
	{
		NewRegistry->Initialize(LocalPlayer);
	}

	return NewRegistry;
}

void UPM_GameSettingScreen::NativeOnActivated()
{
	Super::NativeOnActivated();

	
}

void UPM_GameSettingScreen::DebugBreakpoint()
{
	//Load SharedSetting from LocalPlayer
	UPM_LocalPlayer* LocalPlayer = Cast<UPM_LocalPlayer>(GetOwningLocalPlayer());
	if (LocalPlayer)
	{
		UPM_GameSettingShared* SharedSetting = LocalPlayer->GetSharedSettings();
		if (SharedSetting)
		{
			SharedSetting->SaveSettings();
		}
	}
	
}


