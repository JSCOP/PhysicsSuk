// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "PM_CommonUIManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUiActivatedDelegate, FGameplayTag, ActivatedWidgetTag);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUiDeactivatedDelegate, FGameplayTag, DeactivatedWidgetTag);

class UCommonActivatableWidget;
UCLASS(Blueprintable, meta=(BlueprintSpawnableComponent))
class PHYSICSSUK_API UPM_CommonUIManager : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UPM_CommonUIManager();


protected:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,FActorComponentTickFunction* ThisTickFunction) override;

	// Called when the game starts

	virtual void BeginPlay() override;
	
public:	
	UFUNCTION(BlueprintCallable)
	void ActivateMainScreen();

	UFUNCTION(BlueprintCallable)
	void DeactivateMainScreen();
	
	UFUNCTION(BlueprintCallable)
	void ActivateDeathScreen();

	UFUNCTION(BlueprintCallable)
	void DeactivateDeathScreen();

private:
	UPROPERTY(EditAnywhere, Category=UI)
	TSoftClassPtr<UCommonActivatableWidget> MainScreenClass;
	
	UPROPERTY(EditAnywhere, Category=UI)
	TSoftClassPtr<UCommonActivatableWidget> DeathScreen;

	class IAdvertisingProvider* AdvertisingProvider;

};
