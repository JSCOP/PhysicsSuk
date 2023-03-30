// Fill out your copyright notice in the Description page of Project Settings.


#include "PM_GameSettingShared.h"


#include "PM_LocalPlayer.h"
#include "Kismet/GameplayStatics.h"

static FString SHARED_SETTINGS_SLOT_NAME = TEXT("SharedGameSettings");

void UPM_GameSettingShared::Initialize(UPM_LocalPlayer* LocalPlayer)
{
	OwningPlayer = LocalPlayer;
}

void UPM_GameSettingShared::ApplySettings()
{
}

UPM_GameSettingShared* UPM_GameSettingShared::LoadOrCreateSettings(const UPM_LocalPlayer* LocalPlayer)
{
	UPM_GameSettingShared* SharedSettings = nullptr;

	// If the save game exists, load it.
	if (UGameplayStatics::DoesSaveGameExist(SHARED_SETTINGS_SLOT_NAME, LocalPlayer->GetLocalPlayerIndex()))
	{
		USaveGame* Slot = UGameplayStatics::LoadGameFromSlot(SHARED_SETTINGS_SLOT_NAME, LocalPlayer->GetLocalPlayerIndex());
		SharedSettings = Cast<UPM_GameSettingShared>(Slot);
	}
	
	if (SharedSettings == nullptr)
	{
		SharedSettings = Cast<UPM_GameSettingShared>(UGameplayStatics::CreateSaveGameObject(UPM_GameSettingShared::StaticClass()));
	}

	SharedSettings->Initialize(const_cast<UPM_LocalPlayer*>(LocalPlayer));

	return SharedSettings;
}

void UPM_GameSettingShared::SaveSettings()
{
	UGameplayStatics::SaveGameToSlot(this, SHARED_SETTINGS_SLOT_NAME,OwningPlayer->GetLocalPlayerIndex());
}
