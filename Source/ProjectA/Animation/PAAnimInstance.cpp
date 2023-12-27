// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/PAAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Character/PACharacterPlayer.h"

UPAAnimInstance::UPAAnimInstance()
{
	MovingThreshould = 0.5f;
	JumpingThreshould = 100.0f;
	bIsIdle = true;
}

UPAAnimInstance::UPAAnimInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UPAAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Owner = Cast<APACharacterPlayer>(GetOwningActor());

	if (Owner != nullptr)
	{
		Movement = Owner->GetCharacterMovement();
	}
}

void UPAAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (Movement != nullptr)
	{
		Velocity = Movement->Velocity;
		Speed = Velocity.Size2D();
		bIsIdle = Speed < MovingThreshould;
		bIsFalling = Movement->IsFalling();
		bIsJumping = bIsFalling & (Velocity.Z > JumpingThreshould);
		bIsSprint = Owner->IsSprint();
	}
}
