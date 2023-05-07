// Fill out your copyright notice in the Description page of Project Settings.


#include "PM_GameSettingPanel.h"

#include "CommonUserSubsystem.h"
#include "GameFramework/PM_LocalPlayer.h"
#include "CommonUI/MainMenu/GameSetting/PM_GameSettingShared.h"

void UPM_GameSettingPanel::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	
}

void UPM_GameSettingPanel::NativeConstruct()
{
	Super::NativeConstruct();
}

void UPM_GameSettingPanel::NativeDestruct()
{
	Super::NativeDestruct();
}

FReply UPM_GameSettingPanel::NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent)
{
	return Super::NativeOnFocusReceived(InGeometry, InFocusEvent);
}

