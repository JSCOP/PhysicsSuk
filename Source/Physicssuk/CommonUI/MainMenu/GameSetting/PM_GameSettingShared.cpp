// Fill out your copyright notice in the Description page of Project Settings.


#include "PM_GameSettingShared.h"
#include "Physicssuk.h"
#include "GameFramework/PM_LocalPlayer.h"
#include "Kismet/GameplayStatics.h"

static FString SHARED_SETTINGS_SLOT_NAME = TEXT("SharedGameSettings");
// Define the static variable


void UPM_GameSettingShared::Initialize(UPM_LocalPlayer* LocalPlayer)
{
	OwningPlayer = LocalPlayer;
	
	DebugTimer();
}


void UPM_GameSettingShared::ApplySettings()
{
}
//인스턴스를 만든다. 만든 인스턴스는 UPM_GameSettingShared::SettingShared에 저장된다. 그리고 더 이상의 인스턴스를 만들지 않는다.
UPM_GameSettingShared* UPM_GameSettingShared::LoadOrCreateSettings(const UPM_LocalPlayer* LocalPlayer)
{
	UPM_GameSettingShared* SettingShared = nullptr;

	// If the save game exists, load it.
	if (UGameplayStatics::DoesSaveGameExist(SHARED_SETTINGS_SLOT_NAME, LocalPlayer->GetLocalPlayerIndex()))
	{
		USaveGame* Slot = UGameplayStatics::LoadGameFromSlot(SHARED_SETTINGS_SLOT_NAME, LocalPlayer->GetLocalPlayerIndex());
		SettingShared = Cast<UPM_GameSettingShared>(Slot);
	}
	
	if (SettingShared == nullptr)
	{
		SettingShared = Cast<UPM_GameSettingShared>(UGameplayStatics::CreateSaveGameObject(UPM_GameSettingShared::StaticClass()));
	}

	SettingShared->Initialize(const_cast<UPM_LocalPlayer*>(LocalPlayer));

	return SettingShared;
}

void UPM_GameSettingShared::SaveSettings()
{
	UGameplayStatics::SaveGameToSlot(this, SHARED_SETTINGS_SLOT_NAME, OwningPlayer->GetLocalPlayerIndex());
}

void UPM_GameSettingShared::DebugTimer()
{
}