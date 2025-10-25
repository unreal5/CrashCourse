// 版权没有，拷贝自由。


#include "Player/CC_PlayerState.h"

#include "AbilitySystemComponent.h"

ACC_PlayerState::ACC_PlayerState()
{
	SetNetUpdateFrequency(100.f);

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
}

UAbilitySystemComponent* ACC_PlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
