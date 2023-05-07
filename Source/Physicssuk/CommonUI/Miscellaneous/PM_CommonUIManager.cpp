// Fill out your copyright notice in the Description page of Project Settings.


#include "PM_CommonUIManager.h"

#include "Advertising.h"
#include "NativeGameplayTags.h"
#include "PrimaryGameLayout.h"
#include "GameFramework/PM_LocalPlayer.h"
#include "SubSystems/PM_CommonUISubsystemBase.h"

namespace FrontendTags 
{
	UE_DEFINE_GAMEPLAY_TAG_STATIC(TAG_UI_LAYER_MENU, "UI.Layer.Menu");
	UE_DEFINE_GAMEPLAY_TAG_STATIC(TAG_UI_LAYER_DEATH, "UI.Layer.GameMenu");
}

// Sets default values for this component's properties
UPM_CommonUIManager::UPM_CommonUIManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPM_CommonUIManager::BeginPlay()
{
	Super::BeginPlay();

	// ...

	//UPM_LocalPlayer* LocalPlayer = Cast<UPM_LocalPlayer>(GetWorld()->GetFirstLocalPlayerFromController());
	//UPM_CommonUISubsystemBase* CommonUISubsystem = LocalPlayer->GetGameInstance()->GetSubsystem<UPM_CommonUISubsystemBase>();
	//
	//if (IsValid(CommonUISubsystem) && IsValid(LocalPlayer))
	//{
	//	CommonUISubsystem->ActivateBaseUI(LocalPlayer);
	//}
//
	//AdvertisingProvider = FAdvertising::Get().GetAdvertisingProvider(FName("PromotionAfterDeath"));
}

void UPM_CommonUIManager::ActivateMainScreen()
{
	if (UPrimaryGameLayout* RootLayout = UPrimaryGameLayout::GetPrimaryGameLayoutForPrimaryPlayer(this->GetOwner()->GetWorld()))
	{
		constexpr bool bSuspendInputUntilComplete = true;
		RootLayout->PushWidgetToLayerStackAsync<UCommonActivatableWidget>(FrontendTags::TAG_UI_LAYER_MENU, bSuspendInputUntilComplete, MainScreenClass);
	}
}

void UPM_CommonUIManager::DeactivateMainScreen()
{
	if (UPrimaryGameLayout* RootLayout = UPrimaryGameLayout::GetPrimaryGameLayoutForPrimaryPlayer(this))
	{
		RootLayout->GetLayerWidget(FrontendTags::TAG_UI_LAYER_DEATH)->GetActiveWidget()->DeactivateWidget();
	}
}

void UPM_CommonUIManager::ActivateDeathScreen()
{
	if (UPrimaryGameLayout* RootLayout = UPrimaryGameLayout::GetPrimaryGameLayoutForPrimaryPlayer(this->GetOwner()->GetWorld()))
	{
		constexpr bool bSuspendInputUntilComplete = true;
		RootLayout->PushWidgetToLayerStackAsync<UCommonActivatableWidget>(FrontendTags::TAG_UI_LAYER_DEATH, bSuspendInputUntilComplete, DeathScreen);
	}
}

void UPM_CommonUIManager::DeactivateDeathScreen()
{
	if (UPrimaryGameLayout* RootLayout = UPrimaryGameLayout::GetPrimaryGameLayoutForPrimaryPlayer(this))
	{
		RootLayout->GetLayerWidget(FrontendTags::TAG_UI_LAYER_DEATH)->GetActiveWidget()->DeactivateWidget();
	}
}



// Called every frame
void UPM_CommonUIManager::TickComponent(float DeltaTime, ELevelTick TickType,
                                        FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

