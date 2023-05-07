// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/Pawn.h"
#include "PM_MainCharacter.generated.h"

class APlayerStart;
USTRUCT(BlueprintType)
struct FCharacterMovementStats
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float MovementSpeed = 1.f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float AngularSpeed = 1.f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float MaxAngularSpeed = 1.f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float JumpVelocity = 300.f;
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnJumpDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUserRespawn);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAnykeyPressedDelegate);

UCLASS()
class PHYSICSSUK_API APM_MainCharacter : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APM_MainCharacter();

protected:
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnConstruction(const FTransform& Transform) override;

	virtual void PossessedBy(AController* NewController) override;
public:	
	void Look(const FInputActionValue& InputActionValue);

	void Move(const FInputActionValue& InputActionValue);

	void MovePhysics(const float DeltaTime);
	
	void MoveRelease(const FInputActionValue& InputActionValue);
	
	void Jump(const FInputActionValue& InputActionValue);

	void StopJumping(const FInputActionValue& InputActionValue);
	
	void Respawn(const FInputActionValue& InputActionValue);
	
	void AnyKey();
	
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
public:
	
	UPROPERTY()
	FOnJumpDelegate OnJumpDelegate;

	UPROPERTY(BlueprintReadWrite, BlueprintAssignable, Category = "Delegates")
	FOnUserRespawn OnUserRespawn;

	UPROPERTY(BlueprintReadWrite, BlueprintAssignable, Category = "Delegates")
	FOnAnykeyPressedDelegate OnAnykeyDelegate;
private:
	
	//Input properties
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Input", meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultContext;

	//Actions
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Input", meta = (AllowPrivateAccess = "true"))
	class UInputAction* MouseInputAction;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Input", meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveInputAction;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Input", meta = (AllowPrivateAccess = "true"))
	class UInputAction* JumpInputAction;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Input", meta = (AllowPrivateAccess = "true"))
	class UInputAction* RespawnInputAction;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UStaticMeshComponent> CharacterMesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USpringArmComponent> SpringArm;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCameraComponent> Camera;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UNiagaraSystem> JumpFX;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	FCharacterMovementStats MovementStats;

	bool bIsOnGround = false;

	FVector LastNormalImpulse = FVector::ZeroVector;

	bool bIsRespawning = false;

	bool bMoveTriggerTest = false;

	FVector BoundSize;

	TOptional<FVector2D> MoveAxisValue;
};
