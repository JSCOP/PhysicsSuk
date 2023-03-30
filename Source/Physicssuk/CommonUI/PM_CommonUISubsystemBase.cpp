// Fill out your copyright notice in the Description page of Project Settings.


#include "CommonUI/PM_CommonUISubsystemBase.h"

#include "CommonLocalPlayer.h"

void UPM_CommonUISubsystemBase::ActivateBaseUI(ULocalPlayer* Player)
{
	if (Player && Cast<UCommonLocalPlayer>(Player))
	{
		NotifyPlayerAdded(Cast<UCommonLocalPlayer>(Player));
	}
}
