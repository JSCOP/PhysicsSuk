// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/GameSettingScreen.h"
#include "PM_GameSettingScreen.generated.h"


/**
 * 
 */
UCLASS()
class PHYSICSSUK_API UPM_GameSettingScreen : public UGameSettingScreen
{
public:
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized() override;
	
	virtual UGameSettingRegistry* CreateRegistry() override;

	virtual void NativeOnActivated() override;
	
	 
};
