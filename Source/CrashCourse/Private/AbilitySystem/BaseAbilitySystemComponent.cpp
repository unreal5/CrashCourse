// 版权没有，拷贝自由。


#include "AbilitySystem/BaseAbilitySystemComponent.h"

#include "GameplayTag/CCTags.h"

void UBaseAbilitySystemComponent::OnGiveAbility(FGameplayAbilitySpec& AbilitySpec)
{
	// TODO: 详细分析Super::OnGiveAbility的实现
	Super::OnGiveAbility(AbilitySpec);

	HandleAutoActivatedAbility(AbilitySpec);
}

void UBaseAbilitySystemComponent::OnRep_ActivateAbilities()
{
	// TODO: 详细分析Super::OnRep_ActivateAbilities的实现
	Super::OnRep_ActivateAbilities();

	// 对于所有可激活技能，由于是动态的，因此在循环时要锁定技能列表，防止在迭代过程中移除技能导致崩溃
	ABILITYLIST_SCOPE_LOCK();
	for (const auto& Spec : GetActivatableAbilities())
	{
		HandleAutoActivatedAbility(Spec);
	}
}

void UBaseAbilitySystemComponent::HandleAutoActivatedAbility(const FGameplayAbilitySpec& AbilitySpec)
{
	if (!IsValid(AbilitySpec.Ability)) return;

	if (!AbilitySpec.Ability->GetAssetTags().HasTagExact(CCTags::CCAbilities::ActivateOnGiven)) return;

	TryActivateAbility(AbilitySpec.Handle);
	// 不要使用GiveAbilityAndActivateOnce，因为它会在激活一次移除能力，而我们希望保留能力。
}
