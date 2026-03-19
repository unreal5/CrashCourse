// 版权没有，拷贝自由。


#include "Player/MainPlayerState.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/BaseAbilitySystemComponent.h"

AMainPlayerState::AMainPlayerState()
{
	SetNetUpdateFrequency(100.f);

	CharAsc = CreateDefaultSubobject<UBaseAbilitySystemComponent>("BaseASC");
	CharAsc->SetIsReplicated(true);
	CharAsc->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
}

UAbilitySystemComponent* AMainPlayerState::GetAbilitySystemComponent() const
{
	return CharAsc;
}
