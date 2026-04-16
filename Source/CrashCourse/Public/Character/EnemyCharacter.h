// 版权没有，拷贝自由。

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "EnemyCharacter.generated.h"

class UAttributeSet;
class UBaseAbilitySystemComponent;
class UAbilitySystemComponent;

UCLASS()
class CRASHCOURSE_API AEnemyCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	AEnemyCharacter();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual UAttributeSet* GetAttributeSet() const override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Crash | AI")
	float AcceptanceRadius = 500.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Crash | AI")
	float MinAttackDelay = 0.1f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Crash | AI")
	float MaxAttackDelay = .5f;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	TObjectPtr<UBaseAbilitySystemComponent> EnemyAsc;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
};
