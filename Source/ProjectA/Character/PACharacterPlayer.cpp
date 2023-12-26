// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PACharacterPlayer.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

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



	// Input
	static ConstructorHelpers::FObjectFinder<UInputMappingContext> DefaultMappingContextRef(TEXT("/Game/ProjectA/Input/IMC_Default.IMC_Default"));
	if (DefaultMappingContextRef.Succeeded())
	{
		DefaultMappingContext = DefaultMappingContextRef.Object;
	}
	static ConstructorHelpers::FObjectFinder<UInputAction> JumpActionRef(TEXT("/Game/ProjectA/Input/IA_JumpAction.IA_JumpAction"));
	if (JumpActionRef.Succeeded())
	{
		JumpAction = JumpActionRef.Object;
	}
	static ConstructorHelpers::FObjectFinder<UInputAction> MoveActionRef(TEXT("/Game/ProjectA/Input/IA_MoveAction.IA_MoveAction"));
	if (MoveActionRef.Succeeded())
	{
		MoveAction = MoveActionRef.Object;
	}
	static ConstructorHelpers::FObjectFinder<UInputAction> LookActionRef(TEXT("/Game/ProjectA/Input/IA_LookAction.IA_LookAction"));
	if (LookActionRef.Succeeded())
	{
		LookAction = LookActionRef.Object;
	}
	static ConstructorHelpers::FObjectFinder<UInputAction> ChangeCameraActionRef(TEXT("/Game/ProjectA/Input/IA_ChangeCameraAction.IA_ChangeCameraAction"));
	if (ChangeCameraActionRef.Succeeded())
	{
		ChangeCameraAction = ChangeCameraActionRef.Object;
	}
}

void APACharacterPlayer::BeginPlay()
{
	Super::BeginPlay();
	
	// MappingContext

	APlayerController* PlayerController = CastChecked<APlayerController>(GetController());

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
}

void APACharacterPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APACharacterPlayer::Move);
	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APACharacterPlayer::Look);
	EnhancedInputComponent->BindAction(ChangeCameraAction, ETriggerEvent::Triggered, this, &APACharacterPlayer::SetChangeCamera);
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
	else
	{
		UE_LOG(LogTemp, Error, TEXT("ERRORORORORORR"));
	}
}

void APACharacterPlayer::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(ForwardDirection, MovementVector.X);
	AddMovementInput(RightDirection, MovementVector.Y);
}

void APACharacterPlayer::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	AddControllerYawInput(LookAxisVector.X);
	AddControllerPitchInput(LookAxisVector.Y);
}

