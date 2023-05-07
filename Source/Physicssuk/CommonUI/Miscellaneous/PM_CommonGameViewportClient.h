// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonGameViewportClient.h"
#include "PM_CommonGameViewportClient.generated.h"

/**
 * 
 */



UCLASS()
class PHYSICSSUK_API UPM_CommonGameViewportClient : public UCommonGameViewportClient
{
	GENERATED_BODY()

public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAnykeyDelegate);

	UPROPERTY(BlueprintAssignable, BlueprintReadWrite)
	FOnAnykeyDelegate OnAnykeyDelegate;
	virtual bool InputKey(const FInputKeyEventArgs& EventArgs) override;
	virtual bool InputTouch(FViewport* InViewport, int32 ControllerId, uint32 Handle, ETouchType::Type Type, const FVector2D& TouchLocation, float Force, FDateTime DeviceTimestamp, uint32 TouchpadIndex) override;
};
