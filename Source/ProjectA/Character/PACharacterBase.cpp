// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PACharacterBase.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Net
#include "Net/UnrealNetwork.h"

// PlayerController
#include "Player/PAPlayerController.h"

static FName NAME_PACharacterCollisionProfile_Capsule(TEXT("PAPawnCapsule"));
static FName NAME_PACharacterCollisionProfile_Mesh(TEXT("PAPawnMesh"));

APACharacterBase::APACharacterBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Tick 제거
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	// ? 이것은 무엇?
	NetCullDistanceSquared = 900000000.0f;

	// Capsule
	UCapsuleComponent* CapsuleComp = GetCapsuleComponent();
	check(CapsuleComp);
	CapsuleComp->InitCapsuleSize(42.f, 96.f);
	CapsuleComp->SetCollisionProfileName(NAME_PACharacterCollisionProfile_Capsule);

	// SkeletalMesh
	USkeletalMeshComponent* MeshComp = GetMesh();
	check(MeshComp);
	MeshComp->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));		// Mesh가 앞을 보게끔회전
	MeshComp->SetCollisionProfileName(NAME_PACharacterCollisionProfile_Mesh);

	// Movement
	UCharacterMovementComponent* PAMoveComp = GetCharacterMovement();
	check(PAMoveComp);
	PAMoveComp->GravityScale = 1.0f;
	PAMoveComp->MaxAcceleration = 2400.0f;
	PAMoveComp->BrakingFrictionFactor = 1.0f;
	PAMoveComp->BrakingFriction = 6.0f;
	PAMoveComp->GroundFriction = 8.0f;
	PAMoveComp->BrakingDecelerationWalking = 1400.0f;
	PAMoveComp->bUseControllerDesiredRotation = false;
	PAMoveComp->bOrientRotationToMovement = false;
	// Movement - 회전속도
	PAMoveComp->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
	// Movement - AnimationRootMotion
	PAMoveComp->bAllowPhysicsRotationDuringAnimRootMotion = false;
	// Movement - Crouch
	PAMoveComp->GetNavAgentPropertiesRef().bCanCrouch = true;
	PAMoveComp->bCanWalkOffLedgesWhenCrouching = true;
	PAMoveComp->SetCrouchedHalfHeight(65.0f);

	// UseControllerRotation
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = true;
	bUseControllerRotationYaw = false;

	// 시야
	BaseEyeHeight = 80.0f;
	CrouchedEyeHeight = 50.0f;

	// Camera
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetRelativeLocation(FVector(-300.0f, 0.0f, 75.0f));
}

APAPlayerController* APACharacterBase::GetPlayerController() const
{
	return CastChecked<APAPlayerController>(Controller, ECastCheckedType::NullAllowed);
}

APlayerState* APACharacterBase::GetPAPlayerState() const
{
	return GetPlayerState();
}

void APACharacterBase::PreInitializeComponents()
{
	Super::PreInitializeComponents();
}



void APACharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
	UWorld* World = GetWorld();

	// 네트워크가 없으면
	const bool bRegisterWithSignificanceManager = !IsNetMode(NM_DedicatedServer);
	if (bRegisterWithSignificanceManager)
	{
		// @TODO: 나중에
	}
}

void APACharacterBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	// @TODO: 나중에
}

void APACharacterBase::Reset()
{

}

void APACharacterBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
}

void APACharacterBase::PreReplication(IRepChangedPropertyTracker& ChangedPropertyTracker)
{
}

void APACharacterBase::NotifyControllerChanged()
{
	// NotifyControllerChanged는 컨트롤러가 Actor를 조작하는 권한을 얻거나 잃을 때 호출되며, 
	// 이를 통해 Actor는 컨트롤 상태의 변화에 대응
}

void APACharacterBase::PossessedBy(AController* NewContorller)
{
	
}

void APACharacterBase::UnPossessed()
{
}

void APACharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
}
