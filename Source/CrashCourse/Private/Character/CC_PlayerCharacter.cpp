// 版权没有，拷贝自由。


#include "Character/CC_PlayerCharacter.h"

#include "AbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Player/CC_PlayerState.h"

ACC_PlayerCharacter::ACC_PlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input
	GetCharacterMovement()->RotationRate = FRotator(0.f, 540.f, 0.f);
	GetCharacterMovement()->JumpZVelocity = 500.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.f;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 600.f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
}

UAbilitySystemComponent* ACC_PlayerCharacter::GetAbilitySystemComponent() const
{
	auto CC_PlayerState = GetPlayerState<ACC_PlayerState>();
	return CC_PlayerState ? CC_PlayerState->GetAbilitySystemComponent() : nullptr;
}

// Called when this Pawn is possessed. Only called on the server (or in standalone).
void ACC_PlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	UAbilitySystemComponent* Asc = GetAbilitySystemComponent();
	if (!IsValid(Asc)) return;
	
	Asc->InitAbilityActorInfo(GetPlayerState(), this);
	GiveStartupAbilities();
}

void ACC_PlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	auto Asc = GetAbilitySystemComponent();
	if (!IsValid(Asc)) return;
	
	Asc->InitAbilityActorInfo(GetPlayerState(), this);
}
