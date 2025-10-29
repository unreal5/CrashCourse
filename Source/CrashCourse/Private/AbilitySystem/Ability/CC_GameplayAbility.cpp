// 版权没有，拷贝自由。


#include "AbilitySystem/Ability/CC_GameplayAbility.h"

void UCC_GameplayAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (!bDrawDebugs || !GEngine) return;

	GEngine->AddOnScreenDebugMessage(-1,5.f,FColor::Cyan, TEXT("Ability Activated: ") + GetName());
}
