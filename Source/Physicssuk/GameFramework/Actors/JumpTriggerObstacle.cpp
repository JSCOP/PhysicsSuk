// Fill out your copyright notice in the Description page of Project Settings.


#include "JumpTriggerObstacle.h"

#include "EngineUtils.h"
#include "GameFramework/Character/PM_MainCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AJumpTriggerObstacle::AJumpTriggerObstacle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AJumpTriggerObstacle::OnMainCharacterDestroyed(AActor* DestroyedActor)
{
	bIsMainCharacterIsDestroyed = true;
}

// Called when the game starts or when spawned
void AJumpTriggerObstacle::BeginPlay()
{
	Super::BeginPlay();
	MainCharacter = Cast<APM_MainCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if(!IsValid(MainCharacter))
	{
		return;
	}
	MainCharacter->OnJumpDelegate.AddDynamic(this, &AJumpTriggerObstacle::ActivateObstacle);
	MainCharacter->OnDestroyed.AddDynamic(this, &AJumpTriggerObstacle::OnMainCharacterDestroyed);
}

// Called every frame
void AJumpTriggerObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(bIsMainCharacterIsDestroyed)
	{
		for(auto* maincharacter : TActorRange<APM_MainCharacter>(GetWorld()))
		{
			maincharacter->OnJumpDelegate.AddDynamic(this, &AJumpTriggerObstacle::ActivateObstacle);
			maincharacter->OnDestroyed.AddDynamic(this, &AJumpTriggerObstacle::OnMainCharacterDestroyed);
			bIsMainCharacterIsDestroyed = false;
		}
	}
}

void AJumpTriggerObstacle::ActivateObstacle()
{
	K2_ActivateObstacle();
}
