// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"

DECLARE_LOG_CATEGORY_EXTERN(LogPhysicssuk, Warning, All);

static FString GetNetModeToString(ENetMode NetMode)
{
	switch(NetMode)
	{
	case NM_Client:
		return FString("Client") + FString::FromInt(GPlayInEditorID) + FString(" ");
	case NM_DedicatedServer:
		return FString("Server") + FString::FromInt(GPlayInEditorID) + FString(" ");
	case NM_ListenServer:
		return FString("Server") + FString::FromInt(GPlayInEditorID) + FString(" ");
	case NM_Standalone:
		return FString("Standalone") + FString::FromInt(GPlayInEditorID) + FString(" ");
	default:
		break;
	}
	return FString("");
}

static int32 GetNetModeToInt(ENetMode NetMode)
{
	switch(NetMode)
	{
	case NM_Client:
		return 10001;
	case NM_DedicatedServer:
		return 20001;
	case NM_ListenServer:
		return 20001;
	case NM_Standalone:
		return 30001;
	default:
		break;
	}
	return 0;
}

static int32 GetSpecialNumber(UObject* SpecialObject)
{
	if(IsValid(SpecialObject))
	{
		return SpecialObject->GetUniqueID();
	}
	return 0;
}

static int32 GetNetworkIndex(UObject* SpecialObject)
{
	if(IsValid(SpecialObject))
	{
		UWorld* World = SpecialObject->GetWorld();
		auto* gameinstance = UGameplayStatics::GetGameInstance(SpecialObject->GetWorld());
		if(auto* gameplayer = gameinstance->GetFirstGamePlayer())
		{
			auto netID =gameplayer->GetPreferredUniqueNetId().GetUniqueNetId();
			return static_cast<int32>(*netID->GetBytes());
		}		
	}
	return -1;
}

//메세지만 화면, 콘솔에 띄움.
#define LOG_K(Key, Format, ...) GEngine->AddOnScreenDebugMessage(Key, 1.f, FColor::Red, FString::Printf(TEXT(Format), ##__VA_ARGS__))

#define LOG_ALL(Key, Format, HowLong, Color, ...) GEngine->AddOnScreenDebugMessage(Key, HowLong, Color, FString::Printf(TEXT(Format), ##__VA_ARGS__))

#define LOG_FL(Format, HowLong, ...) GEngine->AddOnScreenDebugMessage(-1, HowLong, Color, FString::Printf(TEXT(Format), ##__VA_ARGS__))

#define LOG_CALLINFO (FString(__FUNCTION__) + TEXT("(") + FString::FromInt(__LINE__) + TEXT(")"))

#define LOG(Format, ...)  GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, GetNetModeToString(GetWorld()->GetNetMode()) + FString::Printf(TEXT(Format), ##__VA_ARGS__));\
UE_LOG(LogPhysicssuk, Warning, TEXT("%s " Format),*GetNetModeToString(GetWorld()->GetNetMode()), ##__VA_ARGS__)

//Call it Inside of component.
#define IS_CLIENT GetOwner()->GetLocalRole() == ENetRole::ROLE_AutonomousProxy && GetNetMode() == NM_Client
//Call it Inside of component.
#define IS_SERVER GetNetMode() == NM_ListenServer || GetNetMode() == NM_DedicatedServer || GetOwner()->GetLocalRole() == ROLE_Authority

#define SETTIMER(Amount, Function) FTimerHandle TimerHandle;\
GetWorld()->GetTimerManager().SetTimer(TimerHandle,Function, Amount, false, -1.f)



