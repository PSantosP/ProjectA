// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GenericTeamAgentInterface.h"
#include "UObject/Object.h"
#include "UObject/WeakObjectPtr.h"

#include "PATeamAgentInterface.generated.h"

template <typename InterfaceType> class TScriptInterface;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnPATeamIndexChangedDelegate, UObject*, ObjectChangingTeam, int32, OldTeamID, int32, NewTeamID);

inline int32 GenericTeamIdToInteger(FGenericTeamId ID)
{
	return (ID == FGenericTeamId::NoTeam) ? INDEX_NONE : (int32)ID;
}

inline FGenericTeamId IntegerToGenericTeamId(int32 ID)
{
	return (ID == INDEX_NONE) ? FGenericTeamId::NoTeam : FGenericTeamId((uint8)ID);
}

//
UINTERFACE(meta=(CannotImplementInterfaceInBlueprint))
class UPATeamAgentInterface : public UGenericTeamAgentInterface
{
	GENERATED_UINTERFACE_BODY()
};

class PROJECTA_API IPATeamAgentInterface : public IGenericTeamAgentInterface
{
	GENERATED_IINTERFACE_BODY()
	
	virtual FOnPATeamIndexChangedDelegate* GetOnTeamIndexChangedDelegate() { return nullptr; }
	static void ConditionalBroadcastTeamChanged(TScriptInterface<IPATeamAgentInterface> This, FGenericTeamId OldTeamID, FGenericTeamId NewTeamID);


	// 델리게이트가 있는지 없는지체크한 후 반환
	FOnPATeamIndexChangedDelegate& GetTeamChangedDelegateChecked()
	{
		FOnPATeamIndexChangedDelegate* Result = GetOnTeamIndexChangedDelegate();
		check(Result);
		return *Result;
	}
};
