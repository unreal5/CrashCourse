// 版权没有，拷贝自由。


#include "Player/CC_PlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/Character.h"

void ACC_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	auto InputSubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (!IsValid(InputSubSystem)) return;

	for (const auto Context : InputMappingContexts)
	{
		InputSubSystem->AddMappingContext(Context, 0);
	}
	auto EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	if (!IsValid(EnhancedInputComponent)) return;

	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ThisClass::Jump);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ThisClass::StopJumping);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ThisClass::Move);
	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ThisClass::Look);

	EnhancedInputComponent->BindAction(PrimaryAction, ETriggerEvent::Started, this, &ThisClass::Primary);
}

void ACC_PlayerController::Jump()
{
	auto Char = GetCharacter();
	if (!IsValid(Char))return;

	Char->Jump();
}

void ACC_PlayerController::StopJumping()
{
	auto Char = GetCharacter();
	if (!IsValid(Char))return;

	Char->StopJumping();
}

void ACC_PlayerController::Move(const FInputActionValue& Value)
{
	if (!IsValid(GetPawn()))return;
	
	FVector2D InputValue = Value.Get<FVector2D>();
	FVector MovementDirection = FVector{InputValue.Y,InputValue.X, 0.f};
	const FRotator YawRotation {0.f, GetControlRotation().Yaw,0.f};
	MovementDirection = YawRotation.RotateVector(MovementDirection);
	GetPawn()->AddMovementInput(MovementDirection);
}

void ACC_PlayerController::Look(const FInputActionValue& Value)
{
	FVector2D InputValue = Value.Get<FVector2D>();
	AddPitchInput(InputValue.Y);
	AddYawInput(InputValue.X);
}

void ACC_PlayerController::Primary()
{
}
