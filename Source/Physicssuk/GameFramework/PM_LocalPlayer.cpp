// Fill out your copyright notice in the Description page of Project Settings.


#include "PM_LocalPlayer.h"

#include "CommonUI/MainMenu/GameSetting/PM_GameSettingLocal.h"
#include "CommonUI/MainMenu/GameSetting/PM_GameSettingShared.h"
#include "SubSystems/PM_LocalPlayerSubsystem.h"


void UPM_LocalPlayer::InitOnlineSession()
{
	Super::InitOnlineSession();

}

UPM_GameSettingLocal* UPM_LocalPlayer::GetLocalSettings() const
{
	return UPM_GameSettingLocal::Get();
}

UPM_GameSettingShared* UPM_LocalPlayer::GetSharedSettings() const
{
	UPM_LocalPlayerSubsystem* LocalPlayerSubsystem = GetSubsystem<UPM_LocalPlayerSubsystem>();
	if (LocalPlayerSubsystem && ensure(LocalPlayerSubsystem->SettingShared))
	{
		return LocalPlayerSubsystem->SettingShared;
	}
	return nullptr;
}
	