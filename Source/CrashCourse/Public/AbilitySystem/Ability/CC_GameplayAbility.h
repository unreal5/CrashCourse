// 版权没有，拷贝自由。

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "CC_GameplayAbility.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class CRASHCOURSE_API UCC_GameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Crash|Debug")
	bool bDrawDebugs = false;
};
