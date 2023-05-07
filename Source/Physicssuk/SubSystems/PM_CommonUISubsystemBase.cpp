// Fill out your copyright notice in the Description page of Project Settings.


#include "PM_CommonUISubsystemBase.h"

#include "CommonLocalPlayer.h"
#include "GameplayTagContainer.h"

void UPM_CommonUISubsystemBase::ActivateBaseUI(ULocalPlayer* Player)
{
	if (Player && Cast<UCommonLocalPlayer>(Player))
	{
		NotifyPlayerAdded(Cast<UCommonLocalPlayer>(Player));
	}
}
