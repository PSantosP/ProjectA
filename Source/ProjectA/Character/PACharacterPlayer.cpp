// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PACharacterPlayer.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

APACharacterPlayer::APACharacterPlayer()
{
	// SpringArm
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;


	// Camera
	TpsCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("TPSCamera"));
	TpsCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TpsCamera->bUsePawnControlRotation = false;

	FpsCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FPSCamera"));
	FpsCamera->SetupAttachment(GetMesh(), TEXT("FX_Head"));
	FpsCamera->bUsePawnControlRotation = false;

	FpsCamera->SetAutoActivate(false);
}

void APACharacterPlayer::BeginPlay()
{
	Super::BeginPlay();
	//SetChangeCamera();
}

void APACharacterPlayer::SetChangeCamera()
{
	ensure(TpsCamera);
	ensure(FpsCamera);
	if (IsValid(TpsCamera) && IsValid(FpsCamera))
	{
		switch (CameraType)
		{
		case ECAMERA::TPS:
			TpsCamera->Deactivate();
			FpsCamera->Activate();
			MyCamera = TpsCamera;
			break;
		case ECAMERA::FPS:
			TpsCamera->Activate();
			FpsCamera->Deactivate();
			MyCamera = FpsCamera;
			break;
		}
	}
}


