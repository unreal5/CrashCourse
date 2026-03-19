// 版权没有，拷贝自由。

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "MainPlayerState.generated.h"

class UBaseAbilitySystemComponent;
class UAbilitySystemComponent;

UCLASS()
class CRASHCOURSE_API AMainPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AMainPlayerState();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Crash Coursh | AbilitySystem")
	TObjectPtr<UBaseAbilitySystemComponent> CharAsc;
};
