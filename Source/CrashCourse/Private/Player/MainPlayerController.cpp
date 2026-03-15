// 版权没有，拷贝自由。


#include "Player/MainPlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/Character.h"
#include "GameplayTag/CCTags.h"

void AMainPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (!IsLocalPlayerController()) return;

	// Add Input Mapping Contexts
	auto Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (!Subsystem) return;

	for (UInputMappingContext* CurrentContext : InputMappingContexts)
	{
		Subsystem->AddMappingContext(CurrentContext, 0);
	}

	// 绑定输入事件
	auto EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	if (!EnhancedInputComponent) return;

	auto JumpFunctor = [this](const FInputActionValue& /* Value */, bool bIsTriggered)
	{
		auto Char = GetCharacter();
		if (!Char) return;
		bIsTriggered ? Char->Jump() : Char->StopJumping();
	};

	EnhancedInputComponent->BindActionValueLambda(JumpAction, ETriggerEvent::Started, JumpFunctor, true);
	EnhancedInputComponent->BindActionValueLambda(JumpAction, ETriggerEvent::Completed, JumpFunctor, false);

	auto MoveFunctor = [this](const FInputActionValue& Value)
	{
		auto Char = GetCharacter();
		if (!Char) return;

		const FVector2D MoveValue = Value.Get<FVector2D>();
		FRotator ControlRotation = GetControlRotation();
		ControlRotation.Pitch = 0.f;
		const FVector MoveDirection = ControlRotation.RotateVector(FVector{MoveValue.Y, MoveValue.X, 0.f});
		Char->AddMovementInput(MoveDirection);
	};
	EnhancedInputComponent->BindActionValueLambda(MoveAction, ETriggerEvent::Triggered, MoveFunctor);

	auto LookFunctor = [this](const FInputActionValue& Value)
	{
		const FVector2D LookValue = Value.Get<FVector2D>();
		AddYawInput(LookValue.X);
		AddPitchInput(LookValue.Y);
	};
	EnhancedInputComponent->BindActionValueLambda(LookAction, ETriggerEvent::Triggered, LookFunctor);


	// 绑定 Primary Action
	EnhancedInputComponent->BindAction(PrimaryAction, ETriggerEvent::Started, this, &ThisClass::Primary);
}

void AMainPlayerController::Primary()
{
	auto ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn());
	if (!ASC) return;
	
	FGameplayTagContainer TagContainer;
	TagContainer.AddTag(CCTags::CCAbilities::Primary);
	ASC->TryActivateAbilitiesByTag(TagContainer);

}
