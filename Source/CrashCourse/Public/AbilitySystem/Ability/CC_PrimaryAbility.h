// 版权没有，拷贝自由。

#pragma once

#include "CoreMinimal.h"
#include "CC_GameplayAbility.h"
#include "CC_PrimaryAbility.generated.h"

/**
 * 
 */
UCLASS()
class CRASHCOURSE_API UCC_PrimaryAbility : public UCC_GameplayAbility
{
	GENERATED_BODY()
public:
	UCC_PrimaryAbility();
protected:
	void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	                     const FGameplayAbilityActivationInfo ActivationInfo,
	                     const FGameplayEventData* TriggerEventData) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Crash|Montage")
	TObjectPtr<UAnimMontage> AbilityMontage;
};
