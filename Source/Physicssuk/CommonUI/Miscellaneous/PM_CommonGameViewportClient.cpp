// Fill out your copyright notice in the Description page of Project Settings.


#include "CommonUI/Miscellaneous/PM_CommonGameViewportClient.h"

#include "Physicssuk.h"

bool UPM_CommonGameViewportClient::InputKey(const FInputKeyEventArgs& EventArgs)
{
	if(!EventArgs.Key.IsMouseButton() && EventArgs.Event == IE_Pressed)
	{
		OnAnykeyDelegate.Broadcast();
	}
	return Super::InputKey(EventArgs);
}

bool UPM_CommonGameViewportClient::InputTouch(FViewport* InViewport, int32 ControllerId, uint32 Handle,
	ETouchType::Type Type, const FVector2D& TouchLocation, float Force, FDateTime DeviceTimestamp, uint32 TouchpadIndex)
{
	return Super::InputTouch(InViewport, ControllerId, Handle, Type, TouchLocation, Force, DeviceTimestamp,
	                         TouchpadIndex);
}
