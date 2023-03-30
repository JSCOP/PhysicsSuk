// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/GameSettingPanel.h"
#include "PM_GameSettingPanel.generated.h"

/**
 * 
 */
UCLASS()
class PHYSICSSUK_API UPM_GameSettingPanel : public UGameSettingPanel
{
	GENERATED_BODY()
public:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	// Focus transitioning to subwidgets for the gamepad
	virtual FReply NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent) override;
	
	UFUNCTION(BlueprintCallable)
	void SaveSettings();
	
};
