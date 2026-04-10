// 版权没有，拷贝自由。


#include "Character/MainPlayerCharacter.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/BaseAbilitySystemComponent.h"
#include "AbilitySystem/BaseAttributeSet.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Player/MainPlayerState.h"


// Sets default values
AMainPlayerCharacter::AMainPlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 540.f, 0.f);
	GetCharacterMovement()->JumpZVelocity = 500.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.f;

	// 设置相机相关组件
	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 600.0f;
	CameraBoom->bUsePawnControlRotation = true;

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
}

UAbilitySystemComponent* AMainPlayerCharacter::GetAbilitySystemComponent() const
{
	auto PS = GetPlayerState<AMainPlayerState>();
	return UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(PS);
}

UAttributeSet* AMainPlayerCharacter::GetAttributeSet() const
{
	auto PS = GetPlayerState<AMainPlayerState>();
	if (!IsValid(PS)) return nullptr;


	return PS->GetAttributeSet();
}

void AMainPlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (!HasAuthority()) return;
	
	auto ASC = GetAbilitySystemComponent();
	if (!IsValid(ASC)) return;
	
	InitializeAbilityActorInfo();
	GiveStartupAbilities();

	InitializeAttributes();
	
	ASC->GetGameplayAttributeValueChangeDelegate(UBaseAttributeSet::GetHealthAttribute()).AddUObject(
		this, &AMainPlayerCharacter::OnHealthChanged);
}

void AMainPlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	InitializeAbilityActorInfo();
	
	// 这里代码和 PossessedBy 中重复了，要考虑重构，并且EnemyCharacter中也有类似代码。
	auto ASC = GetAbilitySystemComponent();
	if (!IsValid(ASC)) return;
	ASC->GetGameplayAttributeValueChangeDelegate(UBaseAttributeSet::GetHealthAttribute()).AddUObject(
		this, &AMainPlayerCharacter::OnHealthChanged);
}

void AMainPlayerCharacter::InitializeAbilityActorInfo()
{
	AMainPlayerState* PS = GetPlayerState<AMainPlayerState>();
	if (!IsValid(PS)) return;

	auto ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(PS);
	if (!ensureMsgf(IsValid(ASC),
	                TEXT(
		                "%s has a valid MainPlayerState, but its AbilitySystemComponent is null. This usually indicates a Blueprint default object/component reset after a native rename."
	                ), *GetNameSafe(PS)))
	{
		return;
	}

	ASC->InitAbilityActorInfo(PS, this);

	OnASCInitialized.Broadcast(ASC, GetAttributeSet());
}
