// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PM_FrontEnd.generated.h"


class UCommonActivatableWidget;
UCLASS(Blueprintable,ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PHYSICSSUK_API UPM_FrontEnd : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UPM_FrontEnd();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess="true"))
	TSoftClassPtr<UCommonActivatableWidget> MainWidget;
};
