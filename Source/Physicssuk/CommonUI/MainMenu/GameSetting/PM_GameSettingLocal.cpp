// Fill out your copyright notice in the Description page of Project Settings.


#include "PM_GameSettingLocal.h"

UPM_GameSettingLocal* UPM_GameSettingLocal::Get()
{
	return GEngine ? CastChecked<UPM_GameSettingLocal>(GEngine->GetGameUserSettings()) : nullptr;
}
