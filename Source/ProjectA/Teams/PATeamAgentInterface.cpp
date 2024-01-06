// Fill out your copyright notice in the Description page of Project Settings.


#include "Teams/PATeamAgentInterface.h"

#include "UObject/ScriptInterface.h"

// ������ cpp ������ ��� cpp ���Ͽ� �ζ����ϴ� ������ �߰�
// �̷��� �ϸ� ��� ���� �м��� �� �ʿ��ϹǷ� ������ �ð��� ����
#include UE_INLINE_GENERATED_CPP_BY_NAME(PATeamAgentInterface)

UPATeamAgentInterface::UPATeamAgentInterface(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

// ���̹ٲ�� ��������Ʈ�� �����
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
