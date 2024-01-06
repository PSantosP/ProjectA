// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PAPawn.h"
#include "GameFramework/Controller.h"
#include "UObject/ScriptInterface.h"
#include "Net/UnrealNetwork.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(PAPawn)

class FLifetimeProperty;
class UObject;

APAPawn::APAPawn(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void APAPawn::PreInitializeComponents()
{
	Super::PreInitializeComponents();
}

void APAPawn::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, MyTeamID);
}

void APAPawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void APAPawn::PossessedBy(AController* NewController)
{
	const FGenericTeamId OldTeamID = MyTeamID;
	// 빙의가 되면
	Super::PossessedBy(NewController);

	if (IPATeamAgentInterface* ControllerAsTeamProvider = Cast<IPATeamAgentInterface>(NewController))
	{
		MyTeamID = ControllerAsTeamProvider->GetGenericTeamId();
		ControllerAsTeamProvider->GetTeamChangedDelegateChecked().AddDynamic(this, &ThisClass::OnControllerChangedTeam);
	}
	ConditionalBroadcastTeamChanged(this, OldTeamID, MyTeamID);
}

void APAPawn::UnPossessed()
{
	AController* const OldController = Controller;

	const FGenericTeamId OldTeamID = MyTeamID;
	if (IPATeamAgentInterface* ControllerAsTeamProvider = Cast<IPATeamAgentInterface>(OldController))
	{
		// 델리게이트 다 취소
		ControllerAsTeamProvider->GetTeamChangedDelegateChecked().RemoveAll(this);
	}
}

void APAPawn::SetGenericTeamId(const FGenericTeamId& NewTeamID)
{
}

FGenericTeamId APAPawn::GetGenericTeamId() const
{
	return MyTeamID;
}

FOnPATeamIndexChangedDelegate* APAPawn::GetOnTeamIndexChangedDelegate()
{
	return &OnTeamChangedDelegate;
}

void APAPawn::OnControllerChangedTeam(UObject* TeamAgent, int32 OldTeam, int32 NewTeam)
{
	const FGenericTeamId MyOldTeamID = MyTeamID;
	MyTeamID = IntegerToGenericTeamId(NewTeam);
	ConditionalBroadcastTeamChanged(this, MyOldTeamID, MyTeamID);
}

void APAPawn::OnRep_MyTeamID(FGenericTeamId OldTeamID)
{
	ConditionalBroadcastTeamChanged(this, OldTeamID, MyTeamID);
}
