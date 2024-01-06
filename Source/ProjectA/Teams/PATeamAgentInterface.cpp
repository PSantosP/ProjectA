// Fill out your copyright notice in the Description page of Project Settings.


#include "Teams/PATeamAgentInterface.h"

#include "UObject/ScriptInterface.h"

// 생성된 cpp 파일을 모듈 cpp 파일에 인라인하는 지원이 추가
// 이렇게 하면 헤더 구문 분석이 덜 필요하므로 컴파일 시간이 향상됨
#include UE_INLINE_GENERATED_CPP_BY_NAME(PATeamAgentInterface)

UPATeamAgentInterface::UPATeamAgentInterface(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

// 팀이바뀌면 델리게이트가 실행됨
void IPATeamAgentInterface::ConditionalBroadcastTeamChanged(TScriptInterface<IPATeamAgentInterface> This, FGenericTeamId OldTeamID, FGenericTeamId NewTeamID)
{
	if (OldTeamID != NewTeamID)
	{
		const int32 OldTeamIndex = GenericTeamIdToInteger(OldTeamID);
		const int32 NewTeamIndex = GenericTeamIdToInteger(NewTeamID);

		UObject* ThisObj = This.GetObject();

		This.GetInterface()->GetTeamChangedDelegateChecked().Broadcast(ThisObj, OldTeamIndex, NewTeamIndex);
		
	}
}
