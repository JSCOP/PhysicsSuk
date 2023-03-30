// Fill out your copyright notice in the Description page of Project Settings.


#include "PM_GameSettingScreen.h"

#include "CommonUI/MainMenu/GameSetting/PM_GameSettingRegistry.h"


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


