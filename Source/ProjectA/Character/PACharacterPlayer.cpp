// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PACharacterPlayer.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"


APACharacterPlayer::APACharacterPlayer()
{
	// SpringArm
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;


	// Camera
	UCameraComponent* TpsFollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("TpsFollowCamera"));
	TpsFollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TpsFollowCamera->bUsePawnControlRotation = false;

	UCameraComponent* FpsFollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FpsFollowCamera"));
	FpsFollowCamera->SetupAttachment(GetMesh(), TEXT("FX_Head"));
	FpsFollowCamera->bUsePawnControlRotation = true;
	FpsFollowCamera->SetRelativeRotation(FRotator(180.f, 0.f, 0.f));

	FpsFollowCamera->SetAutoActivate(false);

	CameraMap.Emplace(ECAMERA::TPS, TpsFollowCamera);
	CameraMap.Emplace(ECAMERA::FPS, FpsFollowCamera);

	CameraType = ECAMERA::TPS;
	MyCamera = CameraMap[CameraType];

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
	SetChangeCamera();
}

void APACharacterPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APACharacterPlayer::Move);
	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APACharacterPlayer::Look);
	EnhancedInputComponent->BindAction(ChangeCameraAction, ETriggerEvent::Started, this, &APACharacterPlayer::SetChangeCamera);
}

void APACharacterPlayer::SetChangeCamera()
{
	CameraType = CameraType == ECAMERA::TPS ? ECAMERA::FPS : ECAMERA::TPS;
	MyCamera->Deactivate();
	MyCamera = CameraMap[CameraType];
	MyCamera->Activate();
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

