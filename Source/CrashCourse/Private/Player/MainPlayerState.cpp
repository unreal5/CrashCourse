// 版权没有，拷贝自由。


#include "Player/MainPlayerState.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/BaseAbilitySystemComponent.h"
#include "AbilitySystem/BaseAttributeSet.h"


AMainPlayerState::AMainPlayerState()
{
	SetNetUpdateFrequency(100.f);

	CharAsc = CreateDefaultSubobject<UBaseAbilitySystemComponent>("BaseASC");
	CharAsc->SetIsReplicated(true);
	CharAsc->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	
	AttributeSet = CreateDefaultSubobject<UBaseAttributeSet>("BaseCharacterAttributeSet");
}

UAbilitySystemComponent* AMainPlayerState::GetAbilitySystemComponent() const
{
	return GetBaseAbilitySystemComponent();
}

UAttributeSet* AMainPlayerState::GetAttributeSet() const
{
	return AttributeSet;
}

UBaseAbilitySystemComponent* AMainPlayerState::GetBaseAbilitySystemComponent() const
{
	return CharAsc;
}
