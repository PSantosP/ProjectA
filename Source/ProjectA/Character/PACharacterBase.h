// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PACharacterBase.generated.h"

UCLASS()
class PROJECTA_API APACharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	APACharacterBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UFUNCTION(BlueprintCallable, Category = "PA|Character")
	APAPlayerController* GetPlayerController() const;

	UFUNCTION(BlueprintCallable, Category = "PA|Character")
	APlayerState* GetPAPlayerState() const;

	/*UFUNCTION(BlueprintCallable, Category = "PA|Character")*/


	// AActor Interface
	virtual void PreInitializeComponents() override;	// Actor의 컴포넌트들이 초기화되기전 호출
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Reset() override;						// Actor가 원래대로 돌아가야 할 때 호출
	// GetLifetimeReplicatedProps는 네트워크에서 복제되는 프로퍼티 설정
	// FLifetimeProperty는 복제되어야 할 프로퍼티 정보를 담고 있음
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	// 네트워크에서 복제 되기 직전에 호출되는 콜백 함수
	virtual void PreReplication(IRepChangedPropertyTracker& ChangedPropertyTracker) override;
	// AActor Interface End

	// APawn Interface
	virtual void NotifyControllerChanged() override;
	// APawn Interface End

protected:
	virtual void PossessedBy(AController* NewContorller) override;
	virtual void UnPossessed() override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

private:
	// Camera Section
	TObjectPtr<class UCameraComponent> CameraComponent;
};
