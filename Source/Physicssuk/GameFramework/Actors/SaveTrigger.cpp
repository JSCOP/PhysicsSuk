// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveTrigger.h"

#include "GameFramework/Character/PM_MainCharacter.h"
#include "Components/BoxComponent.h"
#include "GameFramework/PhysicssukGameMode.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASaveTrigger::ASaveTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	RespawnPointComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RespawnPointComponent"));

	SetRootComponent(BoxComponent);
	RespawnPointComponent->SetupAttachment(BoxComponent);
}

// Called when the game starts or when spawned
void ASaveTrigger::BeginPlay()
{
	Super::BeginPlay();

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnOverlapBegin);

	
}

// Called every frame
void ASaveTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASaveTrigger::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(APM_MainCharacter* MainCharacter = Cast<APM_MainCharacter>(OtherActor))
	{
		//Make maincharacter spawn to PlayerStart

		APhysicssukGameMode* GameMode = Cast<APhysicssukGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		if(IsValid(GameMode) && IsValid(PlayerController))
		{
			GameMode->SetSavePoint(this);
		}
	}
}

