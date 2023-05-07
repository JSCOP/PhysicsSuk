// Copyright Epic Games, Inc. All Rights Reserved.

#include "PhysicssukGameMode.h"


#include "EngineUtils.h"
#include "PhysicssukCharacter.h"
#include "PhysicssukPC.h"
#include "Actors/SaveTrigger.h"
#include "Character/PM_MainCharacter.h"
#include "GameFramework/InputSettings.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

class UInputSettings;

APhysicssukGameMode::APhysicssukGameMode()
{
}


void APhysicssukGameMode::BeginPlay()
{	
	Super::BeginPlay();
	//PlayerDied Delegate initialize

}

void APhysicssukGameMode::RespawnPlayer()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	
	if(IsValid(PlayerController) && IsValid(PlayerController->GetPawn()))
	{
		PlayerController->GetPawn()->Destroy();
		if(IsValid(CurrentSaveTrigger))
		{
			FTransform Transform = CurrentSaveTrigger->GetRespawnPointComponent()->GetComponentTransform();
			
			FActorSpawnParameters SpawnParms;
			SpawnParms.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			
			AActor* SpawnedPawn = GetWorld()->SpawnActor(DefaultPawnClass, &Transform, SpawnParms);
			if(IsValid(SpawnedPawn) && Cast<APM_MainCharacter>(SpawnedPawn))
			{
				PlayerController->Possess(Cast<APM_MainCharacter>(SpawnedPawn));
			}
		}
		else
		{
			//Find PlayerStart from world
			for(auto* playerstart : TActorRange<APlayerStart>(GetWorld()))
			{
				if(IsValid(playerstart))
				{
					AActor* SpawnedPawn = GetWorld()->SpawnActor(DefaultPawnClass, &playerstart->GetActorTransform(), FActorSpawnParameters());
					if(IsValid(SpawnedPawn) && Cast<APM_MainCharacter>(SpawnedPawn))
					{
						PlayerController->Possess(Cast<APM_MainCharacter>(SpawnedPawn));
					}
					break;
				}
			}
		}
	}
}

void APhysicssukGameMode::SetSavePoint(ASaveTrigger* SaveTrigger)
{
	CurrentSaveTrigger = SaveTrigger;
}

void APhysicssukGameMode::StartPlay()
{
	Super::StartPlay();


}

void APhysicssukGameMode::MobileInputSetup()
{
	//Get Input Settings
	UInputSettings* InputSettings = GetMutableDefault<UInputSettings>();

	bool bIsMouseForTouch = false;
	
	if(InputSettings != nullptr)
	{
		bIsMouseForTouch = InputSettings->bUseMouseForTouch;	
	}
	
	//If platform is mobile or MouseInputToTouch is enabled(In the project settings) , create virtual joystick 
	if(UGameplayStatics::GetPlatformName() == "Android" || UGameplayStatics::GetPlatformName() == "IOS" || bIsMouseForTouch)
	{
		if(APhysicssukPC* PlayerController = Cast<APhysicssukPC>(UGameplayStatics::GetPlayerController(GetWorld(), 0)))
		{
			PlayerController->MobileInputSetup();
		}		
	}
}



