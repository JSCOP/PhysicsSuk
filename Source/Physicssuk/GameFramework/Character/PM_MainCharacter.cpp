// Fill out your copyright notice in the Description page of Project Settings.


#include "PM_MainCharacter.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputTriggers.h"
#include "NiagaraFunctionLibrary.h"
#include "Physicssuk.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "Components/BoxComponent.h"
#include "GameFramework/PhysicssukPC.h"

// Sets default values
APM_MainCharacter::APM_MainCharacter()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	//Initialize All Components
	CharacterMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CharacterMesh"));
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	//Setup Attachement
	SetRootComponent(CharacterMesh);

	SpringArm->SetupAttachment(RootComponent);
	Camera->SetupAttachment(SpringArm);
	
	SpringArm->bUsePawnControlRotation = true; 
	Camera->bUsePawnControlRotation = false;
}

// Called when the game starts or when spawned
void APM_MainCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	//Set Max Velocity of character mesh
	CharacterMesh->SetPhysicsMaxAngularVelocityInRadians(MovementStats.MaxAngularSpeed);


	//Set JumpState to false whenever the character is hit something.
	CharacterMesh->OnComponentHit.AddDynamic(this, &APM_MainCharacter::OnHit);

}

// Called every frame
void APM_MainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	BoundSize = FVector(CharacterMesh->Bounds.BoxExtent.X, CharacterMesh->Bounds.BoxExtent.Y, CharacterMesh->Bounds.BoxExtent.Z);
	//DrawDebugSphere(GetWorld(), GetActorLocation(), )
	FHitResult Hit;
	FVector StartPos = GetActorLocation() - BoundSize;
	FVector EndPos = GetActorLocation() + BoundSize;

	FCollisionQueryParams CollisionQueryParams;

	CollisionQueryParams.AddIgnoredActor(this);
	
	bIsOnGround = GetWorld()->SweepSingleByChannel(Hit, StartPos, EndPos, FQuat::Identity, ECollisionChannel::ECC_WorldStatic,
										FCollisionShape::MakeSphere(BoundSize.Length() - 1), CollisionQueryParams, FCollisionResponseParams::DefaultResponseParam);
	
	MovePhysics(DeltaTime);
}

void APM_MainCharacter::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	
}

void APM_MainCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	//GetPlayerController
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if(ensure(PlayerController != nullptr))
	{
		PlayerController->PlayerInput->FlushPressedKeys();
		PlayerController->PlayerInput->FlushPressedActionBindingKeys(FName("Move"));
		PlayerController->PlayerInput->FlushPressedActionBindingKeys(FName("Respawn"));
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultContext, 0);
		}
	}
	CharacterMesh->SetPhysicsLinearVelocity(FVector(0.f,0.f,0.f));
	CharacterMesh->SetPhysicsAngularVelocityInDegrees(FVector(0.f,0.f,0.f));
	
}

void APM_MainCharacter::Look(const FInputActionValue& InputActionValue)
{
	// input is a Vector2D
	FVector2D LookAxisVector = InputActionValue.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void APM_MainCharacter::Move(const FInputActionValue& InputActionValue)
{
	if(InputActionValue.IsNonZero() && InputComponent)
	{
		// input is a Vector2D
		MoveAxisValue = InputActionValue.Get<FVector2D>();

		//Debug to screen about MoveAxisValue
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("MoveAxisValue: %s"), *MoveAxisValue.GetValue().ToString()));
	}
}

void APM_MainCharacter::MovePhysics(const float DeltaTime)
{
	if(MoveAxisValue.IsSet())
	{
		// find out which way is forward
		FRotator Rotation = Controller->GetControlRotation();
		// Get Forward Vector
		FVector ForwardDirection = FRotationMatrix(Rotation).GetUnitAxis(EAxis::X);
		// Get Right Vector
		FVector RightDirection = FRotationMatrix(Rotation).GetUnitAxis(EAxis::Y);

		ForwardDirection *= MoveAxisValue.GetValue().Y;
		RightDirection *= MoveAxisValue.GetValue().X;

		FVector ActualDirection = (ForwardDirection + RightDirection).GetSafeNormal();

		//Draw Debugline about ActualDirection
		DrawDebugLine(GetWorld(), GetActorLocation(), GetActorLocation() + ActualDirection * 1000.f, FColor::Red, false, 0.1f, 0, 5.f);
	
		// add LinearVelocity and RotationalVelocity in that direction
		CharacterMesh->AddImpulse(ActualDirection * MovementStats.MovementSpeed * DeltaTime);

		CharacterMesh->SetPhysicsAngularVelocityInDegrees(CharacterMesh->GetPhysicsAngularVelocityInDegrees() + (FVector(-ActualDirection.Y, ActualDirection.X, ActualDirection.Z) * MovementStats.AngularSpeed * DeltaTime));
		
	}
}

void APM_MainCharacter::MoveRelease(const FInputActionValue& InputActionValue)
{
	MoveAxisValue.Reset();
}

void APM_MainCharacter::Jump(const FInputActionValue& InputActionValue)
{
	if(bIsOnGround)
	{
		bIsOnGround = false;
		
		CharacterMesh->AddImpulse(LastNormalImpulse * MovementStats.JumpVelocity);
		OnJumpDelegate.Broadcast();

		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), JumpFX, GetActorLocation(), FVector::CrossProduct(LastNormalImpulse, FVector(0.f,0.f,1.f)).Rotation());
	}
}

void APM_MainCharacter::StopJumping(const FInputActionValue& InputActionValue)
{
	//BindAction 의 Release 이벤트가 발생하면 호출됨.
}

void APM_MainCharacter::Respawn(const FInputActionValue& InputActionValue)
{
	if(APhysicssukPC* PC = Cast<APhysicssukPC>(GetController()))
	{
		DisableInput(PC);
		PC->OnRespawn();
		OnUserRespawn.Broadcast();
	}
}


void APM_MainCharacter::AnyKey()
{
	OnAnykeyDelegate.Broadcast();
}

void APM_MainCharacter::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                              FVector NormalImpulse, const FHitResult& Hit)
{
	bIsOnGround = true;
	NormalImpulse.Normalize();
	LastNormalImpulse = NormalImpulse;
	LastNormalImpulse.Z = 1;

	DrawDebugLine(GetWorld(), Hit.ImpactPoint, Hit.ImpactPoint + LastNormalImpulse * 100, FColor::Red, false, 1.f, 0, 1.f);
}



// Called to bind functionality to input
void APM_MainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		//Looking
		EnhancedInputComponent->BindAction(MouseInputAction, ETriggerEvent::Triggered, this, &APM_MainCharacter::Look);
		//Moving
		EnhancedInputComponent->BindAction(MoveInputAction, ETriggerEvent::Triggered, this, &APM_MainCharacter::Move);

		EnhancedInputComponent->BindAction(MoveInputAction, ETriggerEvent::Completed, this, &APM_MainCharacter::MoveRelease);
		//Jumping
		EnhancedInputComponent->BindAction(JumpInputAction, ETriggerEvent::Triggered, this, &APM_MainCharacter::Jump);
		//StopJumping
		EnhancedInputComponent->BindAction(JumpInputAction, ETriggerEvent::Completed, this, &APM_MainCharacter::StopJumping);
		//Respawn 
		EnhancedInputComponent->BindAction(RespawnInputAction, ETriggerEvent::Triggered, this, &APM_MainCharacter::Respawn);
	}
	InputComponent->BindAction(TEXT("AnyKey"), EInputEvent::IE_Pressed, this, &APM_MainCharacter::AnyKey);
}