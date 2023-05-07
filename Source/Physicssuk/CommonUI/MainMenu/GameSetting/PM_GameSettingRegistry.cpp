// Fill out your copyright notice in the Description page of Project Settings.


#include "PM_GameSettingRegistry.h"
#include "CommonInputBaseTypes.h"
#include "PM_GameSettingShared.h"

#include "GameSettingCollection.h"
#include "GameSettingValueScalarDynamic.h"
#include "PM_GameSettingLocal.h"
#include "GameFramework/PM_LocalPlayer.h"
#include "DataSource/GameSettingDataSourceDynamic.h"
#include "EditCondition/WhenCondition.h"

#define LOCTEXT_NAMESPACE "PM_GameSettingRegistry"

void UPM_GameSettingRegistry::OnInitialize(ULocalPlayer* InLocalPlayer)
{
	if(Cast<UPM_LocalPlayer>(InLocalPlayer))
	{
		//Add the mouse and keyboard settings
		UGameSettingCollection* MouseAndKeyboardSettings = this->MouseAndKeyboardSettings(Cast<UPM_LocalPlayer>(InLocalPlayer));
		RegisterSetting(MouseAndKeyboardSettings);
	}
}

UGameSettingCollection* UPM_GameSettingRegistry::MouseAndKeyboardSettings(ULocalPlayer* InLocalPlayer)
{

	UGameSettingCollection* Screen = NewObject<UGameSettingCollection>();
	Screen->SetDevName(TEXT("MouseAndKeyboardCollection"));
	Screen->SetDisplayName(LOCTEXT("MouseAndKeyboardCollection_Name", "Mouse & Keyboard"));
	Screen->Initialize(InLocalPlayer);
	
	//Create a setting for mouse x sensivity
	const TSharedRef<FWhenCondition> WhenPlatformSupportsMouseAndKeyboard = MakeShared<FWhenCondition>(
		[](const ULocalPlayer*, FGameSettingEditableState& InOutEditState)
		{
			const UCommonInputPlatformSettings* PlatformInput = UPlatformSettingsManager::Get().GetSettingsForPlatform<UCommonInputPlatformSettings>();
			if (!PlatformInput->SupportsInputType(ECommonInputType::MouseAndKeyboard))
			{
				InOutEditState.Kill(TEXT("Platform does not support mouse and keyboard"));
			}
		});

	UGameSettingCollection* Sensitivity = NewObject<UGameSettingCollection>();
	Sensitivity->SetDevName(TEXT("MouseSensitivityCollection"));
	Sensitivity->SetDisplayName(LOCTEXT("MouseSensitivityCollection_Name", "Sensitivity"));
	Screen->AddSetting(Sensitivity);
	{
		UGameSettingValueScalarDynamic* Settings = NewObject<UGameSettingValueScalarDynamic>();
		Settings->SetDevName(TEXT("MouseSensitivityYaw"));
		Settings->SetDisplayName(LOCTEXT("MouseSensitivityYaw_Name", "X-Axis Sensitivity"));
		Settings->SetDescriptionRichText(LOCTEXT("MouseSensitivityYaw_Description", "Sets the sensitivity of the mouse's horizontal (x) axis. With higher settings the camera will move faster when looking left and right with the mouse."));		
		Settings->SetDynamicGetter(GET_SHARED_SETTINGS_FUNCTION_PATH(GetMouseSensitivityX));
		Settings->SetDynamicSetter(GET_SHARED_SETTINGS_FUNCTION_PATH(SetMouseSensitivityX));
		Settings->SetDefaultValue(GetDefault<UPM_GameSettingShared>()->GetMouseSensitivityX());
		Settings->SetDisplayFormat(UGameSettingValueScalarDynamic::RawTwoDecimals);
		Settings->SetSourceRangeAndStep(TRange<double>(0, 10), 0.01);
		Settings->SetMinimumLimit(0.01);

		Settings->AddEditCondition(WhenPlatformSupportsMouseAndKeyboard);

		Sensitivity->AddSetting(Settings);
	}
	{
		UGameSettingValueScalarDynamic* Settings = NewObject<UGameSettingValueScalarDynamic>();
		Settings->SetDevName(TEXT("MouseSensitivityPitch"));
		Settings->SetDisplayName(LOCTEXT("MouseSensitivityPitch_Name", "Y-Axis Sensitivity"));
		Settings->SetDescriptionRichText(LOCTEXT("MouseSensitivityYaw_Description", "Sets the sensitivity of the mouse's Vertical (y) axis. With higher settings the camera will move faster when looking left and right with the mouse."));		
		Settings->SetDynamicGetter(GET_SHARED_SETTINGS_FUNCTION_PATH(GetMouseSensitivityY));
		Settings->SetDynamicSetter(GET_SHARED_SETTINGS_FUNCTION_PATH(SetMouseSensitivityY));
		Settings->SetDefaultValue(GetDefault<UPM_GameSettingShared>()->GetMouseSensitivityY());
		Settings->SetDisplayFormat(UGameSettingValueScalarDynamic::RawTwoDecimals);
		Settings->SetSourceRangeAndStep(TRange<double>(0, 10), 0.01);
		Settings->SetMinimumLimit(0.01);

		Settings->AddEditCondition(WhenPlatformSupportsMouseAndKeyboard);

		Sensitivity->AddSetting(Settings);
	}
	{
		UGameSettingValueScalarDynamic* Settings = NewObject<UGameSettingValueScalarDynamic>();
		Settings->SetDevName(TEXT("MouseOverallSensivity"));
		Settings->SetDisplayName(LOCTEXT("MouseSensitivity_Overall", "Overall Mouse Sensitivity"));
		Settings->SetDescriptionRichText(LOCTEXT("OverallMouseSensitivity_Description", "Sets the sensitivity of the mouse's both axis. With higher settings the camera will move faster when looking left and right with the mouse."));		
		Settings->SetDynamicGetter(GET_SHARED_SETTINGS_FUNCTION_PATH(GetOverallMouseSensitivity));
		Settings->SetDynamicSetter(GET_SHARED_SETTINGS_FUNCTION_PATH(SetOverallMouseSensitivityY));
		Settings->SetDefaultValue(GetDefault<UPM_GameSettingShared>()->GetOverallMouseSensitivity());
		Settings->SetDisplayFormat(UGameSettingValueScalarDynamic::RawTwoDecimals);
		Settings->SetSourceRangeAndStep(TRange<double>(0, 10), 0.01);
		Settings->SetMinimumLimit(0.01);

		Settings->AddEditCondition(WhenPlatformSupportsMouseAndKeyboard);

		Sensitivity->AddSetting(Settings);
	}

	
	return Screen;
	
}

void UPM_GameSettingRegistry::SaveChanges()
{
	Super::SaveChanges();

	//Save the mouse and keyboard settings
	if(UPM_LocalPlayer* LocalPlayer = Cast<UPM_LocalPlayer>(OwningLocalPlayer))
	{
		LocalPlayer->GetLocalSettings()->ApplySettings(true);//Let's findout what is this true for.
		
		LocalPlayer->GetSharedSettings()->ApplySettings();
		LocalPlayer->GetSharedSettings()->SaveSettings();
	}
}


