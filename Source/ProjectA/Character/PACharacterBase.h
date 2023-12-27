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
	virtual void PreInitializeComponents() override;	// Actor�� ������Ʈ���� �ʱ�ȭ�Ǳ��� ȣ��
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Reset() override;						// Actor�� ������� ���ư��� �� �� ȣ��
	// GetLifetimeReplicatedProps�� ��Ʈ��ũ���� �����Ǵ� ������Ƽ ����
	// FLifetimeProperty�� �����Ǿ�� �� ������Ƽ ������ ��� ����
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	// ��Ʈ��ũ���� ���� �Ǳ� ������ ȣ��Ǵ� �ݹ� �Լ�
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
