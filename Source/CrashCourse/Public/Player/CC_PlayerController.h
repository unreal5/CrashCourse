// 版权没有，拷贝自由。

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/PlayerController.h"
#include "CC_PlayerController.generated.h"

struct FGameplayTag;
struct FInputActionValue;
class UInputAction;
class UInputMappingContext;
/**
 * 
 */
UCLASS()
class CRASHCOURSE_API ACC_PlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void SetupInputComponent() override;

private:
	UPROPERTY(EditDefaultsOnly, Category="Crash|Input|Movement")
	TArray<TObjectPtr<UInputMappingContext>> InputMappingContexts;

	UPROPERTY(EditDefaultsOnly, Category="Crash|Input|Movement")
	TObjectPtr<UInputAction> JumpAction;

	UPROPERTY(EditDefaultsOnly, Category="Crash|Input|Movement")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditDefaultsOnly, Category="Crash|Input|Movement")
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditDefaultsOnly, Category="Crash|Input|Ability")
	TObjectPtr<UInputAction> PrimaryAction;
	UPROPERTY(EditDefaultsOnly, Category="Crash|Input|Ability")
	TObjectPtr<UInputAction> SecondaryAction;
	UPROPERTY(EditDefaultsOnly, Category="Crash|Input|Ability")
	TObjectPtr<UInputAction> TeriaryAction;
	
	// Input Callbacks
	void Jump();
	void StopJumping();

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

	void Primary();
	void Secondary();
	void Tertiary();	
	void ActivateAbility(const FGameplayTag& AbilityTag) const;
};
