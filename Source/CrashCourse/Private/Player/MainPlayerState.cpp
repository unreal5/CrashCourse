// 版权没有，拷贝自由。


#include "Player/MainPlayerState.h"

#include "AbilitySystemComponent.h"

AMainPlayerState::AMainPlayerState()
{
	SetNetUpdateFrequency(100.f);

	ASC = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystemComponent");
	ASC->SetIsReplicated(true);
	ASC->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
}

UAbilitySystemComponent* AMainPlayerState::GetAbilitySystemComponent() const
{
	return ASC;
}
