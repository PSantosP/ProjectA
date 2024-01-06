// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Teams/PATeamAgentInterface.h"
#include "PAPawn.generated.h"

UCLASS()
class PROJECTA_API APAPawn : public APawn, public IPATeamAgentInterface
{
	GENERATED_BODY()

public:
	
	APAPawn(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());


	// AActor interface
	virtual void PreInitializeComponents() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	// End of AActor interface

	// APawn interface
	virtual void PossessedBy(AController* NewController) override;
	virtual void UnPossessed() override;
	// End of APawn interface

	// IGenericTeamAgentInterface interface
	virtual void SetGenericTeamId(const FGenericTeamId& NewTeamID) override;
	virtual FGenericTeamId GetGenericTeamId() const override;
	virtual FOnPATeamIndexChangedDelegate* GetOnTeamIndexChangedDelegate() override;
	// End of IGenericTeamAgentInterface interface

protected:
	// 빙의가 종료가 되면 팀 아이디가 어떻게 되는지 확인하기 위한 호출
	virtual FGenericTeamId DetermineNewTeamAfterPossessionEnds(FGenericTeamId OldTeamID) const
	{
		return FGenericTeamId::NoTeam;
	}

private:
	UFUNCTION()
	void OnControllerChangedTeam(UObject* TeamAgent, int32 OldTeam, int32 NewTeam);

private:
	UPROPERTY(ReplicatedUsing = OnRep_MyTeamID)
	FGenericTeamId MyTeamID;

	UPROPERTY()
	FOnPATeamIndexChangedDelegate OnTeamChangedDelegate;

private:
	UFUNCTION()
	void OnRep_MyTeamID(FGenericTeamId OldTeamID);
};
