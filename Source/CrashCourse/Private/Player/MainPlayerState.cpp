// 版权没有，拷贝自由。


#include "Player/MainPlayerState.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/BaseAbilitySystemComponent.h"

namespace MainPlayerStateDefaults
{
	static const FName AbilitySystemComponentName(TEXT("BaseASC"));
}

AMainPlayerState::AMainPlayerState()
{
	SetNetUpdateFrequency(100.f);

	CharAsc = CreateDefaultSubobject<UBaseAbilitySystemComponent>(MainPlayerStateDefaults::AbilitySystemComponentName);
	CharAsc->SetIsReplicated(true);
	CharAsc->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
}

UAbilitySystemComponent* AMainPlayerState::GetAbilitySystemComponent() const
{
	return GetBaseAbilitySystemComponent();
}

UBaseAbilitySystemComponent* AMainPlayerState::GetBaseAbilitySystemComponent() const
{
	return CharAsc;
}
