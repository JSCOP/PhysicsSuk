// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/SaveGame.h"
#include "UObject/Object.h"
#include "PM_GameSettingShared.generated.h"

/**
 * 
 */
UCLASS()
class PHYSICSSUK_API UPM_GameSettingShared : public USaveGame
{
	GENERATED_BODY()
public:
	DECLARE_EVENT_OneParam(UPM_GameSettingShared, FOnSettingChangedEvent, UPM_GameSettingShared* Settings);
	FOnSettingChangedEvent OnSettingChanged;
	
	virtual void Initialize(UPM_LocalPlayer* LocalPlayer); 
	
	UFUNCTION()
	double GetMouseSensitivityX() const { return MouseSensitivityX; }
	UFUNCTION()
	void SetMouseSensitivityX(double NewValue){ChangeValueAndDirty(MouseSensitivityX, NewValue);}
	UPROPERTY()
	double MouseSensitivityX = 1.f;

	UFUNCTION()
	double GetMouseSensitivityY() const { return MouseSensitivityY; }
	UFUNCTION()
	void SetMouseSensitivityY(double NewValue){ChangeValueAndDirty(MouseSensitivityY, NewValue);}
	UPROPERTY()
	double MouseSensitivityY = 1.f;

	UFUNCTION()
	double GetOverallMouseSensitivity() const { return OverallMouseSensivity; }
	UFUNCTION()
	void SetOverallMouseSensitivityY(double NewValue){ChangeValueAndDirty(OverallMouseSensivity, NewValue);}
	UPROPERTY()
	double OverallMouseSensivity = 1.f;


	UFUNCTION()
	void ApplySettings();

	UFUNCTION()
	void SaveSettings();
	
	UFUNCTION()
	static UPM_GameSettingShared* LoadOrCreateSettings(const UPM_LocalPlayer* LocalPlayer);
	
	UFUNCTION()
	void DebugTimer();

	bool IsTimerTick = false;
private:
	template<typename T>
	bool ChangeValueAndDirty(T& CurrentValue, const T& NewValue)
	{
		if (CurrentValue != NewValue)
		{
			CurrentValue = NewValue;
			bIsDirty = true;
			OnSettingChanged.Broadcast(this);
    			
			return true;
		}
    
		return false;
	}
	
    
    bool bIsDirty = false;
   
    UPROPERTY(Transient)
    TObjectPtr<UPM_LocalPlayer> OwningPlayer = nullptr;
};
